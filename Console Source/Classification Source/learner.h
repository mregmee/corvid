
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include "preprocessor.h"
#endif
#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include "transactions.h"
#endif

class Learner
{
private:
	static string dataPath;
	
public:
	void learn(string email,string sub,string cls);
	static void initialize(string path)
	{
		dataPath=path;
	}
};
string Learner::dataPath;
void Learner::learn(string email,string sub,string cls)
{
	vector< vector<int> >transactionSet;
	transactionSet.clear();
	ofstream transactionFile((dataPath+"\\"+cls).c_str(),ios::app);
	Transactions transactions;
	Transactions::initialize(dataPath);
	PreProcessor *preProcessor=new PreProcessor(dataPath);		
	preProcessor->processEmail(email, sub);	
	transactions.createTransactions(preProcessor->getSentences(),preProcessor->getSubject(),transactionSet,true);
	Transactions::reset();	
	preProcessor->getSentences().clear();
	preProcessor->getSubject().clear();
	//cout<<"email processed"<<endl;
	transactionFile.seekp(transactionFile.end);
	transactionFile<<transactionSet.size()<<endl;
	for(int i=0;i<transactionSet.size();++i)
	{
		transactionFile<<transactionSet[i].size()<<endl;
		for(int j=0;j<transactionSet[i].size();++j)
		{
			transactionFile<<transactionSet[i][j]<<"\t";
		}
	}
	transactionFile.close();
}
	

	