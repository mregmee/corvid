#ifndef TOKENIZER_H
	#define TOKENIZER_H
	#include "tokenizer.h"
#endif

/*
	The class SentenceDiscoverer is responsible 
	for getting sentences from an email text. The factors used for sentence
	separators are
	--",;.?" are considered as sentence separator
	
*/


class SentenceDiscoverer
{
private:
	static  string sentenceDelimiters;//stores characters used as sentence separators
	static int avgLength;//average length of the sentence to be considered
public:
	SentenceDiscoverer(int len);
	void changeSeparator(string &temp);
	void discoverSentences(string,vector< vector<string> >&);
};
string SentenceDiscoverer::sentenceDelimiters;
int SentenceDiscoverer::avgLength;
SentenceDiscoverer::SentenceDiscoverer(int len)
{
	avgLength=len;
	sentenceDelimiters=",;.?\n:";
}


void SentenceDiscoverer::discoverSentences(string emailText,vector< vector<string> >& sentences)
{
	
	vector<string>phrase;
	sentences.clear();

	changeSeparator(emailText);
	// n is number of newline characters
	//p is number of set of words read after the last sentence separator
	int n=0,p=0;

	vector<string>tokens;
	CTokenizer<>::Tokenize(tokens, emailText);
		
	string t;int j,k,m,count;
	vector<string>tempPhrase;
	vector<int>indexOfNewLine;
	for(int i=0;i<tokens.size();i++)
	{
		t=tokens[i];
		if(t[0]=='.')//if separator
		{
			if((p/(n+1))>avgLength)
			{
				//do not split into shorter sentence
				sentences.push_back(phrase);
			}
			else
			{
				count=0;
				indexOfNewLine.push_back(p);
				for(j=0;j<(n+1);j++)
				{
	
					m=indexOfNewLine[j]-count;

					for(k=0;k<m;k++)
					{
						tempPhrase.push_back(phrase[count]);
						count++;
			
					}
					if(!tempPhrase.empty())
						sentences.push_back(tempPhrase);
					tempPhrase.clear();
				}

			}
	
			phrase.clear();
			indexOfNewLine.clear();
			n=0;
			p=0;

		}
		else if(t[0]=='\n')
		{
			n=n+1;
			indexOfNewLine.push_back(p);
		}
		else
		{
			phrase.push_back(tokens[i]);
			p++;
		}
	}
}
void SentenceDiscoverer::changeSeparator(string &temp)
{
	
	const char *space = " ";
	temp+=".";

	for(int i=0;i<temp.length();i++)
	{
		for(int j=0;j<sentenceDelimiters.length();j++)
		{
			if(temp[i]==sentenceDelimiters[j])
			{
				//if \n is sentence separator then do not replace it with dot
				if(sentenceDelimiters[j]!='\n')
					temp[i]='.';
				temp.insert(i,space);
				temp.insert(i+2,space);
				i=i+2;
				break;
			}
		}
	}
}