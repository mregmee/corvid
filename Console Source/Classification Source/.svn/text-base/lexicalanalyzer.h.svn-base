
#include<string>
#include<vector>
#include<iostream>
using namespace std;
/*
This class performs lexical operations on given sentence. The factors 
considered in lexical operation are:
	--eliminate word starting with a digit 
	--non literal characters  at the beginning or end of the word are stripped
	off if any non-literal character are still present the word is discarded
	eg. "**important$" becomes "important" whereas "imp*ortant" is discarded
	--words containing appostrophe are stripped to retain original word only
	eg. world's becomes world
	--words containing forward slash are divided into parts from the positions
	of slash eg. political/social becomes "political" and "social"
*/
	  
class LexicalAnalyzer
{
private:
	static  string nonLiterals;//list of nonliteral character considered
public:
	void eliminateNumbers(vector< vector<string> >&);
	void eliminateNonLiterals(vector< vector<string> >&);
};
string LexicalAnalyzer::nonLiterals="=-(){}|@*&~`!#$%+";


void LexicalAnalyzer::eliminateNumbers(vector< vector<string> >& sentences)
{
	for(int k=0;k<sentences.size();++k)
	{
		//discarding tokens starting with numbers
		for(int i=0;i<sentences[k].size();++i)
		{
			if(isdigit(sentences[k][i][0]))//discard word that begins with a digit
			{
				sentences[k].erase(sentences[k].begin()+i);
				--i;
			}
		}
	}
}
void LexicalAnalyzer::eliminateNonLiterals(vector< vector<string> >& sentences)
{

	
	/* debug 19th Dec,2007 problem: string subscript out of range
	the problem was in substring extraction:
	sentences[m][i].substr(j,len-k-j+1)
	and the value of k and j was not checked for safety:
	simple change: if(k+j>sentences[m][i].length()) continue;
	will work
	*/

	
	for(int m=0;m<sentences.size();++m)
	{
		for(int i=0;i<sentences[m].size();++i)
		{
			//strip nonLiteral characters which are at the end positions and if
			//any nonLiterals are still remaining discard the word
			int j=0;
			while(nonLiterals.find(sentences[m][i][j])!=-1)
			{
				++j;
				
			}
			int k=0;
			int len=sentences[m][i].length()-1;
			while((nonLiterals.find(sentences[m][i][len-k])!=-1) && k<len)
			{
				
				k++;
			}
			bool valid=true;
			string temp;
			if(k+j>sentences[m][i].length())
			{
				valid=false;
			}
			else
			{
				
				temp=sentences[m][i].substr(j,len-k-j+1);				
				for(int l=0;l<temp.length();++l)
				if(nonLiterals.find(temp[l])!=-1)
				{
					valid=false;
					break;
				}
			}
			if(!valid)
			{
				sentences[m].erase(sentences[m].begin()+i);
				--i;
				continue;
			}
			sentences[m].erase(sentences[m].begin()+i);
			
			sentences[m].insert(sentences[m].begin()+i,temp);

			


		//strip the characters following and includeing the character "'"
		
			int apsIndex;//index of ' character
			if((apsIndex=sentences[m][i].find('\''))!=-1)
			{
				if(apsIndex>0)
					sentences[m][i]=sentences[m][i].substr(0,apsIndex);
				else
				{
					sentences[m].erase(sentences[m].begin()+i);
					--i;
					continue;
				}
			}

			//separate a word in  parts from the position of character "/"
			int slashIndex;
			while((slashIndex=sentences[m][i].find('/'))!=-1)
			{
				if(slashIndex>0&&slashIndex<sentences[m][i].length()-1)
				{
					sentences[m].insert(sentences[m].begin()+i,sentences[m][i].substr(0,slashIndex));
					++i;
					sentences[m][i]=sentences[m][i].substr(slashIndex+1,sentences[m][i].length()-slashIndex);
				}
				else
				{
					if(slashIndex==0)
						sentences[m][i].erase(0,1);
					else
						sentences[m][i]=sentences[m][i].substr(0,sentences[m][i].length()-1);
				}
			}			
		}
		if(sentences[m].empty())
		{
			sentences.erase(sentences.begin()+m);
			--m;
		}
	}
}


	