
#ifndef SENTENCEEXTRACTOR_H
#define SENTENCEEXTRACTOR_H
#include "SentenceExtractor.h"
#endif
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include "PreProcessor.h"
#endif
#include "SummaryExtractor.h"


class EmailSummarizer
{
private:
	string pEmail;
	
public:
	EmailSummarizer(string txt);
	
	string summarizeEmail();

};
EmailSummarizer::EmailSummarizer(string txt)
	{
		pEmail = txt;
	}
string EmailSummarizer::summarizeEmail()
{
	PreProcessor preProcessor;
	preProcessor.processEmail(pEmail);
	cout<<"---------------------------------------------------------------------";
	cout<<"					PRE PROCESSED EMAIL"<<endl;
	cout<<"---------------------------------------------------------------------"<<endl;
	cout<<pEmail<<endl;
	getch();
		
		//char** t=preProcessor.getTokens();
	
	NounPhraseExtractor nounphraseextractor;
	vector< vector<string> > cnplist;
	nounphraseextractor.constructNPList(cnplist,pEmail);
	cout<<"---------------------------------------------------------------------";
	cout<<"					Candidate NounPhrase List"<<endl;
	cout<<"---------------------------------------------------------------------"<<endl;
	for(int i=0;i<cnplist.size();i++)
	{
		for(int j=0;j<cnplist[i].size();j++)
			cout<<cnplist[i][j]<<" ";
		cout<<endl;
	}
	getch();

	NounPhraseRanker npranker(cnplist,pEmail);
	vector<float> importanceVector;
	//npranker.createNeuralNet();
	npranker.processNPFeature(importanceVector);
	cout<<"---------------------------------------------------------------------";
	cout<<"				Importance Vector from Neural Network"<<endl;
	cout<<"---------------------------------------------------------------------"<<endl;
	for(int i=0;i<importanceVector.size();i++)
		cout<<importanceVector[i]<<endl;
	getch();
	SummaryExtractor summaryExtractor;
	cout<<"---------------------------------------------------------------------";
	cout<<"				Summarized Email"<<endl;
	cout<<"---------------------------------------------------------------------"<<endl;
	return summaryExtractor.getSummary(importanceVector,pEmail,cnplist);
	

}
