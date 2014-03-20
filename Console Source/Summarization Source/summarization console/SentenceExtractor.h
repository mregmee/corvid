#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include "PreProcessor.h"
#endif
using namespace std;
class SentenceExtractor
{
public:
	static string extractSentence(string nPhrase,int npCount,string pEmail)
	{  
               
		int cTokenIndex=0; 
		//cout<<"nPhrase length"<<nPhrase.length()<<endl;
			string nounPhrase=PreProcessor::TrimSpaces(nPhrase);
			//cout<<"nounPhrase length"<<nounPhrase.length()<<endl;
		
		for(int i=0;i<npCount;i++)
			cTokenIndex=pEmail.find(nounPhrase);               
				                   
         
         int start=cTokenIndex;
		        
         while(pEmail[start]!= '\n' && pEmail[start]!= '.' && start!=0) start--;
        
         /*if(start<0)
			start = 0;*/
		 int end=cTokenIndex;
         while(pEmail[end]!= '\n' && pEmail[end]!= '.' && end!=pEmail.length()) end++;
         char* sentence= new char[end-start+1];
         int i;
         for(i=start;i<end;i++)
                 sentence[i-start]=pEmail[i];
		 sentence[end-start]='\0';
		 
                 
         //free(pEmail);
		 //cout<<"impsentence"<<end<<"   "<<start<<endl;
         
         return sentence;

      }
};
	
