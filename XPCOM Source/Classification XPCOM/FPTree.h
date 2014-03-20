#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include "transactions.h"
#endif
#include<process.h>


/* TreeeNode is the FPTree node, each node has to store a link for the
next node with the same item and parent*/

struct TreeNode{
public:
	TreeNode *nodeLink;
	TreeNode *parent;
	int itemId;
	int itemSupport;//count of the item for that particular link
};
struct HeaderNode{
	//int itemId;
public:
	int itemSupport;//total count for the occurence of the item
	TreeNode *nodeLink;//link of first node int the tree with this item
};
/*struct ItemHeader{
public:
	int itemId;
	TreeNode* nodeLink;
	int itemSupport;
};*/

	

class FPTree{
protected:
	
	static vector<int>frequentItems;//frequent items in the whole database
	static int D;//size of database in terms of number of items, reoccurence
					//of same item is counted
	static bool initialized;//if frequntItems is loaded from itemSupport file
	static string itemSupportLocation;
	
public:
	static void initialize(string dataPath){
		itemSupportLocation=dataPath+"\\itemSupport.txt";
		if(!initialized)
		{		
			loadFrequentItems(0.002f,dataPath);
			initialized=true;
			
		}
	}
	static void loadFrequentItems(float minSupport,string dataPath)
	{//loads frequent items if they satisfy minSupport
		ifstream inFile(itemSupportLocation.c_str());
		if(!Transactions::initialized)
			Transactions::initialize(dataPath);
		loadItemsFromMap(Transactions::getItemSupportMap(),minSupport);
	}
	static void	loadItemsFromMap(map<int,int>& itemSupportMap,float minSupport)
	{//loads frequent items using itemSupport map from the transaction class
	
		
		D=0;
		float support;
		map<int,int>::iterator itr=itemSupportMap.begin();
		for(;itr!=itemSupportMap.end();++itr)//calculate D
			D+=itr->second;
		for(itr=itemSupportMap.begin();itr!=itemSupportMap.end();++itr){
			support=(float)itr->second/(float)D;
			if(support>minSupport)//if the item satisfies min-sup
				frequentItems.push_back(itr->first);
		}
		////cout<<"size in beginning"<<frequentItems.size();
	}
	static void sortItemsAscending(vector<int> frequentItems,vector<int>& ascendingItems)
	{
		//sorts items in the frequency ascending order using 
		//frequentItems map as the base table and uses bubble sort
		map<int,int>::iterator;
		ascendingItems.clear();
		map<int,int>tempMap=Transactions::getItemSupportMap();
		while(frequentItems.size()>0){
			int index=0;
			for(int i=1;i<frequentItems.size();++i){
				if(tempMap[frequentItems[i]]<tempMap[frequentItems[index]])
					index=i;
			}
			ascendingItems.push_back(frequentItems[index]);
			frequentItems.erase(frequentItems.begin()+index);
		}
		

	}
	static void sortItemsDescending(vector<int>& frequentItems,vector<int>& descendingItems)
	{
		//sorts items in the frequency descending order according to 
		//frequent items map in the Transaction class using bubble sort
		map<int,int>::iterator;
		descendingItems.clear();
		////cout<<"size "<<frequentItems.size()<<endl;
		
		map<int,int>tempMap=Transactions::getItemSupportMap();
		/*for(int i=0;i<frequentItems.size();++i)
		{
			if(tempMap.find(frequentItems[i])==tempMap.end())
			{
				frequentItems.erase(frequentItems.begin()+i);
				--i;
			}
		}*/
		int *sortedIndex=new int[frequentItems.size()+1];
		for(int i=0;i<frequentItems.size();++i)
			sortedIndex[i]=i;
		for(int i=0;i<frequentItems.size()-1;++i)
		{
			sortedIndex[i]=i;
			for(int j=i+1;j<frequentItems.size();++j)
			{
				if(tempMap[frequentItems[sortedIndex[i]]]<tempMap[frequentItems[sortedIndex[j]]])
				{
					int temp=sortedIndex[j];
					sortedIndex[j]=sortedIndex[i];
					sortedIndex[i]=temp;
				}
			}
		}
		for(int i=0;i<frequentItems.size();++i)
		{
			descendingItems.push_back(frequentItems[sortedIndex[i]]);
			
		}
		

	}
	
	
	
	static int getD(){ return D;}

};


int FPTree::D;
string FPTree::itemSupportLocation;
vector<int> FPTree::frequentItems;
bool FPTree::initialized=false;

