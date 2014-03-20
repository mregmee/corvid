
#include "Classification.h"

#include "classifier.h"

#include "trainer.h"
	
#include "learner.h"

/* Implementation file */
NS_IMPL_ISUPPORTS1(Classification, IClassification)

Classification::Classification()
{
  /* member initializers and constructor code */
}

Classification::~Classification()
{
  /* destructor code */
}

/* string classifyEmail (in string email, in string subject, in string dataPath); */
NS_IMETHODIMP Classification::ClassifyEmail(const char *email, const char *subject, const char *dataPath, char **_retval)
{
	Classifier::initialize(dataPath);
	Classifier classifier(email,subject);
	classifier.processEmail();
	string result=classifier.classify();
	*_retval=new char[result.length()+1];
	strcpy(*_retval,result.c_str());
    return NS_OK;
}

/* void trainClassification (in string dataPath); */
NS_IMETHODIMP Classification::TrainClassification(const char *dataPath)
{
	Trainer trainer(dataPath);
	trainer.train();
    return NS_OK;
}

/* void learnClassification (in string email, in string subject, in string category, in string dataPath); */
NS_IMETHODIMP Classification::LearnClassification(const char *email, const char *subject, const char *category, const char *dataPath)
{
	Learner::initialize(dataPath);
	Learner learner;
	learner.learn(email,subject,category);
    return NS_OK;
}