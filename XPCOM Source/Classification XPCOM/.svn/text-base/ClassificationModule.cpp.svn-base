#include "nsIGenericFactory.h"
#include "Classification.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(Classification)

static nsModuleComponentInfo components[] =
{
    {
       CLASSIFICATION_CLASSNAME, 
       CLASSIFICATION_CID,
       CLASSIFICATION_CONTRACTID,
       ClassificationConstructor,
    }
};

NS_IMPL_NSGETMODULE("ClassificationModule", components) 
