#include "nsIGenericFactory.h"
#include "Summarization.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(Summarization)

static nsModuleComponentInfo components[] =
{
    {
       SUMMARIZATION_CLASSNAME, 
       SUMMARIZATION_CID,
       SUMMARIZATION_CONTRACTID,
       SummarizationConstructor,
    }
};

NS_IMPL_NSGETMODULE("SummarizationModule", components) 
