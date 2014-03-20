// project.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "classifier.h"
//for training
#include "trainer.h"	
#include "learner.h"

int _tmain()
{
	//for learning
	/*Learner::initialize("transactions");
	Learner learner;
	string cls="entertainment";
	ifstream inFile1,inFile;
	inFile1.open(string("corpus\\"+cls+"\\index.txt").c_str());
	string line,text,indexLine;
	line="";
	text="";
	Classifier* classifier;
	Classifier::initialize("transactions");
	while(getline(inFile1,indexLine))
	{
		indexLine="corpus\\"+cls+"\\"+indexLine;
		inFile.open(indexLine.c_str());
		if(inFile==NULL)
			cout<<"error in opening email file"<<indexLine<<endl;		
		while(getline(inFile,line))
			text+=line+"\n";
			
		inFile.clear();
		inFile.close();
	}
	//cout<<text<<endl;
	cout<<"--------learning---------------------------------------------"<<endl;
	learner.learn(text,"hello",cls);
	inFile1.close();
	cout<<"learning complete"<<endl;

			



	//generate index file
/*	ofstream outFile,outFile1;
	outFile.open("corpus\\business\\index.txt");
	outFile1.open("corpus\\business\\testIndex.txt");
	if(outFile==NULL)
		cout<<"error"<<endl;
	for(int i=1;i<=200;++i)
		if(i%5==0||i%3==0)
			outFile1<<i<<endl;
		else
			outFile<<i<<endl;
	outFile.close();
	outFile1.close();
	*/
//test classification
	ifstream inFile1,inFile;
	string classes[]={"personal","business","entertainment"};
	string location,line,text,indexLine;
	Classifier* classifier;
	Classifier::initialize("transactions");
	ofstream outFile;
	for(int i=0;i<3;++i)
	{
		location="corpus\\"+classes[i]+"\\";
		outFile.open(string("corpus\\"+classes[i]+".dat").c_str());
		inFile1.open(string(location+"index.txt").c_str());
		
		while(getline(inFile1,indexLine))
		{
			indexLine=location+indexLine;
			inFile.open(indexLine.c_str());
			if(inFile==NULL)
				cout<<"error in opening email file"<<endl;
			text="";
			while(getline(inFile,line))
				text+=line+"\n";
			cout<<"classifying: "<<indexLine<<endl;
			classifier=new Classifier(text,"hello.");
			classifier->processEmail();
			string result=classifier->classify();
			if(result.compare("unclassified")==0)
			{
				outFile<<classifier->getSz()<<"\t"<<classes[i]<<"\t"<<0<<"\t"<<"unclassified"<<endl;
				inFile.clear();
				inFile.close();
				continue;
			}
			cout<<"classification result:"<<endl;
			vector<float> resultSet=classifier->getResult();
			for(int i=0;i<resultSet.size();++i)
				cout<<resultSet[i]<<endl;
			cout<<"decision: "<<result<<endl;
			cout<<"expected: "<<classes[i]<<endl;
			float deviation=resultSet[classifier->getResultClass()]-resultSet[i];
			cout<<"deviation: "<<deviation<<endl;
			//getch();
			outFile<<classifier->getSz()<<"\t"<<classes[i]<<"\t"<<resultSet[i]<<"\t"<<classes[classifier->getResultClass()]<<"\t"<<resultSet[classifier->getResultClass()]<<"\t"<<deviation<<endl;
			inFile.clear();
			inFile.close();
		}
		inFile1.clear();
		inFile1.close();
		outFile.clear();
		outFile.close();
	}
	
	
			
	// for training
	
	//Trainer trainer("transactions");
	//trainer.train();


	//for classification
/*	ifstream emailFile("corpus\\business\\.txt");
	if(emailFile==NULL)
		cout<<"error in opening file"<<endl;
	string text="";
	string email="";
	while(getline(emailFile,text))
	{
		email+=text;	
	}
*/
	
		
	
	getch();
	return 0;
}

