
#ifndef FPTREE_H
#define FPTREE_H
#include "FPTree.h"
#endif
class FPTreePhrase:public FPTree
{
private:
	static int mina;
	static float minSupport;
	static vector<int> frequentItems;
	static TreeNode *root;
	static int lmax;
	static map < int,HeaderNode* > mainHeaderTable;
public:
	static void initialize(string dataPath)
	{
		FPTree::initialize(dataPath);
		mina=3;
		minSupport=.01f;
		TreeNode* temp=new TreeNode();
		temp->itemId=0;
		temp->nodeLink=NULL;
		temp->parent=NULL;
		root=temp;
		FPTree::sortItemsAscending(FPTree::frequentItems,frequentItems);
		for(int i=0;i<frequentItems.size();++i)
		{
			HeaderNode *temp=new HeaderNode();
			temp->itemSupport=0;//itemSupportMap[frequentItems[i]];
			temp->nodeLink=0;
			mainHeaderTable[frequentItems[i]]=temp;
		//////cout<<temp->nodeLink<<endl;
		}
		

	}
	static TreeNode* getRoot(){ return root;}
	static map<int,HeaderNode*>& getHeaderTable(){	return mainHeaderTable;	}
	void insertTransaction(vector<int> transaction,TreeNode*,map<int,HeaderNode*>&,int);
	void fpGrowth(TreeNode*,map<int,HeaderNode*>&, map< vector<int>,int >&,vector<int>);
	void sortVectorForHeader(vector<int>&,map<int,HeaderNode*>&);
	bool isPruned(vector<int>,map< vector<int>, int >,int,int);
};
map<int,HeaderNode*> FPTreePhrase::mainHeaderTable;
TreeNode* FPTreePhrase::root;
int FPTreePhrase::mina=3;
int FPTreePhrase::lmax=3;
float FPTreePhrase::minSupport=0.03f;
vector<int> FPTreePhrase::frequentItems;
void FPTreePhrase::insertTransaction(vector<int> trans,TreeNode *alpha,map<int,HeaderNode*>& headerTable,int s){
	vector<int> transaction;
	FPTree::sortItemsAscending(trans,transaction);
	map<int,HeaderNode*>::iterator itr;	
	int current;
	for(int i=0;i<transaction.size();++i)
	{
		current=transaction[i];
		////cout<<"in inserting\t"<<current<<"  ";
		itr=headerTable.find(current);
		if(itr==headerTable.end())
		{//avoid processing of nonfrequent item
			//transaction.erase(transaction.begin()+0);
			////cout<<"not found"<<endl;
			continue;
			//break;//items are sorted in descending order of support, if this item 
					//doesn't satisfy the minimum support, the rest will not
		}
		//itr->second.itemSupport++;
		HeaderNode* header=itr->second;
		////cout<<header->nodeLink<<endl;
		//getch();
		if(header->itemSupport==0||header->nodeLink==NULL){//there is no previous entry of the item in tree
			TreeNode *temp=new TreeNode();
			////cout<<"just inserting  "<<current<<endl;
			temp->itemId=current;
			temp->nodeLink=0;
			temp->parent=alpha;
			temp->itemSupport=s;
			
			header->nodeLink=temp;
			////cout<<"temp constructed"<<endl;
			//getch();
			alpha=temp;
			//transaction.erase(transaction.begin()+0);
			//////cout<<"inserted  "<<headerTable[current]->nodeLink->itemId<<endl;
			header->itemSupport=s;
			//headerTable[current]=header;
			//getch();
			continue;
		}
		////cout<<"we are here"<<endl;
		TreeNode* previous=header->nodeLink;
		////cout<<previous<<endl;
		TreeNode* next=previous;
		while(next!=NULL && next->parent!=alpha){
			previous=next;
			next=next->nodeLink;
			////cout<<"inside loop"<<next<<endl;
			////cout<<alpha<<endl;
		}
		////cout<<"outside loop"<<endl;
		if(next==NULL){   ///if there is no child of the node alpha whose id is item, so we need to create new node for that item
			TreeNode* temp=new TreeNode();
			////cout<<"just inserting here "<<current<<endl;
			temp->itemId=current;
			temp->nodeLink=NULL;
			temp->parent=alpha;
			temp->itemSupport=s;
			previous->nodeLink=temp;
			alpha=temp;
			//transaction.erase(transaction.begin());
			header->itemSupport+=s;
			////cout<<"inserted here  "<<current;
			continue;
			
		}
		////cout<<"next is not null"<<endl;
		(header->itemSupport)+=s;
		next->itemSupport+=s;/// a child of alpha whose itemid is item, so we nee not create new node rather update support 
		alpha=next;
		//transaction.erase(transaction.begin());
	}
	////cout<<"outside insert"<<endl;
	////cout<<"all done inside insert"<<endl;
	//transaction.clear();
	//getch();
	//exit(0);
	//return;
}
void FPTreePhrase::fpGrowth(TreeNode* alpha,map<int,HeaderNode*>& headerTable,map< vector<int>,int >&F,vector<int>tempPattern){
	vector<int>termVectorForHeader;
	map<int,HeaderNode*>tempTable;
	//map<int,HeaderNode>tempTable1;
	vector< vector<int> >tempPatterns;
	vector<int>pattern;
	//tempTable=headerTable;
	//TreeNode* alpha=root;
	//vector<int>termVectorForHeader1;
	
	//vector<int> tempPattern;
	vector<TreeNode*> nodes	;
	vector<int> supports;
	map< vector<int>,int>::iterator patternIterator;
	
	sortVectorForHeader(termVectorForHeader,headerTable);
	////cout<<"sorted"<<endl;
	vector<int>tpt;
	////cout<<termVectorForHeader.size()<<endl;
	cout<<"whole table"<<endl;
	for(int i=0;i<termVectorForHeader.size();++i)
		cout<<termVectorForHeader[i]<<"\t"<<headerTable[termVectorForHeader[i]]->itemSupport<<endl;
	for(int i=0;i<termVectorForHeader.size();++i)
	{
		
		//tempPattern.clear();
		
		tpt=tempPattern;		
		tpt.insert(tpt.begin(),termVectorForHeader[i]);
		int support=headerTable[termVectorForHeader[i]]->itemSupport;
		
		if(support<mina){//||support/(float)D<minSupport)
			//cout<<"ignored: "<<termVectorForHeader[i]<<endl;
			continue;
		}
		/*if(tempPattern.size()>=2)
		{
			if(isPruned(tempPattern,F,termVectorForHeader[i],support))
				continue;
			if(!tempPattern.empty())
			{
				patternIterator=F.find(tempPattern);
				if(tempPattern.size()>=2)
				{
					if(patternIterator==F.end())
						break;//if a pattern does not satisfy the conditions, then none of its 
							 //super phrases will
				
					//if(support>patternIterator->second)
						//continue;//if any of Spn-1 has less value of den(refer the algorithm in doc)
							//then prune the phrase Pn and all its super phrases
				}
			}
		}*/
		//////cout<<"before headerTable access"<<endl;
		if(2<=tpt.size()&& tpt.size()<=lmax)
			F[tpt]=support;
		//tempPattern.insert();
		//frequentPattern.push_back(tempPattern);
		//tempPattern.clear();
		
		TreeNode *next=headerTable[termVectorForHeader[i]]->nodeLink;
		nodes.clear();
		supports.clear();
		while(next!=NULL)
		{
			nodes.push_back(next);
			next=next->nodeLink;
		}
		tempPatterns.clear();
		tempTable.clear();
		
		
		for(int k=0;k<nodes.size();++k)
		{
			pattern.clear();
			int s=0;
			TreeNode* parent=nodes[k]->parent;
			while(parent!=alpha && parent->itemId!=0)
			{
				
				s=parent->itemSupport;
				//if(s<mina)
					//break;
				pattern.insert(pattern.begin(),parent->itemId);
				parent=parent->parent;
			}
			if(!pattern.empty())
			{
				supports.push_back(s);//(headerTable[pattern[0]]->itemSupport);
				tempPatterns.push_back(pattern);
			}
		}
		////cout<<"patterns constructed"<<endl;
		for(int k=0;k<tempPatterns.size();++k)//construct headerTable for conditional tree
		{
			for(int l=0;l<tempPatterns[k].size();++l)
			{
				if(tempTable.find(tempPatterns[k][l])!=tempTable.end())
					continue;//tempTable[tempPatterns[k][l]]->itemSupport++;
				else
				{
					HeaderNode* tempHeaderNode=new HeaderNode();
					tempHeaderNode->nodeLink=NULL;
					tempHeaderNode->itemSupport=0;
					//tempHeaderNode.nodeLink=NULL;
					tempTable[tempPatterns[k][l]]=tempHeaderNode;
				}
			}
		}
		////cout<<"tempTable constructed"<<endl;
		//getch();


		TreeNode* tempRoot=new TreeNode();
		tempRoot->itemId=0;
		tempRoot->nodeLink=NULL;
		tempRoot->parent=NULL;
		for(int k=0;k<tempPatterns.size();++k)//construct conditional tree
		{
			insertTransaction(tempPatterns[k],tempRoot,tempTable,nodes[k]->itemSupport);
		}
		////cout<<"insertion complete in fpGrowth"<<endl;
		//getch();
		map<int,HeaderNode*>::iterator itr=tempTable.begin(),tempItr;
		for(;itr!=tempTable.end();++itr)
		{
			if(!(itr->second->itemSupport>mina))
			{
				tempItr=itr;				
				++itr;
				if(itr==tempTable.end())
					break;
				tempTable.erase(tempItr);
			}
				
		}
		if(tempTable.size()>1)
			fpGrowth(tempRoot,tempTable,F,tpt);
	}
		/*
		termVectorForHeader1.clear();
		
		do{

			sortVectorForHeader(termVectorForHeader1,tempTable);
			for(int j=0;j<termVectorForHeader1.size();++j)
			{
				tempPattern.clear();
				
				tempPattern.clear();
				next=tempTable[termVectorForHeader1[j]].nodeLink;
				nodes.clear();		
				while(next!=NULL)
				{
					nodes.push_back(next);
					next=next->nodeLink;
				}
				tempPatterns.clear();
				tempTable1.clear();
				
				for(int k=0;k<nodes.size();++k)
				{
					pattern.clear();
					TreeNode* parent=nodes[k]->parent;
					while(parent!=alpha)
					{
						pattern.push_back(parent->itemId);
						parent=parent->parent;
					}
					tempPatterns.push_back(pattern);
				}
				for(k=0;k<tempPatterns.size();++k)//construct headerTable for conditional tree
				{
					for(int l=0;l<tempPatterns.size();++l)
					{
						if(tempTable.find(tempPatterns[k][l])!=tempTable.end())
							tempTable[tempPatterns[k][l]].itemSupport++;
						else
						{
							HeaderNode tempHeaderNode;
							tempHeaderNode.itemSupport=1;
							tempHeaderNode.nodeLink=NULL:
							tempTable[tempPatterns[k][l]=tempHeaderNode;
						}
					}
				}
				TreeNode tempRoot;
				tempRoot.itemId=0;
				tempRoot.nodeLink=NULL;
				tempRoot.parent=NULL:
				for(k=0;k<tempPatterns.size();++k)//construct conditional tree
				{
					insertTransaction(tempPatterns[k],&tempRoot,tempTable);
				}
				alpha=&tempRoot;

			*/





	


	



}
void FPTreePhrase::sortVectorForHeader(vector<int>& termVectorForHeader,map<int,HeaderNode*>& headerTable){

map<int,HeaderNode*>::iterator itr;
//	vector<int>termVectorForHeader;
	for(itr=headerTable.begin();itr!=headerTable.end();++itr){
		if(itr->second->nodeLink==NULL)
			continue;
		termVectorForHeader.push_back(itr->first);
	}
	vector<int>sortedVector;
	int index=0;
	while(termVectorForHeader.size()>0){
		index=0;
		for(int i=1;i<termVectorForHeader.size();++i)
			if(headerTable[termVectorForHeader[i]]->itemSupport>headerTable[termVectorForHeader[index]]->itemSupport)
				index=i;//here we are sorting in suport descending order since we are 
						//starting from the most frequent pattern in FPgrowth
		sortedVector.push_back(termVectorForHeader[index]);
		termVectorForHeader.erase(termVectorForHeader.begin()+index);
	}
	termVectorForHeader=sortedVector;


}
bool FPTreePhrase::isPruned(vector<int>subPattern,map< vector<int>, int >F,int w,int support)
{
	return false;
}
