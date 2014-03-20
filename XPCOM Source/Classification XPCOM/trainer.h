#ifndef FPTREEPATTERN_H
#define FPTREEPATTERN_H
#include "FPTreePattern.h"
#endif
#ifndef EFPTREE_H
#define EFPTREE_H
#include"EFPTree.h"
#endif
#ifndef RULEOPERATOR_H
#define  RULEOPERATOR_H
#include "ruleoperator.h"
#endif 
#include <conio.h>
class Trainer
{
private:
	//Preprocessor *preprocessor;
	//ifstream indexFile;
	string corpusLocation;
	map< vector<int>,int >frequentPattern;	
	map<int,string>classes;
	int classSize;
public:
	Trainer(string index);
	void train();
};
Trainer::Trainer(string index)
{
	corpusLocation=index;
	ifstream indexFile;
	//indexFile.open("corpus\\index.txt");
	indexFile.open((index+"\\index.txt").c_str());
	if(indexFile==NULL)
		return;
		//cout<<"error in opening file"<<endl;
	string emailFile;
	int i=0;
	while(getline(indexFile,emailFile))
	{
		//////cout<<emailFile<<endl;
		////getch();
		classes[i]=emailFile;
		i++;
	}
	classSize=classes.size();
}
void Trainer::train()
{
	/* debug 19th Dec,2007
	author Lekhnath
	we have used non literals removal, which worked for small size emails
	and failed in large emails: giving error "string subscript out of range"
	in fact this error came out to be from LexicalAnalyzer::eliminateNonLiterals function"
	*/
	map<int,string>::iterator classIterator;
	int classIndex;	
	vector< vector<int> >transactionSet;
	vector< vector< vector<int> > >transactionSets;
	ifstream transactionFile;
	vector<int>transaction;
	int tcount=0;
	int transactionSize=0;
	for(classIterator=classes.begin();classIterator!=classes.end();++classIterator)
	{
		transactionSet.clear();
		transactionFile.open((corpusLocation+"\\"+classIterator->second).c_str());
		if(transactionFile==NULL)
		{
			
			//cout<<"error in opening transactionfile   "<<classIterator->second<<endl;
			//getch();
		}
		
		while(transactionFile>>transactionSize)
		{
			for(int i=0;i<transactionSize;++i)
			{
				int size;
				int temp;
				transaction.clear();
				transactionFile>>size;
				//cout<<"Transaction "<<tcount++<<".  ";
				for(int j=0;j<size;++j)
				{
					transactionFile>>temp;
					//cout<<temp<<"\t";
					transaction.push_back(temp);
				}
				//cout<<endl;
				if(!transaction.empty())
					transactionSet.push_back(transaction);
			}
		}
		transactionFile.clear();//reading large file may reach end of stream
		transactionFile.close();	
		
		if(!transactionSet.empty())
			transactionSets.push_back(transactionSet);
		////getch();
		while(transactionFile.is_open());
		
	}
	


		FPTreePattern::initialize(corpusLocation);//initialize FPTree and HeaderTable for frequent patterns
		FPTreePattern fpTreePattern;
		//FPTreePhrase::initialize();
		//FPTreePhrase fpTreePhrase;
		int k=0;
		tcount=0;
		
		
		try
		{
			for(int j=0;j<transactionSets.size();++j)
			{
				for( k=0;k<transactionSets[j].size();k++)
				{
					
					
					
					//fpTreePhrase.insertTransaction(transactionSet[k],FPTreePhrase::getRoot(),FPTreePhrase::getHeaderTable(),1);
					fpTreePattern.insertTransaction(transactionSets[j][k],FPTreePattern::getRoot(),FPTreePattern::getHeaderTable(),1);//insert each transaction in database to tree
					//cout<<"inserting "<<tcount++<<endl;
				}
			}
			//cout<<"insertion complete"<<endl;
			
			
		}
		catch(...)
		{
			////cout<<"exception inside insert"<<endl;
			//////cout<<error.message();
		}
		//////cout<<"return safely from insert"<<endl;
		////getch();	
		
		//////cout<<"HeaderTable"<<endl;
		//FPTreePattern::displayTree();
		/*for(itr=aTable.begin();itr!=aTable.end();++itr)
		{
			////cout<<itr->first<<"\t"<<itr->second->itemSupport<<endl;
			
			
		}*/
		////getch();		
		vector<int>emptyVector;
		//////cout<<FPTreePattern::getRoot()<<endl;
		fpTreePattern.fpGrowth(FPTreePattern::getRoot(),FPTreePattern::getHeaderTable(),frequentPattern,emptyVector);
		//Transactions::clean();
		////getch();
		//cout<<"pattern generation complete"<<endl;
		map< vector<int>,int >::iterator patternItr;
		k=0;
		vector<int> pattern;
		//cout<<"Frequent patterns"<<endl;
		////getch();
		for(patternItr=frequentPattern.begin();patternItr!=frequentPattern.end();++patternItr)
		{
			//cout<<"pattern "<<k<<". ";
			pattern=patternItr->first;
			for(int m=0;m<pattern.size();m++)
				//cout<<pattern[m]<<"  ";
			//cout<<" :    "<<patternItr->second<<endl;
			k++;
		}
		
		////cout<<"rule construction:  "<<endl<<endl;
		

		
		EFPTree::initialize(transactionSets,classSize);
		//cout<<"initialized"<<endl;
		EFPTree efpTree;
		RuleTreeNode* ruleRoot=new RuleTreeNode();
		ruleRoot->itemId=0;
		for(int j=0;j<transactionSets.size();++j)
		{
			for(int i=0;i<transactionSets[j].size();++i)
			{
				efpTree.sortAscending(transactionSets[j][i]);
				efpTree.insertTransaction(transactionSets[j][i],j,EFPTree::getRoot(),EFPTree::getHeaderTable(),1);
				//efpTree.insertTransaction(transactionSet[i],1,EFPTree::getRoot(),EFPTree::getHeaderTable(),1);
			}
		}
		map< vector<int>,statistic*>* frequentRules=new map< vector<int>,statistic*>[classSize];
		vector<int>empty;
		//cout<<"rule insertion complete"<<endl;
		efpTree.efpGrowth(frequentRules,empty,EFPTree::getRoot(),EFPTree::getHeaderTable(),frequentPattern);
		
			
		}
		//cout<<"sorted rules"<<endl<<endl;
		RuleOperator ruleOperator(classSize,corpusLocation);
		ruleOperator.rankRules(frequentRules);
		ruleOperator.writeRules();
		ruleOperator.readRules();
		vector< vector<Rule*> > rules=ruleOperator.getRules();
		
}
