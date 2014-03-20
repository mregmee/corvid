#include "FilterTrainer.h"

int main(){
    FilterTrainer filter("none");
    filter.trainFromCorpus();
    return 0;
    }


/*
//code for testing 
#include "FilterTest.h"

int main(){
      float threshold=0.98;
      int positive=0;
      int totalProcessed=0;
      int negative=0;
     ifstream inFile;
     string corpusIndexLocation="C:\\Documents and Settings\\prashrestha\\Desktop\\trec05p-1\\full\\index";
     string corpusLocation="C:\\Documents and Settings\\prashrestha\\Desktop\\trec05p-1";
    inFile.open(corpusIndexLocation.c_str());
    if(inFile==NULL){
                     cout<<"error in opening index file";
                     getch();                     
                     }
    string status;
  
    int counter=0;
    ofstream outFile("..\\filterdata.dat");
    FilterTest::initializeFilter("C:\\Documents and Settings\\prashrestha\\Desktop\\Trainermodule");
    while((inFile>>status)!=NULL)
    {
       
      string path;   
      inFile>>path;    
      int slash=0;   
      while((slash=path.find("/",slash))!=-1){  
       string slashchar="\\";
       path[slash]='\\';
       path.insert(slash,slashchar);
      }
      path.erase(0,2);    
      path=corpusLocation+path;
    
    FilterTest* filterTest;
    filterTest=new FilterTest("none");
    filterTest->setEmailLocation(path.c_str());
    filterTest->constructEmailTokens();
    if(filterTest->getNoFile())
    {
      filterTest->clean();
      continue;
      }                          
    float result=filterTest->predictEmail();
    if(result>threshold && status.compare("ham"))
                        positive++;
    else if(result<=threshold && status.compare("spam"))
         negative++;
    cout<<"email: "<<path<<"\t"<<"expected: "<<status<<"\t result: "<<result<<endl;
    outFile<<"Expected\t"<<status<<"\tprobability\t"<<result<<endl;
    totalProcessed++;
	filterTest->clean();  
    
} 
outFile.close();
ofstream resultFile("..\\filterResult.dat");
resultFile<<"totalProcessed\t"<<totalProcessed<<endl;
resultFile<<"falsepositive\t"<<positive<<endl;
resultFile<<"falsenegative\t"<<negative<<endl;
  getch();
    return 0;
    }
*/
