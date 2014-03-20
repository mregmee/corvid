
#include "Filtration.h"

#include "updateTest.h"

NS_IMPL_ISUPPORTS1(Filtration, IFiltration)

Filtration::Filtration()
{
	//filterTest=FilterTest("none");
  /* member initializers and constructor code */
}

Filtration::~Filtration()
{
  /* destructor code */
}

/* short InitFilter (in string dataPath); */
NS_IMETHODIMP Filtration::InitFilter(const char *dataPath, PRInt16 *_retval)
{
	FilterTest::initializeFilter(dataPath);
	*_retval = 1;

    return NS_OK;
}

/* short InitUpdate (in string dataPath); */
NS_IMETHODIMP Filtration::InitUpdate(const char *dataPath, PRInt16 *_retval)
{
	UpdateFilterKnowledge::initialize(dataPath);
    return NS_OK;
}

/* float PredictEmail (in string email); */
NS_IMETHODIMP Filtration::PredictEmail(const char *email, float *_retval)
{
	try
	{
		FilterTest filterTest("none");
		filterTest.setEmailLocation(email);
		filterTest.constructEmailTokens();
		*_retval=filterTest.predictEmail();
		filterTest.clean();
	}    
	catch(exception e)
	{		
	}
    return NS_OK;
}

/* long UpdateKnowledge (in string email, in string status); */
NS_IMETHODIMP Filtration::UpdateKnowledge(const char *email, const char *status, PRInt32 *_retval)
{
	UpdateFilterKnowledge update;
	update.markEmails(email,status);
	update.clean();
    return NS_OK;
}