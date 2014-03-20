
#include <stdio.h>
#include<vector>
#include<string>
#include "deelx.h"
//#include "stlsl.h"
#include<map>
#ifndef SENTENCEEXTRACTOR_H
#define SENTENCEEXTRACTOR_H
#include "SentenceExtractor.h"
#endif

#include<math.h>
#ifndef DATAPATH_H
#define DATAPATH_H
#include "DataPath.h"
#endif

using namespace std;

class FeatureExtractor
{
   private:
	  string pEmail;
	   int sentenceLength;
	   int paraLength;
	   int nofwords;
	 // char** tokens;	
     // int noOfWords;
     // vector<string> emailtokens;
      //vector< vector<string> > cnplist;
	  //string dataPath;
            
    public:
	  FeatureExtractor(string);
      int setEmail(string email);
	  string TrimSpaces( string str);
      int processEmail();
      void getFeatureVector(vector< vector<string> >& cnplist,vector< vector<float> >& ftr);
      float calculateTfidf(string token);
      int noOfOccurance(string tkn);
      int calculateNo(string token);
      int tokenFocc(string tkn);
      int sentPos(vector<string>&);
      int parPos(vector<string>&);
      int noOfDocuments();
      int nowordscnp(vector< vector<string> >&);
      int nocharscnp();
	  static map<string,int> stmap;
	  static void loadStfile()
	  {
		
		    string stfilepath=DataPath::dataPath+"\\stfile.txt";
              
              file_trait_reader file_reader (stfilepath.c_str());      
              if(file_reader==NULL){
                     cout<<"error in opening file inside calculate no"<<endl;
                     getch();
               }
                 
               value_trait < std::map<string,int> > data_filer;
               data_filer.load(stmap,file_reader);     
               file_reader.close();
	  }
	  static void writeStfile()
	  {
		             string stfilepath=DataPath::dataPath+"\\stfile.txt";
					 value_trait < std::map<string,int> > data_filer; 
		             stl_trait_writer file_interface (stfilepath.c_str());
                     data_filer.serialize(stmap,file_interface);
                     file_interface.close();
                   
	  }
	  string getProcessedEmail();
         
      };

    map<string,int> FeatureExtractor::stmap;

	FeatureExtractor::FeatureExtractor(string eemail)
      {
                         pEmail=eemail;
						 sentenceLength=12;
						 paraLength=10;
						 
						 
      }
           
                       
      
    
      
      float FeatureExtractor:: calculateTfidf(string token)
      {
                                  float tf, idf, tfidf;
                                  int d;//no.of documents containing the term
                                  int n=0;
                                  int m=noOfOccurance(token);
                                 // cout<<"token"<<token<<endl;
                                  
                                  //n=emailtokens.size(); 
                                  //cout<<"m"<<m<<"n"<<n<<endl;                              
                                  tf=(float)m/nofwords;
                                  //cout<<"tf"<<tf<<endl;
                                  d=calculateNo(token);
                                  //cout<<"d"<<d<<endl;
                                  idf=log((float)noOfDocuments()/d);
                                   //cout<<"idf"<<idf<<endl;
                                  tfidf=tf*idf;
                                  return tfidf;
           }
            
      
      int FeatureExtractor::noOfOccurance(string token)
      {
           int count=0;
          // string token=TrimSpaces(tkn);

           int found=0;
           int length=token.size();
           while((found=pEmail.find(token,found))!=-1)
               {
                    count++;
                   found=(int)found+length+1; 
               }
              return count;
       }
          
          int FeatureExtractor:: calculateNo(string token)
          {             
              
			
                int tokencount;
               map<string,int>::iterator tokenitr;
               if((tokenitr=stmap.find(token))!=stmap.end())
                   {
                            tokencount=tokenitr->second;                                    
                            stmap[token]=++tokencount;                                      
                   }
               else
                   {
                       stmap[token]=1;
                       tokencount=1;
                       
                   }
                   
                     
                   
                   return tokencount;
                               
               }  
             
             int FeatureExtractor:: tokenFocc(string token)
             {
                 int count=0;
                 //string token=TrimSpaces(tkn);                               
                 return (int)pEmail.find(token);
             }
                 
             int FeatureExtractor:: sentPos(vector<string>& nounPhrases)
               {
				   string currentPhrase=nounPhrases[nounPhrases.size()-1];
				   int occurences=0;
				   //cout<<"PEmail"<<pEmail<<endl;
				   for(int i=0;i<nounPhrases.size();++i)
				   {
					   
					   if(strcmp(nounPhrases[i].c_str(),currentPhrase.c_str())==0)
					   						     occurences++;
					   
				   }
				   
				   string sentence=SentenceExtractor::extractSentence(currentPhrase,occurences,pEmail);
				   int position=sentence.find(currentPhrase);
				   int count=0;
				   for(int i=0;i<position;++i)
				   {
					   if(isspace(sentence[i]))
						   count++;
				   }
				   return count;
					   
			 }                       
               int FeatureExtractor::parPos(vector<string>& nounPhrases)
                 {
					string currentPhrase=nounPhrases[nounPhrases.size()-1];
				   int occurences=1;
				   for(int i=0;i<nounPhrases.size()-1;++i)
				   {
					   if(strcmp(nounPhrases[i].c_str(),currentPhrase.c_str())==0)
						   occurences++;
				   }

                 int count=0;
				 int index=0;
				 while(count<occurences)
				 {
					 index=(int)pEmail.find(currentPhrase);
					count++;
					}
				 count=0;
                 for(int i=0;i<index;i++)
                  if(pEmail[i]=='\n')
                                count++;
                  
                  return count;
                                                              
                   }
       int FeatureExtractor:: noOfDocuments()
       {
		   return DataPath::noOfDocuments;
       }
 
       int FeatureExtractor::nowordscnp(vector< vector<string> >& cnplist)
       {
           
           int count=0;
		   //cout<<"cnplistSize"<<cnplist.size();
           for(int i=0;i<cnplist.size();i++)
           {
              for(int j=0;j<cnplist[i].size();j++)
              {
                     //cout<<cnplist[i][j]<<" ";            
                      count++;
              }
              //cout<<endl;
           }
           
                      
           return count;
           
       } 
       
       
      
   void FeatureExtractor::getFeatureVector(vector< vector<string> >& cnplist,vector< vector<float> >& ftr)
   {
              
       
       int nofchars;
       int nofwordsnp;
       int nofcharsnp;
       float mhtfidf=0.0;
	   vector<float> feature;
	  
	   nofwords=nowordscnp(cnplist);
	   nofchars=pEmail.length();
	   ftr.clear();
	   vector<string> nounPhrases;
	   for(int k=0;k<cnplist.size();++k)
	   {
		   mhtfidf=0.0;
		   vector<string> np=cnplist[k];               
           string head=np[np.size()-1];
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
		   nounPhrases.push_back(nounphrase);
		   feature.clear();
           feature.push_back(calculateTfidf(head));
		   //cout<<"tokenFocc"<<tokenFocc(head)<<endl;
           feature.push_back(tokenFocc(head));
           feature.push_back(calculateTfidf(nounphrase));
           feature.push_back(tokenFocc(nounphrase));
           nofwordsnp=np.size();
          
		   //nofwords=5;
		   //cout<<" nofwordsnp"<< nofwordsnp<<endl;
		   //cout<<"nofwords"<<nofwords<<endl;
           feature.push_back((float)nofwordsnp/(float)nofwords);
           nofcharsnp=nounphrase.length();
           
           feature.push_back((float)nofcharsnp/(float)nofchars);
           feature.push_back(sentPos(nounPhrases)/(float)sentenceLength);
           feature.push_back(parPos(nounPhrases)/(float)paraLength);
           for(int i=0;i<np.size();i++)
                   mhtfidf+=calculateTfidf(np[i]);
           feature.push_back(mhtfidf);

		   ftr.push_back(feature);

                
	   }
	}

	string FeatureExtractor::getProcessedEmail()
	{
		return pEmail;
	}
