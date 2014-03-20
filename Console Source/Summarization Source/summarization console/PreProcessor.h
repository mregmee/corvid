#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "Tokenizer.h"
#endif

class PreProcessor:public StringOperation
{
private:
	//string pEmail;
	char** tokens;
public:
void processEmail(string& email);
static string TrimSpaces(string str)
{
	// Trim Both leading and trailing spaces
        size_t startpos= str.find_first_not_of(" \t\n"); // Find the first character position after excluding leading blank spaces
        size_t endpos= str.find_last_not_of(" \t\n"); // Find the first character position from reverse af
        // if all spaces or empty return an empty string
        if(( string::npos == startpos ) || ( string::npos == endpos))
        {
            str = "";
        }
        else
            str = str.substr( startpos, endpos-startpos+1 );
        return str;
}
char** getTokens();

};
char** PreProcessor::getTokens()
{
	return tokens;
}

  void PreProcessor::processEmail(string& email)
      {     
          
          string p ="";
		  Tokenizer tokenizer(email);
		  tokens= tokenizer.tokenize();
			
		  int size=count_strings(tokens);
          for(int i=0;i<size;i++)
			  {
                  p+=(string)tokens[i]+" ";  
				  //cout<<tokens[i]<<" ";
				 // cout<<endl;
		  }
		  //getch();
		  strlwr((char*)p.c_str());
          email=TrimSpaces((string)p);
		  free_strings(tokens);
                    
      }
  
      