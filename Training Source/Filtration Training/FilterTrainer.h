#include "EmailFunctions.h"
#include "xmlParser.h"
#include "Tokenizer.h"
//#include "stlsl.h"
using namespace filterspace;

class FilterTrainer:public EmailFunctions
{
 private:
         string corpusLocation;
         char* corpusIndexLocation;         
         map<string,int>hamMap;
         map<string,int>spamMap;
         map<string,float>knowledgebase;
         int frequencyThreshold;
         int hamBias;
         char* spamMapLocation;
         char* hamMapLocation;
         char* knowledgebaseLocation;
         vector<string>stopWords;
         float ignoringProbability;
         int ngood;
         int nbad;
         char* stopWordsLocation;
 public:
        FilterTrainer(char * contextLocation);
        void trainFromCorpus();
        void updateKnowledgeMap(string status,map<string,int>tokens);
        void createTokenMap(map<string,string>header,map<string,int>& tokens);
        void createKnowledgebase();
        void calculateProbability();
        void pruneKnowledgeMaps();
        void trim(string &token);
        void readStopWords();
        inline float max(float x,float y) { return (x>y)?x:y; }            
        inline float min(float x,float y){ return (x<y)?x:y;  }
           
               
};
FilterTrainer::FilterTrainer(char* contextLocation){
       corpusIndexLocation="C:\\Documents and Settings\\prashrestha\\Desktop\\trec05p-1\\full\\index";
       corpusLocation="C:\\Documents and Settings\\prashrestha\\Desktop\\trec05p-1";
       frequencyThreshold=5;
       hamBias=2;
       spamMapLocation="..\\spamMap.txt";
       hamMapLocation="..\\hamMap.txt";
       knowledgebaseLocation="..\\knowledgebase.txt";
       stopWordsLocation="C:\\Documents and Settings\\prashrestha\\Desktop\\Trainermodule\\stopwords.txt";
       readStopWords();
       ignoringProbability=0.1;
       ngood=0;
       nbad=0;
       
       
}                       
void FilterTrainer::readStopWords(){
    ifstream stopwordsFile; 
    stopwordsFile.open(stopWordsLocation);
    string line;
    if(stopwordsFile==NULL){
        cout<<"error in reading stopWords file"<<endl;
        getch();
        return ;
    } 
    while(getline(stopwordsFile,line)!=NULL)
          stopWords.push_back(line);
}  
 
                

    
                                 
                                   
                               
void FilterTrainer::trainFromCorpus(){
    ifstream inFile;
    inFile.open(corpusIndexLocation);
    if(inFile==NULL){
                     cout<<"error in opening index file";
                     getch();                     
                     }
    string status;
  
    int counter=0;
    while((inFile>>status)!=NULL){
       
      string path;   
      inFile>>path;    
      int slash=0;   
      while((slash=path.find("/",slash))!=-1){  
       string slashchar="\\";
       path[slash]='\\';
       path.insert(slash,slashchar);
      }
      path.erase(0,2);    
      path=corpusLocation+path;
     
      map<string,string>temp;
      scanEmail(temp,path.c_str());
      if(strcmp(temp["error"].c_str(),"error in opening file")==0)
                    continue; 
      cout<<" working on\t " <<counter++<<"  emails processed "<<path<<" written"<<endl; 
      map<string,int>tokenMap;
      createTokenMap(temp,tokenMap);
      updateKnowledgeMap(status,tokenMap);
  }   
   inFile.close(); 
   serializeMap(hamMapLocation,hamMap);
   serializeMap(spamMapLocation,spamMap);
   pruneKnowledgeMaps();
   serializeMap(hamMapLocation,hamMap);
   serializeMap(spamMapLocation,spamMap);
   createKnowledgebase();
   serializeMap(knowledgebaseLocation,knowledgebase);
   ofstream counterFile("..\\counter.txt");
   counterFile<<ngood<<endl;
   counterFile<<nbad<<endl;
   counterFile.close();                 
   
   
    
} 
void FilterTrainer::updateKnowledgeMap(string status,map<string,int>tokens){
       
     if(strcmp(status.c_str(),"ham")==0){
        createKnowledgeFromTokens(tokens,hamMap);
        ++ngood;
     }
     else{
         createKnowledgeFromTokens(tokens,spamMap);
         nbad++;
     }
}
        
 
 
