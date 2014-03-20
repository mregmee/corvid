/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM IClassification.idl
 */

#ifndef __gen_IClassification_h__
#define __gen_IClassification_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    IClassification */
#define ICLASSIFICATION_IID_STR "369a0940-b081-11dc-8314-0800200c9a66"

#define ICLASSIFICATION_IID \
  {0x369a0940, 0xb081, 0x11dc, \
    { 0x83, 0x14, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66 }}

class NS_NO_VTABLE IClassification : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(ICLASSIFICATION_IID)

  /* string classifyEmail (in string email, in string subject, in string dataPath); */
  NS_IMETHOD ClassifyEmail(const char *email, const char *subject, const char *dataPath, char **_retval) = 0;

  /* void trainClassification (in string dataPath); */
  NS_IMETHOD TrainClassification(const char *dataPath) = 0;

  /* void learnClassification (in string email, in string subject, in string category, in string dataPath); */
  NS_IMETHOD LearnClassification(const char *email, const char *subject, const char *category, const char *dataPath) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_ICLASSIFICATION \
  NS_IMETHOD ClassifyEmail(const char *email, const char *subject, const char *dataPath, char **_retval); \
  NS_IMETHOD TrainClassification(const char *dataPath); \
  NS_IMETHOD LearnClassification(const char *email, const char *subject, const char *category, const char *dataPath); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_ICLASSIFICATION(_to) \
  NS_IMETHOD ClassifyEmail(const char *email, const char *subject, const char *dataPath, char **_retval) { return _to ClassifyEmail(email, subject, dataPath, _retval); } \
  NS_IMETHOD TrainClassification(const char *dataPath) { return _to TrainClassification(dataPath); } \
  NS_IMETHOD LearnClassification(const char *email, const char *subject, const char *category, const char *dataPath) { return _to LearnClassification(email, subject, category, dataPath); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_ICLASSIFICATION(_to) \
  NS_IMETHOD ClassifyEmail(const char *email, const char *subject, const char *dataPath, char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->ClassifyEmail(email, subject, dataPath, _retval); } \
  NS_IMETHOD TrainClassification(const char *dataPath) { return !_to ? NS_ERROR_NULL_POINTER : _to->TrainClassification(dataPath); } \
  NS_IMETHOD LearnClassification(const char *email, const char *subject, const char *category, const char *dataPath) { return !_to ? NS_ERROR_NULL_POINTER : _to->LearnClassification(email, subject, category, dataPath); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IClassification
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_ICLASSIFICATION

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IClassification)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* string classifyEmail (in string email, in string subject, in string dataPath); */
NS_IMETHODIMP _MYCLASS_::ClassifyEmail(const char *email, const char *subject, const char *dataPath, char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void trainClassification (in string dataPath); */
NS_IMETHODIMP _MYCLASS_::TrainClassification(const char *dataPath)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void learnClassification (in string email, in string subject, in string category, in string dataPath); */
NS_IMETHODIMP _MYCLASS_::LearnClassification(const char *email, const char *subject, const char *category, const char *dataPath)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_IClassification_h__ */
