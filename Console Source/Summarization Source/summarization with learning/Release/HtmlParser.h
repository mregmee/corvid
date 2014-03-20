
#include<fstream>
#include "deelx.h"
#include<conio.h>
#include<string>
#include<iostream>
using namespace std;
int main()
{
	// pattern and text
	char ptn[] ="<[^>]*>";//"<[^>]*(table|tr|td|th)[^<]*>";
	ifstream ifile("email.txt");
	string resultEmail="";
    string email="";
	string temp="";
	while(getline(ifile,temp))
        email+=temp+"\n";
	const char* txt = email.c_str();

	// compile
	CRegexpT <char> regexp(ptn);

	// find first
	MatchResult result = regexp.Match(txt);
	int startIndex=0; //starting point that does not contain tag
	string subEmail="";
	while(result.IsMatched())
	{
		// print found
		string str=email.substr(result.GetStart(),result.GetEnd()-result.GetStart());		
		subEmail=email.substr(startIndex,result.GetStart()-startIndex);			
		subEmail=subEmail.substr(0,subEmail.find_last_not_of(" \n\t")+1);		
		resultEmail+=subEmail;
		if(str.compare("<p>")==0 || str.compare("<br>")==0)
			resultEmail+="\n";

		startIndex=result.GetEnd();
		//cout<<str<<endl;



		// find next
		result = regexp.Match(txt, result.GetEnd());
	}
	cout<<resultEmail<<endl;
	
	getch();

	return 0;
}
