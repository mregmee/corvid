#include<iostream>
#include<conio.h>
#include<map>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include "Tokenizer.h"
#include "stlsl.h"

using namespace std;
namespace filterspace{

class EmailFunctions{
 private:
           static vector<string>stopWords;
           static string stopWordsLocation;
 public:
		static void readStopWords(){
			ifstream stopwordsFile;
			stopwordsFile.open(stopWordsLocation.c_str());
			string line;
			if(stopwordsFile==NULL){
				cout<<"error in reading stopWords file"<<endl;
			   getch();
				return ;
			}
			while(getline(stopwordsFile,line)!=NULL)
				  stopWords.push_back(line);
		}


          void scanEmail(map<string,string>&,const char*);
          void tokenize(string text,char tokenSeparator,vector<string>& tokens);
          template<class T>
          void serializeMap(char* file,map<string,T>);
          bool isDigit(string);
          bool isstopwords(vector<string>stopwords,string token);
          void createKnowledgeFromTokens(map<string,int> tokens,map<string,int>& knowledgebase);
         // static void readStopWords();
          void createTokenMap(map<string,string>header,map<string,int>& tokens);
          void trim(string&);
		  static void setStopWordsLocation(const char* dl){
			  stopWordsLocation=string(dl)+"\\stopwords.txt";
		  }
          template<class T>        
         static void loadFile(map<string,T>& reader_object,const char *serializedFile){


      file_trait_reader file_reader (serializedFile);
      if(file_reader==NULL){
       //cout<<"error in opening file  "<<serializedFile<<endl;
      // getch();
       }


      value_trait < std::map<string,T> > data_filer;
      data_filer.load(reader_object,file_reader);
      file_reader.close();


      }

          EmailFunctions();

          };

string EmailFunctions::stopWordsLocation="";
vector<string>EmailFunctions::stopWords;


EmailFunctions::EmailFunctions(){
                                 //stopWordsLocation="c:\\data\\stopwords.txt";

}

 
void EmailFunctions::scanEmail(map<string,string>& headers,const char* emailFile){
    ifstream inFile;
    inFile.open(emailFile);
   // stringstream inFile(emailFile);
    if(inFile==NULL)
    {
     cout<<"errror in opening email file "<<emailFile<<endl;
     headers["error"]="error in opening file";
     return ;
     }
    string line;
    string header="";
    string content="";
    bool isbody=false;
    string temp="";

    while(getline(inFile,line)!=NULL)
    {

      if(line.empty()){
          if(isbody){
                    continue;
                    }
          if(!header.empty()){
             headers[header]=content;
             content="";
           }
           header="body";
           content="";
           isbody=true;
           continue;
       }
      if(isbody)
      {
        content+=line;
        continue;
       }


      int index=line.find(":",0);
      if(index==string::npos){
          content+=line;
          continue;
      }

      if(!(header.empty())){
          temp=line.substr(0,index+1);
          if(isDigit(temp))
          {

           content+=line;
           continue;
         }
         else{
              headers[header]=content;
              content="";
         }
      }
   header=line.substr(0,index);
   content=content+line.substr(index+1,line.length());

 }

   headers["body"]=content;

   //inFile.close();

}
bool EmailFunctions::isDigit(string str){
     string digits="0123456789 ";
     for(int i=0;i<str.length();++i)
             if(digits.find(str[i])!=string::npos)
                return true;
     return false;
}


void EmailFunctions::tokenize(string text,char tokenSeparator,vector<string>& tokens){
      if(tokenSeparator==',')


       CTokenizer<CIsComma>::Tokenize(tokens, text, CIsComma());



 else

	  CTokenizer<>::Tokenize(tokens, text);



}
template<class T>
void EmailFunctions::serializeMap(char * serializationFile,map<string,T>writer_object){

     stl_trait_writer file_interface (serializationFile );
     value_trait < std::map<string,T> > data_filer;
     data_filer.serialize(writer_object,file_interface);
     file_interface.close();
}


bool EmailFunctions:: isstopwords(vector<string>stopwords,string token)
{
      for( int k=0; k<stopwords.size(); k++)
      {
                 if(strcmp(token.c_str(),stopwords[k].c_str())==0)
                                 return true;

       }
       return false;



}

void EmailFunctions::createKnowledgeFromTokens(map<string,int> tokens,map<string,int>& knowledgebase){
     map<string,int>::iterator tokensIterator;
     for(tokensIterator=tokens.begin();tokensIterator!=tokens.end();++tokensIterator){

       map<string,int>::iterator temp=knowledgebase.find(tokensIterator->first);
       if(temp== knowledgebase.end())
           knowledgebase[tokensIterator->first]=1;
       else
       {
           int tempValue=temp->second;
           tempValue++;
           knowledgebase[tokensIterator->first]=tempValue;
        }
    }



}
//static void EmailFunctions::

//template<class T>

void EmailFunctions::createTokenMap(map<string,string>headers,map<string,int>& tokens){
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
void EmailFunctions:: trim(string & token)
{

     string stopLetters=",\".<>,;'{}[]%\\~/";

     while(stopLetters.find(token[0])!=-1)
        token.erase(0,1);

    // while(stopLetters.find(token[token.length()-1])!=-1)
       //  token.erase(token.length()-1,1);
}
}
