/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM ISummarization.idl
 */

#ifndef __gen_ISummarization_h__
#define __gen_ISummarization_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    ISummarization */
#define ISUMMARIZATION_IID_STR "90758a97-a6f3-4ea4-8953-16bd2ee3a977"

#define ISUMMARIZATION_IID \
  {0x90758a97, 0xa6f3, 0x4ea4, \
    { 0x89, 0x53, 0x16, 0xbd, 0x2e, 0xe3, 0xa9, 0x77 }}

class NS_NO_VTABLE ISummarization : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(ISUMMARIZATION_IID)

  /* string summarizeEmail (in string email, in string dataPath); */
  NS_IMETHOD SummarizeEmail(const char *email, const char *dataPath, char **_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_ISUMMARIZATION \
  NS_IMETHOD SummarizeEmail(const char *email, const char *dataPath, char **_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_ISUMMARIZATION(_to) \
  NS_IMETHOD SummarizeEmail(const char *email, const char *dataPath, char **_retval) { return _to SummarizeEmail(email, dataPath, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_ISUMMARIZATION(_to) \
  NS_IMETHOD SummarizeEmail(const char *email, const char *dataPath, char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->SummarizeEmail(email, dataPath, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public ISummarization
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_ISUMMARIZATION

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, ISummarization)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* string summarizeEmail (in string email, in string dataPath); */
NS_IMETHODIMP _MYCLASS_::SummarizeEmail(const char *email, const char *dataPath, char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_ISummarization_h__ */
