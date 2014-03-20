#include<vector>
#include<string>
#include"anntrainer.h"
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include "PreProcessor.h"
#endif
#ifndef DATAPATH_H
#define DATAPATH_H
#include "DataPath.h"
#endif
class SummarizationTrainer
{
private:
	vector< vector<float> >featureVector;
	vector< vector<string> > cnplist;
public:
	void extractNPFeature(string email);
	string getNP();	
	void train();
	void createSpecFile();
	void extraFunction();
};
void SummarizationTrainer::extractNPFeature(string email)
{
	PreProcessor preProcessor;
	preProcessor.processEmail(email);		
		//char** t=preProcessor.getTokens();	
	NounPhraseExtractor nounphraseextractor;
	
	nounphraseextractor.constructNPList(cnplist,email);
	FeatureExtractor* featureExtractor=new FeatureExtractor(email);
	featureExtractor->getFeatureVector(cnplist,featureVector);
}
void SummarizationTrainer::createSpecFile()
{
	string weightLocation=DataPath::dataPath+"\\weightFile";
	string nnFileLocation=DataPath::dataPath+"\\nnData.spec";

	ifstream weightFile(weightLocation.c_str());
	ofstream nnFile(nnFileLocation.c_str());
	//write premble for the spec file format
	nnFile<<"# parity.spec -- specification of input/target pairs for 5-bit parity\n# $Id: parity.spec,v 1.1 2003/10/07 22:41:32 petervr Exp $\n#\n# number of inputs\n9\n# number of outputs\n1\n# input & output\n";
	for(int i=0;i<featureVector.size();++i)
	{
		for(int j=0;j<featureVector[i].size();++j)
		{
			nnFile<<featureVector[i][j]<<" ";

		}
		nnFile<<endl;
		float temp;
		weightFile>>temp;
		nnFile<<temp<<endl;
	}
	nnFile.close();
	weightFile.close();
}

void SummarizationTrainer::train()
{
	ANNTrainer annTrainer;
	annTrainer.train();
}
void SummarizationTrainer::extraFunction()
{
	string weightFileLocation=DataPath::dataPath+"\\weightFile";
	ofstream outFile(weightFileLocation.c_str());
	float weight;
	for(int i=0;i<cnplist.size();++i)
	{
		for(int j=0;j<cnplist[i].size();++j)
		{
			cout<<cnplist[i][j]<<" ";
		}
		cout<<endl;
		cout<<"weight: ";
		cin>>weight;
		outFile<<weight<<"\t";
	}
	outFile.close();
}
