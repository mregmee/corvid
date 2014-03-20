#include "stlsl.h"
#include "stdafx.h"
#ifndef DATAPATH_H
#define DATAPATH_H
#include "DataPath.h"
#endif

#ifndef STRINGOPERATION_H
#define STRINGOPERATION_H
#include "StringOperation.h"
#endif

#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "Tokenizer.h"
#endif


using namespace std;

class Postagger: public Tokenizer
{
private:
	 int tok_start[16384];
	 int tok_stop[16384];
	 static char ** keys;
	 static char ** vals;
	 int num;
	 

public:
	Postagger();
	
	static int loadTagmap()
    {
	string stfilepath=DataPath::dataPath+"\\tagmap.txt";
	//cout<<stfilepath<<endl;
	//getch();
	
	//string stfilepath=dataPath+tempPath;
	//string stfilepath="tagmap.txt";
    map<string,string>tagmap;
	int tokencount;
  
	file_trait_reader file_reader (stfilepath.c_str());      
	
	if(file_reader==NULL){
         cout<<"error in opening file inside load map"<<endl;         
	}
     
    value_trait < std::map<string,string> > data_filer;
    data_filer.load(tagmap,file_reader);     
    file_reader.close();
    
	int i=0;
    map<string,string>::iterator tokenitr;
	keys=new char*[tagmap.size()+1];
	vals=new char*[tagmap.size()+1];
	
	for(tokenitr=tagmap.begin();tokenitr!=tagmap.end();tokenitr++)
    {
		keys[i]=new char[tokenitr->first.length()+1];
		strcpy(keys[i],tokenitr->first.c_str());
		
		vals[i]=new char[tokenitr->second.length()+1];
		strcpy(vals[i],tokenitr->second.c_str());
		i++;
    }	

	

    return 0;
    }	
	char * getValHelper(char *key, int start, int end);
	char * getVal(char *key);
	int local_index(const char * s, char ch);
	char ** tag(char ** strs);
};
 char** Postagger:: keys;
 char** Postagger:: vals;
//static int Postagger::num=93429;

Postagger::Postagger()
{
	num=93429;
	//loadTagmap();
}



 char* Postagger:: getValHelper(char *key, int start, int end)
{

	 int i;
  string token;
  int half = (start + end) / 2;
  if (half == start) return NULL;
  if (half == end)   return NULL;
  token=keys[half];
  strlwr((char *)token.c_str());
  i = strcmp(key,token.c_str());
  //cout<<"reached"<<key<<"       "<<token<<endl;
  if (i == 0)  return vals[half];
  if (i < 0) return getValHelper(key, start, half);
  else       return getValHelper(key, half, end);
}

 char* Postagger:: getVal(char *key) {
  return getValHelper(key, 0, num);

}
int Postagger::local_index(const char * s, char ch)
{

	int i;
	int len;
	len = strlen(s);
	for (i=0; i<len; i++) {
	if (ch == s[i]) return i;
	  }
	  return -1;
}
char** Postagger::tag(char ** strs)
{

	//Tokenizer tokenizer;
	int size = count_strings(strs);
	
  //cout << "tag: size="<< size << "\n";
  char ** tags = make_strings(size);
  for (int i=0; i<size; i++) {
     char* temp  = getVal(strs[i]);
    if (temp==NULL) {
      tags[i] = string_copy("NN");
    }
	else {
		text=string(temp);		
      char ** ts = tokenize();
      if (ts == NULL)  { tags[i] = string_copy("NN"); continue; }
      //int nums = count_strings(ts);
      //cout << "tlist=" << tlist << ", nums=" << nums << "\n";
      tags[i] = string_copy(ts[0]);
    free_strings(ts);
    }
  }
  // Now pass through "most likely tags", applying transformational rules:
  for (int i=0; i<size; i++) {
    int len = strlen(strs[i]);
    // rule 1: DT, {VBD | VBP} --> DT, NN
    if (i > 0) {
      if (strcmp(tags[i-1], "DT")==0) {
	if (strcmp(tags[i], "VBD")==0 || strcmp(tags[i], "VBP")==0 || strcmp(tags[i], "VB")==0) {
	  free(tags[i]);
	  tags[i] = string_copy("NN");
	}
      }
    }
    // rule 2: convert a noun to a number (CD) if "." appears in the word
    if (tags[i][0] == 'N') {
      if (local_index((const char *)strs[i], (int)'.') > -1) {
	free(tags[i]);
	tags[i] = string_copy("CD");
      }
    }
    // rule 3: convert a noun to a past participle if words[i] ends with "ed"
    if (tags[i][0] == 'N') {
      if (len > 2) {
	if (strs[i][len-2]=='e' && strs[i][len-1]=='d') {
	 free(tags[i]);
	  tags[i] =string_copy("VBN");
	}
      }
    }
    // rule 4: convert any type to adverb if it ends in "ly"
    if (len > 2) {
      if (strs[i][len-2]=='l' && strs[i][len-1]=='y') {
	free(tags[i]);
	tags[i] = string_copy("RB");
      }
    }
    // rule 5: convert a common noun (NN or NNS) to a adjective if it ends with "al"
    if (len > 2) {
      if (strcmp(tags[i],"NN")==0 || strcmp(tags[i],"NNS")==0) {
	if (strs[i][len-2]=='a' && strs[i][len-1]=='l') {
	  free(tags[i]);
	  tags[i] = string_copy("JJ");
	}
      }
    }
    // rule 6: convert a noun to a verb if the preceeding work is "would"
    if (i > 0 && len > 2) {
      if (tags[i][0]=='N' && tags[i][1]=='N' && strcmp(strs[i-1], "would")==0) {
	free(tags[i]);
	tags[i] = string_copy("VB");
      }
    }
    // rule 7: if a word has been categorized as a common noun and it ends with "s",
    //         then set its type to plural common noun (NNS)
    if (len > 1 && strcmp(tags[i], "NN")==0) {
      if (strs[i][len-1]=='s') {
	free(tags[i]);
	tags[i] = string_copy("NNS");
      }
    }
    // rule 8: convert a common noun to a present prticiple verb (i.e., a gerand)
    if (strlen(tags[i]) > 1 && len > 4) {
      if (tags[i][0]=='N' && tags[i][1]=='N' && strs[i][len-3]=='i' &&
	  strs[i][len-2]=='n' && strs[i][len-1]=='g') {
	free(tags[i]);
	tags[i] = string_copy("VBG");
      }
    }
  }
  return tags;
}