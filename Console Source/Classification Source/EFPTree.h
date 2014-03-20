/* This class is responsible for constructing EFPTree,extended FPTree,
from the given transaction database associated with the given set of classes
and mining strong association rules using EFPTree mining
*/
#ifndef FPTREEPHRASES_H
#define FPTREEPHRASES_H
#ifndef RULESTRUCTURES_H
#define RULESTRUCTURES_H
#include "rulestructures.h"
#endif
//#include "FPTreePhrases.h"
#endif
#include<memory.h>


class EFPTree{
private:
	static int classSize;
	static RuleTreeNode* root;
	static map< int,int* >messageArray;
	static map<int,int>supportMap;
	static map<int, RuleHeaderNode*>headerTable;//headerTable of the whole tree
	static int mina;//minimum absolute value for support
	static int D;//database length
	static float min_sup;//minimum value of support (sup/D);
	static float min_conf;
	static vector<vector<Rule*> > rules;//the rules generated from this tree
	int* sizes;//number of rules in each class
public:
	static RuleTreeNode* getRoot(){ return root;	}
	static map<int,RuleHeaderNode*>& getHeaderTable(){ return headerTable;	}
	void insertTransaction(vector<int> P,int cls,RuleTreeNode* root,map<int,RuleHeaderNode*>&,int);
	void efpGrowth(map< vector<int>,statistic*>* rulePattern,vector<int>pattern,RuleTreeNode* root,map<int,RuleHeaderNode*>& headerTable,map< vector<int>,int>&);
	void rankRules(map<vector<int>,statistic*>*rulePattern);
	vector< vector<Rule*> >& getRules();
	/* this initializes message array M[i,j] where M[i,j] denotes the
	value of term i for class j */
	static void initializeM(vector< vector< vector<int> > > database)
	{
		for(int i=0;i<database.size();++i)
		{
			for(int j=0;j<database[i].size();++j)
				for(int k=0;k<database[i][j].size();++k)
				{
					if(messageArray.find(database[i][j][k])!=messageArray.end())
						messageArray[database[i][j][k]][i]++;
					else
					{
						int * temp=new int[classSize];
						for(int l=0;l<classSize;++l)
							temp[l]=0;
						temp[i]=1;
						messageArray[database[i][j][k]]=temp;
					}
				}
		}
	}
	/* sort given items in support  asceding order,
	 the support used is the global support */
	static void sortAscending(vector<int>& items)
	{
		vector<int>frequentItems;//=items;
		for(int i=0;i<items.size();++i)
		{
			if(supportMap.find(items[i])==supportMap.end())
			{
				//erase the item that is not in the frequent items map
				//that is, the item that does not satisfy mina and min_sup
				items.erase(items.begin()+i);
				--i;
			}
		}
		while(items.size()>0)
		{
			int index=0;
			for(int i=1;i<items.size();++i)
				if(supportMap[items[i]]<supportMap[items[index]])
					index=i;
			frequentItems.push_back(items[index]);
			items.erase(items.begin()+index);
		}
		items=frequentItems;

	}
	/*initialize an EFPTree for a given transaction database of classes*/
	static void initialize(vector< vector < vector<int> > >database,int size)
	{
		
		//rules=new vector<Rule*>[classSize];
		classSize=size;
		mina=2;
		min_sup=0.000001;
		min_conf=0.002;
		D=0;
		initializeM(database);
		findFrequentItems();
		vector<int> frequentItems;
		for(map<int,int>::iterator itr=supportMap.begin();itr!=supportMap.end();++itr)
			frequentItems.push_back(itr->first);
		sortAscending(frequentItems);
		RuleHeaderNode::classSize=size;
		RuleTreeNode::classSize=size;
		root=new RuleTreeNode();
		for(int i=0;i<frequentItems.size();++i)
		{
			RuleHeaderNode* temp=new RuleHeaderNode();
			headerTable[frequentItems[i]]=temp;
		}

	}
	/* create global support map of items using messageArray */
	static void findFrequentItems()
	{
		map<int,int*>::iterator itr;
		for(itr=messageArray.begin();itr!=messageArray.end();++itr)
		{
			int* supports=itr->second;
			for(int i=0;i<classSize;++i)
				D+=supports[i];
		}
		for(itr=messageArray.begin();itr!=messageArray.end();++itr)
		{
			int* supports=itr->second;
			bool valid=false;
			for(int i=0;i<classSize;++i)
			{
				if(supports[i]>=mina&& supports[i]/(float)D>=min_sup)
				{
					valid=true;
					break;
				}
			}
			if(valid)
			{
				int sum=0;
				for(int i=0;i<classSize;++i)//find global support of item
					sum+=supports[i];
				supportMap[itr->first]=sum;
			}
		}

	}
};
float EFPTree::min_conf;
int EFPTree::classSize;
vector< vector<Rule*> > EFPTree::rules;
int EFPTree::D;
map<int,RuleHeaderNode*> EFPTree::headerTable;
map<int,int>EFPTree::supportMap;
map<int,int*>EFPTree::messageArray;
int EFPTree::mina;
float EFPTree::min_sup;
RuleTreeNode* EFPTree::root;
vector< vector<Rule*> >& EFPTree::getRules(){ return rules; }

