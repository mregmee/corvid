#include<fstream>
#include "deelx.h"
#include<conio.h>
#include<string>
#include<iostream>
using namespace std;
class HtmlParser
{
public:
	void removeTags(string& email);
};
void HtmlParser::removeTags(string& email)
{
	// pattern and text
	char ptn[] ="<[^>]*>";//regular pattern of html tags
	const char* txt = email.c_str();		
	CRegexpT <char> regexp(ptn);
	// find first
	MatchResult result = regexp.Match(txt);
	int startIndex=0; //starting point that does not contain html tag
	string subEmail="";
	string resultEmail="";
	while(result.IsMatched())
	{
		string tag=email.substr(result.GetStart(),result.GetEnd()-result.GetStart());		
		subEmail=email.substr(startIndex,result.GetStart()-startIndex);			
		subEmail=subEmail.substr(0,subEmail.find_last_not_of(" \n\t")+1);		
		resultEmail+=subEmail;
		//replace <p> and <br> with newline
		if(tag.compare("<p>")==0 || tag.compare("<br>")==0)			
			resultEmail+="\n";
		startIndex=result.GetEnd();
		// find next
		result = regexp.Match(txt, result.GetEnd());
	}
	subEmail=email.substr(startIndex);			
	subEmail=subEmail.substr(0,subEmail.find_last_not_of(" \n\t")+1);
	resultEmail+=subEmail;
	email=resultEmail;

		
}
