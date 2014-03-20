#include "EmailFunctions.h"
#include<math.h>

using namespace filterspace;

class FilterTest: public EmailFunctions
{
      private:
        static  string knowledgebaseLocation;
        const char *emailFile;
        float midProbability;
        int maxTokensConsidered;
        float spamThreshold;
        map<string,string>email;
        static map<string,float>knowledgebase;
        map<string,float>emailTokens;
        vector<float>interestingTokens;
      public:

	
		static void FilterTest::initializeFilter(const char* kBLocation){
			 knowledgebaseLocation=string(kBLocation)+"\\knowledgebase.txt";
			 loadFile(knowledgebase,knowledgebaseLocation.c_str());
			 readStopWords();  
			 setStopWordsLocation(kBLocation);
		}  

        FilterTest(const char *);
		FilterTest(){}
        void setEmailLocation(const char *);
        void clean();
        void constructEmailTokens();
        void selectInterestingTokens();
        float predictEmail();
      //  static void initializeFilter(char* kBLocation);        
        float combinedProbability();
};
map<string,float>FilterTest::knowledgebase;
string FilterTest::knowledgebaseLocation="";
void FilterTest::clean(){
     emailTokens.clear();
     interestingTokens.clear();
     email.clear();
     
     }
     
FilterTest::FilterTest(const char * file){
     emailFile=file;
     maxTokensConsidered=15;
     midProbability=0.4;
     spamThreshold=0.98;
}
void FilterTest::setEmailLocation(const char * file){
     emailFile=file;
}


void FilterTest::constructEmailTokens(){
     scanEmail(email,emailFile);
     map<string,string>::iterator emailIterator;
     if((emailIterator=email.find("error"))!=email.end()){
       // cout<<"error in reading file"<<endl;
        return;
        }
        
     map<string,int>tempTokens;
     createTokenMap( email,tempTokens);
     map<string,int>::iterator itr;
     float probabilityValue;
     for(itr=tempTokens.begin();itr!=tempTokens.end();++itr){
         string tempToken=itr->first;
         map<string,float>::iterator searchPtr=knowledgebase.find(tempToken);
         if(searchPtr==knowledgebase.end()||searchPtr->second==0)
             probabilityValue=midProbability;
         else
             probabilityValue=searchPtr->second;
         emailTokens[tempToken]=probabilityValue;
     }
}

float FilterTest::predictEmail()
{
    selectInterestingTokens();
    return combinedProbability();
    //cout<<"Probability of being spam : ";
    //cout<<probability<<endl;
   /* if(probability>=spamThreshold)
       return true;
    else
        return false;*/
}
void FilterTest::selectInterestingTokens(){
     map<string,float>::iterator itr=emailTokens.begin();
     map<string,float>::iterator tempItr;
     int i=0;     
     for(;itr!=emailTokens.end();++itr){
                                 interestingTokens.push_back((float)itr->second);
                               // cout<<itr->second<<endl;
                                //getch();
                                 }
     for(int i=0;i<maxTokensConsidered;++i){
       for(int j=interestingTokens.size()-1;j>i;--j)
          if(fabs(interestingTokens[i]-0.5)<fabs(interestingTokens[j]-0.5)){
                                          float temp=interestingTokens[j];
                                          interestingTokens[j]=interestingTokens[i];
                                          interestingTokens[i]=temp;
                                          //tempItr->second=temp;
           }
            //cout<<interestingTokens[i]<<endl; 
            }
      
      
      interestingTokens.resize(maxTokensConsidered);
}
float FilterTest::combinedProbability(){
      float num=1,den=1;
     
      
      //cout<<"token probability of file    "<<string(emailFile)<<endl;
      for(int i=0;i<interestingTokens.size();++i){
        // cout<<interestingTokens[i]<<endl;                                                               
         num*=interestingTokens[i];
         den*=1-interestingTokens[i];
                  
         }         
      return num/(num+den);
}
      


     
