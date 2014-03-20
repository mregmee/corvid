#ifndef STRINGOPERATION_H
#define STRINGOPERATION_H
#include "StringOperation.h"
#endif

class Tokenizer: public StringOperation
{
protected:
	 string text;
	 int tok_start[16384];
	 int tok_stop[16384];

public:
	Tokenizer();
	Tokenizer(string s);
	char** tokenize();
	int isWhiteSpace(char ch);	
};

Tokenizer::Tokenizer(){ }

Tokenizer::Tokenizer(string s){ text=s;}

char** Tokenizer:: tokenize()
{
	 //cout << "tokenizer("<<str<<")\n";
  
	for(int i=0;i<text.length();i++)
	{
		//if(!isalpha(text[i])||!isdigit(text[i])||text[i]!='.'||text[i]!='\n')
		if(!(isalpha(text[i])|| isspace(text[i])||text[i]=='.'||isdigit(text[i])))
		{
			
			//cout<<text[i];

			text.erase(text.begin()+i);
			--i;
		}
	}
		
		
  const char* str=text.c_str();
  int num_toks = 0;
  int in_tok = 1;
  int start = 0;
  int len = strlen(str);
  // special check for single . or !:
  if (len == 1 && (str[0]=='.' || str[0]=='!')) {
    char **cp = make_strings(1);
    cp[0] = string_copy(".");
    return cp;
  }
  // skip whitespace characters:
  for (int i=0; i<len; i++) {
    if (str[i]!=' ') {
      start = i;
      break;
    }
  }
  int t1 = start;
  for (int i=start; i<len; i++) {
    if (in_tok == 1) {
      if (str[i]==' ') {
	tok_start[num_toks] = t1;
	tok_stop[num_toks] = i;
	num_toks++;
	if (num_toks > 16382) {
	  cout << "Input text is too large\n";
	  exit(1);
	}
	// check to see if this character is a .,;:!, etc, that we want to keep
	// as a separate token:
	if (str[i]=='.' || str[i]=='!') {
	  tok_start[num_toks] = i;
	  tok_stop[num_toks] = i+1;
	  num_toks++;
	}
	in_tok = 0;
      }
    } else { // in white space already
      if (str[i]!=' ') {
	t1 = i;
	in_tok = 1;
      }
    }
  }
  if (in_tok == 1) {
    tok_start[num_toks] = t1;
    tok_stop[num_toks] = len;
    num_toks++;
    // check to see if this character is a .,;:!,\n etc, that we want to keep
    // as a separate token:
    if (len == 1 && str[t1]=='.' || str[t1]=='!'||str[t1]=='\n') {
      tok_start[num_toks] = t1;
      tok_stop[num_toks] = t1+1;
      num_toks++;
    }
  }
  char ** ret = make_strings(num_toks);
  for (int i=0; i<num_toks; i++) {
    int size = tok_stop[i] - tok_start[i];
    char * cp = (char *)malloc(size + 1);
    for (int j=0; j<size; j++) cp[j] = str[tok_start[i]+j];
    cp[size] = 0;
    ret[i] = cp;
  }
  return ret;

}
	
/*	int Tokenizer::isWhiteSpace(char ch)
	{
	  
	  if (ch == ' ') return 1;
	  //if (ch == '.') return 1;
	  if (ch == ';') return 1;
	  if (ch == ',') return 1;
	  if (ch == ':') return 1;
	  if (ch == '!') return 1;
	  if (ch == '"') return 1;
	  if (ch == '&') return 1;
	  if (ch < 14 && ch > 0 ) return 1;
	  return 0;


	}*/
