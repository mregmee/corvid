// project.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "classifier.h"
//for training
//#include "trainer.h"
//#include<conio.h>
	
//#include "learner.h"

int _tmain()
{
	//for learning
	/*Learner::initialize("transactions");
	Learner learner;
	string cls="personal";
	ifstream inFile;
	inFile.open("corpus\\personal.txt");
	string line,text;
	line="";
	text="";
	while(getline(inFile,line))
		text+=line+"\n";
	vector< vector<int> >transactionSet;
	learner.learn(text,"hello","personal");
	inFile.close();
	while(inFile);
	ifstream iFile("corpus\\business.txt");
	if(iFile==NULL)
		cout<<"error"<<endl;

	text="";
	line="";
	while(getline(iFile,line))
		text+=line+"\n";
	learner.learn(text,"hello","business");
	iFile.close();
	

	*/
	ifstream emailFile("corpus\\business.txt");
	if(emailFile==NULL)
		cout<<"error in opening file"<<endl;
	string text="";
	string email="";
	while(getline(emailFile,text))
	{
		email+=text;	
	}

	Classifier::initialize("transactions");
	Classifier classifier(email,"hello.");
	classifier.processEmail();
	float * result=classifier.classify();
	cout<<"classification"<<endl<<endl;
	for(int i=0;i<2;++i)
		cout<<result[i]<<endl;
		
		
	// for training
	//Trainer trainer("transactions");
	//trainer.train();
	
	getch();
	return 0;
}

