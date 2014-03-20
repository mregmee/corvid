#ifndef _SUMMARIZATION_H_
#define _SUMMARIZATION_H_

#include "ISummarization.h"

#endif

#define SUMMARIZATION_CONTRACTID "@mozilla.org/corvidioe/Summarization;1"
#define SUMMARIZATION_CLASSNAME "Email Summarization"
#define SUMMARIZATION_CID  { 0x597a60b0, 0x5272, 0x4284, { 0x90, 0xf6, 0xe9, 0x6c, 0x24, 0x2d, 0x74, 0x6 } }


/* Header file */
class Summarization : public ISummarization
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_ISUMMARIZATION

  Summarization();

private:
  ~Summarization();

protected:
  /* additional members */
};