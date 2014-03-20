#include "stlsl.h"
#include <sstream>

using namespace std;
/*
	This class is responsible for converting sentences 
	to corresponding string of integers
	----------------------------------------
	1. this is text email text ->>>>> 1 2 3 4 3
	2. i like your text  --------->>> 5 6 7 3
	
	This given sentence is converted into numeric form. This is taken as
	a single transaction


*/

class Transactions
{
private:
	static map<string,int>tokenMap; //maps string token into corresponding integers
	static string  tokenMapLocation; //holds location in disk
	static string tokenCounterLocation;//counter location in disk	
	static map<int,int>itemSupportMap;//map for count for individual token item
	static string itemSupportMapLocation;//location in disk
	static int maxTokens;// total number of different tokens
	
	
public:
	static bool initialized;
	void createTransactions(vector< vector<string> >&,vector<string>&,vector< vector<int> >&,bool);
	
	template<class T1,class T2>
		static void loadFile(map<T1,T2>& object,const char* fileLocation)
		//loads a file with specified location into "object"
		{
			ifstream inFile(fileLocation);
			if(inFile==NULL)
				return;
			map_value_trait<T1,T2>data_reader;
			data_reader.load(object,inFile);
			inFile.close();
	}
	static void initialize(string dataPath)
	//initializes initial context for the Transaction class
	{
		tokenMapLocation=dataPath+"\\tokenmap.txt";		
		tokenCounterLocation=dataPath+"\\tokenCounter.txt";
		itemSupportMapLocation=dataPath+"\\itemSupport.txt";
		ifstream inFile(tokenCounterLocation.c_str());
		if(inFile!=NULL)
		{
			
			inFile>>maxTokens;
			inFile.close();
			loadFile(tokenMap,tokenMapLocation.c_str());
			
		}

		else
		{
		//if no email files are scanned,i.e. no tokens encountered
		//then create new file to store tokencounter and initialize
		//counter to zero.
			cout<<"can not load token counter"<<endl;
			maxTokens=0;
			ofstream outFile(tokenCounterLocation.c_str());
			outFile<<maxTokens;
			outFile.close();
		}
		loadFile(itemSupportMap,itemSupportMapLocation.c_str());

	}
	static void reset()
	/* resetes the current status of the class
	this outputs the counter to counterLocation, and other static maps
	to their corresponding location */
	{
			ofstream outFile(tokenCounterLocation.c_str());
			outFile<<maxTokens;
			outFile.close();
			outFile.open(tokenMapLocation.c_str());
			map_value_trait<string,int>data_filer;
			data_filer.serialize(tokenMap,outFile);
			outFile.close();
			outFile.open(itemSupportMapLocation.c_str());
			map_value_trait<int,int>map_filer;
			map_filer.serialize(itemSupportMap,outFile);
			outFile.close();
	}
	static void clean()
		/* this resets the class context and also clears all the variables*/
	{
		
			reset();
			tokenMap.clear();
			initialized=false;
	}
	static map<int,int>& getItemSupportMap(){
		return itemSupportMap;
	}
};

string Transactions::tokenMapLocation;
string Transactions::tokenCounterLocation;
map<string,int> Transactions::tokenMap;
int Transactions::maxTokens;
//int Transactions::avgLength;
string Transactions::itemSupportMapLocation;
map<int,int> Transactions::itemSupportMap;
bool Transactions::initialized=false;



void Transactions::createTransactions(vector< vector<string> >&mappingTokens,vector<string>& subject,vector< vector<int> >&mappedTokens,bool isLearning)
/*maps a vector of string into a vector of int 
if a token in mapping token is found in the tokenMap corresponding mapped
value is used as id for that token
else maxTokens is incremented by 1 and the new value of maxTokens is the 
id for tha token----then the new pair is inserted in tokenMap to map the same
*/
{
	/*
	int i = 5;
	string str;
	stringstream out;
	out << i;
	str = out.str();

 */
	cout<<"----------creating transactions----------------------"<<endl;
	
	map<string,int>::iterator tempItr;
	
	vector<int> tempTokens;
	for(int i=0;i<mappingTokens.size();++i)
	{
		tempTokens.clear();
		for(int j=0;j<mappingTokens[i].size();++j){
			
			if(tokenMap.size()>0)
			{
				tempItr=tokenMap.find(mappingTokens[i][j]);
				if(tempItr!=tokenMap.end())
				{
					tempTokens.push_back(tempItr->second);
					itemSupportMap[tempItr->second]++;//support of the item incremented
				}
				else
				{
					if(!isLearning)
						continue;
					++maxTokens;
					//now convert it to string, append attribute id 
					//then convert back to int
					/*string str;
					stringstream out;
					out<<maxTokens;
					str=out.str();
					maxTokens=atoi(str.c_str());//not appended yet*/
					//we will append id later 
				
					tokenMap[mappingTokens[i][j]]=maxTokens;
					tempTokens.push_back(maxTokens);
					itemSupportMap[maxTokens]=1;//support of the item initialized
				}
			}
			else
			//case when the tokenMap is empty, i.e. no items encountered yet
			{
				if(!isLearning)
					continue;
				tokenMap[mappingTokens[i][j]]=++maxTokens;
				tempTokens.push_back(maxTokens);
				itemSupportMap[maxTokens]=1;
			}

		}
		if(!tempTokens.empty())
			mappedTokens.push_back(tempTokens);
		

	}
	//now repeat the process for subject

	

}
	
