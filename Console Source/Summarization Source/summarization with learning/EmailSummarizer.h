
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
		
		//char** t=preProcessor.getTokens();
	
	NounPhraseExtractor nounphraseextractor;
	vector< vector<string> > cnplist;
	nounphraseextractor.constructNPList(cnplist,pEmail);
	NounPhraseRanker npranker(cnplist,pEmail);
	vector<float> importanceVector;
	//npranker.createNeuralNet();
	npranker.processNPFeature(importanceVector);
	SummaryExtractor summaryExtractor;
	return summaryExtractor.getSummary(importanceVector,pEmail,cnplist);
	

}
