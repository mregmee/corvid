/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM IFiltration.idl
 */

#ifndef __gen_IFiltration_h__
#define __gen_IFiltration_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    IFiltration */
#define IFILTRATION_IID_STR "660bd8b8-b07a-11dc-8314-0800200c9a66"

#define IFILTRATION_IID \
  {0x660bd8b8, 0xb07a, 0x11dc, \
    { 0x83, 0x14, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66 }}

class NS_NO_VTABLE IFiltration : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(IFILTRATION_IID)

  /* short InitFilter (in string dataPath); */
  NS_IMETHOD InitFilter(const char *dataPath, PRInt16 *_retval) = 0;

  /* short InitUpdate (in string dataPath); */
  NS_IMETHOD InitUpdate(const char *dataPath, PRInt16 *_retval) = 0;

  /* float PredictEmail (in string email); */
  NS_IMETHOD PredictEmail(const char *email, float *_retval) = 0;

  /* long UpdateKnowledge (in string email, in string status); */
  NS_IMETHOD UpdateKnowledge(const char *email, const char *status, PRInt32 *_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFILTRATION \
  NS_IMETHOD InitFilter(const char *dataPath, PRInt16 *_retval); \
  NS_IMETHOD InitUpdate(const char *dataPath, PRInt16 *_retval); \
  NS_IMETHOD PredictEmail(const char *email, float *_retval); \
  NS_IMETHOD UpdateKnowledge(const char *email, const char *status, PRInt32 *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFILTRATION(_to) \
  NS_IMETHOD InitFilter(const char *dataPath, PRInt16 *_retval) { return _to InitFilter(dataPath, _retval); } \
  NS_IMETHOD InitUpdate(const char *dataPath, PRInt16 *_retval) { return _to InitUpdate(dataPath, _retval); } \
  NS_IMETHOD PredictEmail(const char *email, float *_retval) { return _to PredictEmail(email, _retval); } \
  NS_IMETHOD UpdateKnowledge(const char *email, const char *status, PRInt32 *_retval) { return _to UpdateKnowledge(email, status, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFILTRATION(_to) \
  NS_IMETHOD InitFilter(const char *dataPath, PRInt16 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->InitFilter(dataPath, _retval); } \
  NS_IMETHOD InitUpdate(const char *dataPath, PRInt16 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->InitUpdate(dataPath, _retval); } \
  NS_IMETHOD PredictEmail(const char *email, float *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->PredictEmail(email, _retval); } \
  NS_IMETHOD UpdateKnowledge(const char *email, const char *status, PRInt32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdateKnowledge(email, status, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFiltration
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFILTRATION

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFiltration)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* short InitFilter (in string dataPath); */
NS_IMETHODIMP _MYCLASS_::InitFilter(const char *dataPath, PRInt16 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* short InitUpdate (in string dataPath); */
NS_IMETHODIMP _MYCLASS_::InitUpdate(const char *dataPath, PRInt16 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* float PredictEmail (in string email); */
NS_IMETHODIMP _MYCLASS_::PredictEmail(const char *email, float *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long UpdateKnowledge (in string email, in string status); */
NS_IMETHODIMP _MYCLASS_::UpdateKnowledge(const char *email, const char *status, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_IFiltration_h__ */
