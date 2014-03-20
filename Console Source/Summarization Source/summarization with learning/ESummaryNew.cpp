// ESummaryNew.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>


#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "Tokenizer.h"
#endif

#ifndef POSTAGGER_H
#define POSTAGGER_H
#include "Postagger.h"
#endif

#include "NounPhraseExtractor.h"

#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H
#include "FeatureExtractor.h"
#endif

#include "NounPhraseRanker.h"

#ifndef SENTENCEEXTRACTOR_H
#define SENTENCEEXTRACTOR_H
#include "SentenceExtractor.h"
#endif
#ifndef POSTAGGER_H
#define POSTAGGER_H
#include "postagger.h"
#endif


#include "EmailSummarizer.h"
#ifndef DATAPATH_H
#define DATAPATH_H
#include "DataPath.h"
#endif
#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H
#include "DataPath.h"
#endif
#ifndef HTMLPARSER_H
#define HTMLPARSER_H
#include "HtmlParser.h"
#endif
#include "summarizationtrainer.h"

using namespace std;

int main(int argc, char* argv[])
{
	string email="";
	DataPath::dataPath = "C:\\Documents and Settings\\mregmee\\Desktop\\complete\\e-summarication\\data";	
	Postagger::loadTagmap();
	string counterPath=DataPath::dataPath+"\\documentcounter.dat";
		ifstream counterFile(counterPath.c_str());
	counterFile>>DataPath::noOfDocuments;
	//cout<<DataPath::noOfDocuments;
	//getch();
	counterFile.close();
	FeatureExtractor::loadStfile();
	string ePath = DataPath::dataPath +"\\email.txt";
	ifstream ifile(ePath.c_str());
    string temp="";
    while(getline(ifile,temp))
        email=email+temp+"\n";
	
	string parsedEmail=parseEmail(email);
	SummarizationTrainer sTrainer;
	sTrainer.extractNPFeature(parsedEmail);
	sTrainer.extraFunction();
	sTrainer.createSpecFile();
	sTrainer.train();
	//cout<<parsedEmail<<endl;
	//getch();
	//cout<<"after parsed email"<<endl;
	EmailSummarizer emlsmr(parsedEmail);
	cout<<emlsmr.summarizeEmail();
	FeatureExtractor::writeStfile();
	getch();

	return 0;
}

