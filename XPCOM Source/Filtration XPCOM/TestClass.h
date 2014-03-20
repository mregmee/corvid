#include <map>
#include<fstream>
#include<string>
using namespace std;
class TestClass
{
private:
		string t;
		map<string,int>myMap;
public:
	TestClass(string test,int a1){
		myMap[test]=a1;
		t=test;
	}
	bool testFunction(int a){
		ofstream file("c:\\data\\sigdel.txt");
		if(file==NULL)
			return false;
		if(myMap[t]==a){

			file<<"success"<<endl;
			file.close();
			return true;
		}
		else{
			file.close();		
			return true;
		}
	}
};
