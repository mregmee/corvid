#ifndef RULESTRUCTURES_H
#define RULESTRUCTURES_H
#include "rulestructures.h"
#endif

#include<vector>
#include<fstream>
using namespace std;
class RuleOperator
{
	static string ruleLocation;
	static vector< vector<Rule*> >rules;
	static int classSize;
public:
	void rankRules(map<vector<int>,statistic*>*rulePattern);
	void writeRules();
	void readRules();
	void pruneRules();
	RuleOperator(int size,string dataPath);
	vector< vector<Rule*> >&getRules();
};
int RuleOperator::classSize;
string RuleOperator::ruleLocation;
vector< vector<Rule*> >RuleOperator::rules;
RuleOperator::RuleOperator(int size,string dataPath)
{
	classSize=size;
	ruleLocation=dataPath+"\\rules.txt";
}
void RuleOperator::rankRules(map< vector<int>,statistic*>*rulePatterns)
{
	//rules is a multidimensional array, we use array since we have fixed number of rules

	//debug-----------------------------//
	/*---author lekhnath
	date:8th dec,2007*/
	/* the number of rules can though be fixed before sorting, the length
	of pattern in each rule varies, this forces us use vector for representing 
	rules for a class as a vector,
	The number of class is fixed however the requirement of using rules in 
	vector forces us, in the same way as before, to use two dimensional
	array of vector for representation of rules
	---> all this arises because if we use array,contiguous memory is used
	so different sizes for each element can not be used,i.e. an element of
	array can not be vector of objects that has vector as a member*/

	int size;
	int* sortedIndex;
	bool swap;//whether swapping is necessary or not
	map< vector<int>,statistic* >::iterator itr;
	vector<Rule*> tempRules;
	vector<Rule*>sortedRules;
	for(int i=0;i<classSize;++i)
	{
		
		size=rulePatterns[i].size();
		sortedIndex=new int[size];
		tempRules.clear();
		sortedRules.clear();		
		for(itr=rulePatterns[i].begin();itr!=rulePatterns[i].end();++itr)
		{
			
			
			Rule* tempRule=new Rule();
			tempRule->pattern=itr->first;
			tempRule->stat=*itr->second;
			tempRules.push_back(tempRule);		

		}
		//now sort the rules array according rule ranking algorithm by bubble sort
		//first find the indices of the given vector that has element in the
		//sorted order, then push the element in that order
	
		for(int j=0;j<size;++j)
		{
			sortedIndex[j]=j;
		}
		for(int j=0;j<size;++j)
		{
			
			for(int k=j+1;k<size;++k)
			{
				
				if(tempRules[sortedIndex[j]]->stat.count<tempRules[sortedIndex[k]]->stat.count)
				{
					int temp=sortedIndex[k];
					sortedIndex[k]=sortedIndex[j];
					sortedIndex[j]=temp;
				}
				
				else if(tempRules[sortedIndex[j]]->stat.count==tempRules[k]->stat.count)
				{
					//write here for rule cohesion
					//lengthy pattern given priority
					if(tempRules[sortedIndex[j]]->pattern.size()<tempRules[k]->pattern.size())
					{
						int temp=sortedIndex[k];
						sortedIndex[k]=sortedIndex[j];
						sortedIndex[j]=temp;
					}
				}
			}
		}
		for(int j=0;j<size;++j)
		{
			sortedRules.push_back(tempRules[sortedIndex[j]]);
		}
	
		rules.push_back(sortedRules);
	}
	
}
vector< vector<Rule*> >& RuleOperator::getRules()
{
	return rules;
}
void RuleOperator::writeRules()
{
	ofstream outFile(ruleLocation.c_str());
	outFile<<rules.size()<<endl;
	for(int i=0;i<rules.size();++i)
	{
		outFile<<rules[i].size()<<endl;
		for(int j=0;j<rules[i].size();++j)
		{
			outFile<<rules[i][j]->stat.count<<endl;
			outFile<<rules[i][j]->stat.sup<<endl;
			outFile<<rules[i][j]->stat.conf<<endl;
			vector<int>pattern=rules[i][j]->pattern;
			outFile<<pattern.size()<<endl;
			
			for(int k=0;k<rules[i][j]->pattern.size();++k)
				outFile<<pattern[k]<<"\t";
		}
	}
}
void RuleOperator::readRules()
{
	rules.clear();
	
	ifstream inFile(ruleLocation.c_str());
	
	inFile>>classSize;
	
	vector < Rule* > tempRules;
	Rule * rule;
	vector<int>pattern;
	
	for(int i=0;i<classSize;++i)
	{
		int size;
		inFile>>size;
		for(int j=0;j<size;++j)
		{
			statistic* stat=new statistic();
			inFile>>stat->count;
			inFile>>stat->sup;
			inFile>>stat->conf;
			int temp;
			
			
			int ptSize;			
			inFile>>ptSize;
			pattern.clear();
			for(int k=0;k<ptSize;++k)
			{
				inFile>>temp;
				pattern.push_back(temp);
			}
			rule=new Rule();
			rule->pattern=pattern;
			pattern.clear();
			rule->stat=*stat;
			tempRules.push_back(rule);
			
		}
		rules.push_back(tempRules);
		tempRules.clear();
	}
	
}
