
//#include <getopt>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include<iostream>

#include "spec.h"
#include "lwneuralnet.h"
using namespace std;
class ANNTrainer
{
private:
	  int no_of_pairs;
	  int no_of_inputs;
	  int no_of_outputs;
	  float input[100];
	  float target[100];
	  float output[100];
	  
	string spec_filename;//[MAX_FILENAME_LENGTH + 1] = "C:\\Documents and Settings\\mregmee\\Desktop\\complete\\Summarization Training\\nndata.spec";
	string nn_filename;//[MAX_FILENAME_LENGTH + 1] = "C:\\Documents and Settings\\mregmee\\Desktop\\complete\\e-summarication\\data\\neuralnet.dat";      /* -i */
	//string output_filename;[MAX_FILENAME_LENGTH + 1] = "C:\\Documents and Settings\\mregmee\\Desktop\\complete\\e-summarication\\data\\neuralnet.dat";    /* -o */
	//int max_trainings = 100000000;  /* -t */
	int max_trainings;// = 1000;
	float max_error;// =0.001;          /* -e */
	int use_bias;// = 1;
	network_t *net;/* -d */

public:
	 ANNTrainer();
	void train();
	
	

};
ANNTrainer:: ANNTrainer()
{

	 spec_filename=DataPath::dataPath+"\\nndata.spec";
	 nn_filename=DataPath::dataPath+"\\neuralnet.dat";      /* -i */
	//string output_filename;[MAX_FILENAME_LENGTH + 1] = "C:\\Documents and Settings\\mregmee\\Desktop\\complete\\e-summarication\\data\\neuralnet.dat";    /* -o */
	//int max_trainings = 100000000;  /* -t */
	 max_trainings=10000000;
	 max_error=0.0000001;          /* -e */
	 use_bias=1; 
	
  
 
  
 
  read_specification (spec_filename.c_str(), &no_of_inputs, &no_of_outputs,&no_of_pairs, input, target);
      

  
  
	net = net_load (nn_filename.c_str());
  
}
void ANNTrainer::train()
{
	srand (time (0));
	 int t;
	 int i;
	 float error,total_error;	
  
  if (!use_bias)
  {
    net_use_bias(net, 0);
  }

	/* See spec.c for the way the input/target pairs are stored
	 * in the input[] and target[] arrays. */
	#define inputs(i) (input + i * no_of_inputs)
	#define targets(i) (target + i* no_of_outputs)

  t = 0;
  total_error = 0;
  while ((t < max_trainings) && ((total_error >= max_error) || (t <= 10))) 
  {
    /* choose one of the input/target pairs: inputs(i), targets(i) */
    i = rand () % no_of_pairs;


      
    /* compute the outputs for inputs(i) */
    net_compute (net, inputs (i), output);


  
    /* find the error with respect to targets(i) */
    error = net_compute_output_error (net, targets (i));

    /* train the network one step */
    net_train (net);

//cout<<"after read specification  "<<t<<endl;;
  
    /* keep track of (moving) average of the error */
    if (t == 0)
	{
      total_error = error;
    }
	else 
	{
      total_error = 0.9 * total_error + 0.1 * error;
    }

    /* next */
    t++;
    //cout<<"total_error  "<<total_error<<endl;
  }
   
 // getch();
 

  
    net_save (nn_filename.c_str(), net);
  
  //printf ("Number of training performed: %i (max %i)\n", t, max_trainings);
  //printf ("Average output error: %f (max %f)\n", total_error, max_error);
  
  //getch();


}
