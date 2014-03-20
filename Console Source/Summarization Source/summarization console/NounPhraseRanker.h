
#include "lwneuralnet.h"
#ifndef DATAPATH_H
#define DATAPATH_H
#include "DataPath.h"
#endif

#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H
#include "FeatureExtractor.h"
#endif

class NounPhraseRanker
{

private:
	vector< vector<float> >featureVector ;
    string output_filename; 
	FeatureExtractor *featureExtractor;
		
public:
	NounPhraseRanker(vector< vector<string> >& nplist,string email);
	int createNeuralNet();
	float calculateImportance(vector<float> feature);
	void processNPFeature(vector<float>& importance);


};

NounPhraseRanker::NounPhraseRanker(vector< vector<string> >& nplist, string email)
 {	
	featureExtractor=new FeatureExtractor(email);
	featureExtractor->getFeatureVector(nplist,featureVector);
	cout<<"---------------------------------------------------------------------";
	cout<<"					Candidate NounPhrase List with Features to each"<<endl;
	cout<<"---------------------------------------------------------------------"<<endl;
	for(int i=0;i<nplist.size();i++)
	{
		for(int j=0;j<nplist[i].size();j++)
			cout<<nplist[i][j]<<" ";
		cout<<endl;
		for(int k=0;k<featureVector[i].size();k++)
			cout<<featureVector[i][k]<<" ";
		cout<<endl<<endl;
	}
	getch();
	output_filename= DataPath::dataPath+"\\neuralnet.dat"; 
}
	
	 


 int NounPhraseRanker::createNeuralNet()
{
    int use_bias = 1;
    network_t *net;
    int no_of_layers=3;
    int no_of_neurons[3]= {9,5,1};
    //cout<<
    net = net_allocate_l (no_of_layers, no_of_neurons);
    

    /* write the network to stdout or the specified file */
	if (strlen (output_filename.c_str()) == 0) {
             printf("no file name");
             net_print (net);
             } else {
             //printf("file name is %s",output_filename);
				 net_save (output_filename.c_str(), net);
             }

             /* free resources */
             net_free (net);
             
             return 0;
}
 float NounPhraseRanker:: calculateImportance(vector<float> feature)
{
      network_t *net;
      float* input;
      float* output;
	  output=new float[1];
      float otpt;
      input = new float(feature.size()+1);
      //float error;
      input= new float[feature.size()];
      for(int i=0;i<feature.size();i++)
              input[i]=feature[i];
	  //cout<<" neural net file"<<output_filename<<endl;
	  //getch();
	  net = net_load (output_filename.c_str());
      
      if (net == NULL) {
      printf ("show_network: failed to load network\n");
      getch();
      exit (1);
      }
      
      net_compute (net,input, output);
      
     // cout<<" the importance value is "<< output[0]<<endl;
      
       otpt=output[0];
       net_free (net);
       free(input);
       free(output);
      
      return otpt;
     
           
      
}
 void NounPhraseRanker::processNPFeature(vector<float>& importanceVector)
 {
	string nPhrase;
    float  importanceValue;
	createNeuralNet();
	
	for(int i=0;i<featureVector.size();++i)
	{
           importanceValue=calculateImportance(featureVector[i]);
           // cout<<"the importance is"<<importanceValue<<endl;   
			//getch();           
           
            importanceVector.push_back(importanceValue);
                       
      }
	featureVector.clear();
	
 }