
#include "stdafx.h"

#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H
#include "FeatureExtractor.h"
#endif
#ifndef SENTENCEEXTRACTOR_H
#define SENTENCEEXTRACTOR_H
#include "SentenceExtractor.h"
#endif

class SummaryExtractor
{
private:
		string summary;
public:
	
	int findMaxImportance(vector<float>& importance);
	string getSummary(vector<float>& importanceVector,string pEmail, vector< vector<string> >& cnpList);
	bool sentenceNotIn(vector<string> tempSentenceVector,string impSentence);


};


	
      
    int SummaryExtractor:: findMaxImportance(vector<float>& importance)
    {
		float max=importance[0];
		int maxindx=0;
		int i=1;
		do
		{
			if(importance[i]>max){
				   max=importance[i];        
				   maxindx=i;
			}
		}while(++i<importance.size());
	    
		return maxindx;
    }
string SummaryExtractor:: getSummary(vector<float>& importanceVector,string pEmail, vector< vector<string> >& cnpList)
{
	  
		
	  string impSentence="";
	  string tempSentence;
	  vector<string> tempSentenceVector;
	  float sumPer=0.2;
	  int emailLength=pEmail.length();
	  int sumLength=(int)(sumPer*emailLength);
	  int length=0;
	  vector<string>nounPhraseVector;
	  vector<string>np;
	  for(int k=0;k<cnpList.size();++k)
	  {
		  np=cnpList[k];
		  
		   string nounphrase="";
               
           if(np.size()>1)
		   {
               int i;
               for(i=0;i<np.size()-1;i++)
			   {
                       nounphrase+=np[i]+" ";
               }
               //cout<<"nounphrase"<<nounphrase<<endl;
               nounphrase+=np[i];
           }
           else
               nounphrase+=np[0];
		   nounPhraseVector.push_back(nounphrase);
	  }
	  while(length<=sumLength)
	  {
	 // int noOfSentence=(int)(email.length()/50)+1;
	  //for(int i=0;i<noOfSentence;i++)
	  //{
	  int index=findMaxImportance(importanceVector);
	  string impNP = nounPhraseVector[index];
	  importanceVector[index]=-1.0;                   //to indicate the token is already extracted

      int sameTokensAhead = 0;
      for(int i=0;i<=index;i++){
		  if(strcmp(nounPhraseVector[i].c_str(),impNP.c_str())==0)
                                     sameTokensAhead++;}
      
	  tempSentence=SentenceExtractor::extractSentence(impNP,sameTokensAhead,pEmail);
	 if(sentenceNotIn(tempSentenceVector,tempSentence))
	 {
	 //tempSentence=impSentence;
	 tempSentenceVector.push_back(tempSentence);
     impSentence += tempSentence+"\n";
	 length = impSentence.length();
	 
	 }
	  
	   
	  }
	  tempSentenceVector.clear();
	  return impSentence;
      //cout<<"The important sentence is "<<impSentence;
}
bool SummaryExtractor:: sentenceNotIn(vector<string> tempSentenceVector,string impSentence)
{
	for(int i=0;i<tempSentenceVector.size();i++)
	{

		if(strcmp(impSentence.c_str(),tempSentenceVector[i].c_str())==0)
			return false;

	}
	return true;


}