void EFPTree::insertTransaction(vector<int> transaction,int cls,RuleTreeNode* alpha,map<int,RuleHeaderNode*>& headerTable,int sup)
{
	int current;	
	for(int i=0;i<transaction.size();++i)
	{
		current=transaction[i];
		map<int,RuleHeaderNode*>::iterator itr;
		itr=headerTable.find(current);
		if(itr==headerTable.end())
			continue;
		RuleHeaderNode* header=itr->second;
		(header->classSupport)[cls]+=sup;
		if(header->nodeLink==NULL)//no item with this id 
									//is inserted in the tree yet
		{
			RuleTreeNode* temp=new RuleTreeNode();
			temp->classSupport[cls]=sup;
			temp->itemId=current;
			temp->parent=alpha;
			header->nodeLink=temp;			
			alpha=temp;
			continue;
		}
		RuleTreeNode* previous;
		RuleTreeNode* next;
		previous=next=header->nodeLink;
		while(next!=NULL && next->parent!=alpha)
			next=next->nodeLink;
		if(next!=NULL)//inserting in the previously existing link
		{
			next->classSupport[cls]+=sup;
			alpha=next;
		}
		
		else
		{//link does not exist create new link
				RuleTreeNode* temp=new RuleTreeNode();
				temp->itemId=current;
				temp->parent=alpha;
				temp->classSupport[cls]=sup;
				previous->nodeLink=temp;
				alpha=temp;
		}
	}
	
}
void EFPTree::efpGrowth(map< vector<int>,statistic*>* rulePattern,vector<int>pattern,RuleTreeNode* root,map<int,RuleHeaderNode*>& headerTable,map< vector<int>,int>& frequentPattern)
{
	vector<int>frequentItems;
	vector<int>tempPattern;
	vector<RuleTreeNode*>nodes;
	map<int,RuleHeaderNode*>tempTable;
	map<int,RuleHeaderNode*>::iterator itr;
	for(itr=headerTable.begin();itr!=headerTable.end();++itr)
			frequentItems.push_back(itr->first);
	sortAscending(frequentItems);
	vector<int> tpt;
	vector<bool>validClasses;
	for(int i=0;i<frequentItems.size();++i)
	{
		tpt=pattern;
		tpt.insert(tpt.begin(),frequentItems[i]);
		//map<int,RuleHeaderNode*>::iterator itr;
		itr=headerTable.find(frequentItems[i]);
		if(itr==headerTable.end())
			continue;
		int* support=itr->second->classSupport;
		validClasses.clear();
		if(frequentPattern.find(tpt)==frequentPattern.end())
				continue;
		for(int j=0;j<classSize;++j)
		{
			
			float conf=support[j]/frequentPattern[tpt];
			
			if(support[j]>=mina && support[j]/(float)D>=min_sup)// && conf>=min_conf)
			{
				statistic* tempStat=new statistic();
				tempStat->count=support[j];
				tempStat->sup=support[j]/(float)D;
				tempStat->conf=conf;
				///currently conf value is not calculated;
				rulePattern[j][tpt]=tempStat;
				validClasses.push_back(true);
			}
			else
				validClasses.push_back(false);


		}
		tempTable.clear();
		nodes.clear();
		RuleTreeNode* tempRoot=new RuleTreeNode();
		vector<int>ptrn;
		RuleTreeNode* header=itr->second->nodeLink;
		while(header!=NULL )
		{
			nodes.push_back(header);
			header=header->nodeLink;
			//////cout<<"inside loop"<<endl;
		}
		//////cout<<"outside loop"<<endl;
		for(int j=0;j<nodes.size();++j)
		{
			ptrn.clear();
			RuleTreeNode* tempLink=nodes[j]->parent;
			while(tempLink!=NULL&& tempLink!=root)
			{
				ptrn.insert(ptrn.begin(),tempLink->itemId);
				tempLink=tempLink->parent;
			}
			for(int k=0;k<ptrn.size();++k)
			{
				if(tempTable.find(ptrn[k])!=tempTable.end())
					continue;
				{
					RuleHeaderNode* headerPtr=new RuleHeaderNode();
					tempTable[ptrn[k]]=headerPtr;
				}
			}
			for(int k=0;k<classSize;++k)
				if(validClasses[k])
					insertTransaction(ptrn,k,tempRoot,tempTable,nodes[j]->classSupport[k]);
			
		}
		if(tempTable.size()>0)
				efpGrowth(rulePattern,tpt,tempRoot,tempTable,frequentPattern);
	}
}

				