void FilterTrainer:: trim(string & token)
{
 
     string stopLetters=",\".<>,;'{}[]%\\~/";
     
     while(stopLetters.find(token[0])!=-1)
        token.erase(0,1);
     
     while(stopLetters.find(token[token.length()-1])!=-1)
         token.erase(token.length()-1,1);
}
void FilterTrainer::createTokenMap(map<string,string>headers,map<string,int>& tokens){
  string tag,value;  
  map<string,string>::iterator headerptr;  
  vector<string>oResult;                            
  for(headerptr=headers.begin();headerptr!=headers.end();++headerptr)
  {
    tag=headerptr->first;
    value=headerptr->second;
    tokenize(value,' ',oResult);
    if(strcmp(tag.c_str(),"body")==0)
       tag="";
    for(int j=0; j<oResult.size(); j++)
    {
       if(isstopwords(stopWords,oResult[j]))
          continue;
       oResult[j]=tag+"."+oResult[j];
       trim(oResult[j]);
       tokens[oResult[j]]=1;          
    } 
   }
   
}
void FilterTrainer::pruneKnowledgeMaps() {
  map<string,int>::iterator itr=hamMap.begin(),endPtr=hamMap.end(),searchPtr,tempPtr;
  while(itr!=endPtr){
     if(itr->second<=frequencyThreshold)
     {
       float b=0;
       searchPtr =spamMap.find(itr->first);
       if(searchPtr!=spamMap.end())
          b=searchPtr->second;
       if((itr->second)*hamBias+b<frequencyThreshold){
                                        
        tempPtr=itr;
        ++itr;
        if(searchPtr!=spamMap.end())
           spamMap.erase(searchPtr);
        hamMap.erase(tempPtr);    
        continue;
       }
     }
     ++itr;
   }
   itr=spamMap.begin();
      endPtr=spamMap.end();
      while(itr!=endPtr){      
          if(itr->second<=frequencyThreshold){
                                     
             float g=0;
             searchPtr =hamMap.find(itr->first);
             if(searchPtr!=hamMap.end())
                                    g=searchPtr->second;
             if((itr->second)+g*hamBias<frequencyThreshold){
                                    
                 tempPtr=itr;
                 ++itr;
                 
                  if(searchPtr!=hamMap.end())
                                            hamMap.erase(searchPtr);
                 spamMap.erase(tempPtr->first);
                
                
                 
                 continue;
                                      
             }
            
                                     
          }
         ++itr;
      }
}



                        
void FilterTrainer::createKnowledgebase(){
      
     
      float tokenProbability; 
      //int 
      
     
      
      string token;
      map<string,int>::iterator hamMapPtr;
      map<string,int>::iterator spamMapPtr;   
      
      int counter=0;      
      
       for(hamMapPtr=hamMap.begin();hamMapPtr!=hamMap.end();++hamMapPtr)
       {
     
         token=hamMapPtr->first;
         float g=hamMapPtr->second;
         float b=0;
         spamMapPtr=spamMap.find(hamMapPtr->first);
         if(spamMapPtr!=hamMap.end())
             b=spamMapPtr->second; 
          if(g+b>5) 
             tokenProbability=max(0.01f,min(0.999f,min(b/nbad,1.0f)/(min(b/nbad,1.0f)+min(g/ngood,1.0f))));                      
          else
           continue;
         cout<<"working on token\t"<<counter++<<endl;
         
         //update knowledge base
        // if(abs(tokenprobability-0.5)<ignoringProbability)
                     //                     continue;
         knowledgebase[token]=tokenProbability ;  
        
        }
         for(spamMapPtr=spamMap.begin();spamMapPtr!=spamMap.end();++spamMapPtr)
       {
     
         token=spamMapPtr->first;
         float b=spamMapPtr->second;
         float g=0;
         if((hamMapPtr=hamMap.find(token))!=hamMap.end())
             b=hamMap[token];                                              
         if(g+b>5)                
            tokenProbability=max(0.01f,min(0.999f,min(b/nbad,1.0f)/(min(b/nbad,1.0f)+min(g/ngood,1.0f))));                      
         else
          continue;
         cout<<"working on token\t"<<counter++<<endl;
         //update knowledge base
         // if(abs(tokenprobability-0.5)<ignoringProbability)
                                   //       continue;
         knowledgebase[token]=tokenProbability ; 
        
      } 
      
}




           
