#include "FilterTest.h"

using namespace filterspace;

class UpdateFilterKnowledge: public EmailFunctions
{
      private:
              static map<string,int>hamMap;
              static map<string,int>spamMap;
              static map<string,float>knowledgebase;
              static const char* dataLocation;
              static string KBLocation;//=string(dl)+"\\knowledgebase.txt";
              static string hamLocation;//=string(dl)+"\\hamMap.txt";
              static string spamLocation;//=string(dl)+"\\spamMap.txt";
              static int ngood;
              static int nbad;
			  static int hamBias;
              static string counterLocation;
              static int frequencyThreshold;
              inline float max(float x,float y){return (x>y) ?  x : y;}
              inline float min(float x,float y){ return (x>y)? y : x;}
              map<string,int>tempHam;
              map<string,int>tempSpam;
              static bool hamUpdated;
              static bool spamUpdated;
              
              
      public:
             static void initialize(const char *dl){
                    dataLocation=dl;
                    string KBLocation=string(dl)+"\\knowledgebase.txt";
                    string hamLocation=string(dl)+"\\hamMap.txt";
                    string spamLocation=string(dl)+"\\spamMap.txt";
                    loadFile(hamMap,hamLocation.c_str());
                    loadFile(spamMap,spamLocation.c_str());
                    loadFile(knowledgebase,KBLocation.c_str());
                    hamBias=2;
                    frequencyThreshold=15;             
                    
                    counterLocation=string(dataLocation)+"\\counter.txt";
                    ifstream inFile(counterLocation.c_str());
                    if(inFile==NULL)
                    {
                     //cout<<"error in reading counterFile "<<endl;
                     //getch();
                     }
     
                    string line;
                    inFile>>line;
                    inFile>>ngood;
                    inFile>>line;
                    inFile>>nbad;
                    //cout<<"ngood: "<<ngood<<endl;
                    //cout<<nbad<<endl;
					hamUpdated=false;
                    spamUpdated=false;
                    
             }
             
             void markEmails(const char * emails,const char* status);
             void updateProbability();
             void clean();
};

map<string,int>UpdateFilterKnowledge::hamMap;
map<string,int>UpdateFilterKnowledge::spamMap;
map<string,float>UpdateFilterKnowledge::knowledgebase;
string UpdateFilterKnowledge::KBLocation;
string UpdateFilterKnowledge::spamLocation;
string UpdateFilterKnowledge::hamLocation;
int UpdateFilterKnowledge::frequencyThreshold=15;
string UpdateFilterKnowledge::counterLocation;
const char* UpdateFilterKnowledge::dataLocation;
int UpdateFilterKnowledge::ngood;
int UpdateFilterKnowledge::nbad;
bool UpdateFilterKnowledge::spamUpdated;
bool UpdateFilterKnowledge::hamUpdated;
int UpdateFilterKnowledge::hamBias;


void UpdateFilterKnowledge::clean(){
     
         if(spamUpdated){
         createKnowledgeFromTokens(tempSpam,spamMap);
        // serializeMap(spamLocation.c_str(),spamMap);
         }
      if(hamUpdated){
         createKnowledgeFromTokens(tempHam,hamMap);
        // serializeMap(hamLocation.c_str(),hamMap);
         }
      updateProbability();
      //serializeMap(KBLocation.c_str(),knowledgebase);
      
      knowledgebase.clear();
      hamMap.clear();
      spamMap.clear();
      tempHam.clear();
      tempSpam.clear();
      ofstream out(counterLocation.c_str());
      out<<"nGood\t"<<ngood<<"\n"<<"nBad\t"<<nbad<<"\n";
      out.close();
}

void UpdateFilterKnowledge:: markEmails(const char*emailFile,const char* status){
     map<string,int>tokenMap;     
     map<string,string>email;
     tokenMap.clear();
     
    // for(int i=0;i<emailCount;++i){
             scanEmail(email,emailFile);
             if(email.find("error")!=email.end())
                return;
                //continue;//error in reading email
             createTokenMap(email,tokenMap);
             if(strcmp(status,"ham")==0){
               //cout<<status<<endl;
                createKnowledgeFromTokens(tokenMap,tempHam);
                hamUpdated=true;
                ngood++;
                }
             else{
                  createKnowledgeFromTokens(tokenMap,tempSpam);
                  spamUpdated=true;
                  nbad++;
                  }
             tokenMap.clear();
    // }
    // initialize("c:\\data");
   // map<string,int>::iterator itr=tempHam.begin();
   // for(;itr!=tempHam.end();++itr){
                                // cout<<itr->first<<endl;
                               //  cout<<itr->second<<endl;
                               //  }
    
}
void UpdateFilterKnowledge::updateProbability(){
     map<string,int>::iterator mapIterator,tempIterator;     
     float tokenProbability;
     //map<string,float>::iterator knowledgeIterator;
     for(mapIterator=tempHam.begin();mapIterator!=tempHam.end();++mapIterator){
          float g=0,b=0;
          //if((tempIterator=tempSpam.find(mapIterator->first))!=tempSpam.end())
            // tempSpam.erase(tempIterator);
          if((tempIterator=spamMap.find(mapIterator->first))!=spamMap.end())
           b=tempIterator->second;
          g=hamMap[mapIterator->first];
          g*=hamBias;
         //cout<<"g  "<<g<<"b:  "<<b<<endl;
          if(g+b>frequencyThreshold) 
               tokenProbability=max(0.01f,min(0.999f,min(b/nbad,1.0f)/(min(b/nbad,1.0f)+min(g/ngood,1.0f))));                     
           else         
              continue;
            //cout<<"token\t"<<mapIterator->first<<"previous prob:  "<<knowledgebase[mapIterator->first]<<"\tupdated prob:  "<<tokenProbability<<endl;
            //getch();
          knowledgebase[mapIterator->first]=tokenProbability;
         }
         
         
        for(mapIterator=tempSpam.begin();mapIterator!=tempSpam.end();++mapIterator){
            float g=0,b=0;
            if((tempIterator=hamMap.find(mapIterator->first))!=hamMap.end())
            g=tempIterator->second;
            g*=hamBias;
            b=spamMap[mapIterator->first];
           // cout<<"gb:   "<<g+b<<endl;
            if(g+b>frequencyThreshold) 
                tokenProbability=max(0.01f,min(0.999f,min(b/nbad,1.0f)/(min(b/nbad,1.0f)+min(g/ngood,1.0f))));                      
             else         
                continue;
             //cout<<"token\t"<<mapIterator->first<<"previous prob:  "<<knowledgebase[mapIterator->first]<<"\tupdated prob:  "<<tokenProbability<<endl;
             //getch();
             knowledgebase[mapIterator->first]=tokenProbability;
         }
      }

        
  
       
           
    
     
        
