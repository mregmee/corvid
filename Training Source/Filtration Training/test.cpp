
         FilterTest::initializeFilter(dataPath);
         FilterTest filterTest("none");
		filterTest.setEmailLocation(email);
		filterTest.constructEmailTokens();
		*_retval=filterTest.predictEmail();
		filterTest.clean();

ifstream inFile;
    inFile.open(corpusIndexLocation);
    if(inFile==NULL){
                     cout<<"error in opening index file";
                     getch();                     
                     }
    string status;
  
    int counter=0;
    while((inFile>>status)!=NULL){
       
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
     
      map<string,string>temp;
      scanEmail(temp,path.c_str());
      if(strcmp(temp["error"].c_str(),"error in opening file")==0)
                    continue; 
      cout<<" working on\t " <<counter++<<"  emails processed "<<path<<" written"<<endl; 
      map<string,int>tokenMap;
      createTokenMap(temp,tokenMap);
