
#ifndef POSTAGGER_H
#define POSTAGGER_H
#include "Postagger.h"
#endif
#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "Tokenizer.h"
#endif

#include "deelx.h"
#include<vector>
using namespace std;

class NounPhraseExtractor: public StringOperation
{
private:
	
	vector<string> tokenv;
	
public:
	
	void  constructNPList(vector< vector<string> >&,string email);
};



	
void NounPhraseExtractor:: constructNPList(vector< vector<string> >& cnplist,string email)
{

	Tokenizer tokenizer(email);
	char** tokens = tokenizer.tokenize();
	int size = count_strings(tokens);
     for (int i=0; i<size; i++) 
	 {
		
       tokenv.push_back(string(strlwr(tokens[i])));
	 }
	char** tags;
	   Postagger postagger;
	   tags=postagger.tag(tokens);
	   char* txt=(char *)malloc(size + 1);
      for(int i=0;i<size;++i)
	  {
       if(strcmp(tags[i],"NN")==0||strcmp(tags[i],"NNP")==0||strcmp(tags[i],"NNPS")==0||strcmp(tags[i],"NNS")==0||strcmp(tags[i],"PRP")==0)
                                     txt[i]='A';
                           else if(strcmp(tags[i],"JJ")==0)
                                txt[i]='B';
                           else if(strcmp(tags[i],"IN")==0)
                                txt[i]='C';
                           else
                               txt[i]='D';                                                                           
  
	  }  
            //cout <<txt<<endl<<endl;
            char ptn[] = "[BA]*(C)?[BA]*A";
	
	        CRegexpT <char> regexp(ptn);

	        // find first
	        MatchResult result = regexp.Match(txt);
       	while(result.IsMatched())
		{
		// print found
	    //	printf("%.*s\n", result.GetEnd() - result.GetStart(), txt + result.GetStart());
	
        vector<string> temp;	    	    
		for(int i=result.GetStart();i<result.GetEnd();i++)
		{
		          temp.push_back(tokenv[i]);
          }
           cnplist.push_back(temp);
        // find next
		result = regexp.Match(txt, result.GetEnd());
	   }
       free_strings(tokens);
       free_strings(tags); 
       free(txt); 
       tokenv.clear();
     
}