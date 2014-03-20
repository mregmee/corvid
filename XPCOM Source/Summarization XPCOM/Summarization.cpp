
#include "Summarization.h"

#include "stdafx.h"
#include <fstream>

#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "Tokenizer.h"
#endif

#ifndef POSTAGGER_H
#define POSTAGGER_H
#include "Postagger.h"
#endif

#include "NounPhraseExtractor.h"

#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H
#include "FeatureExtractor.h"
#endif

#include "NounPhraseRanker.h"

#ifndef SENTENCEEXTRACTOR_H
#define SENTENCEEXTRACTOR_H
#include "SentenceExtractor.h"
#endif
#ifndef POSTAGGER_H
#define POSTAGGER_H
#include "postagger.h"
#endif


#include "EmailSummarizer.h"
#ifndef DATAPATH_H
#define DATAPATH_H
#include "DataPath.h"
#endif
#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H
#include "DataPath.h"
#endif

using namespace std;

/* Implementation file */
NS_IMPL_ISUPPORTS1(Summarization, ISummarization)

Summarization::Summarization()
{
  /* member initializers and constructor code */
}

Summarization::~Summarization()
{
  /* destructor code */
}

/* string summarizeEmail (in string email, in string dataPath); */
NS_IMETHODIMP Summarization::SummarizeEmail(const char *email, const char *dataPath, char **_retval)
{
	DataPath::dataPath = dataPath;
	Postagger::loadTagmap();
	FeatureExtractor::loadStfile();

	EmailSummarizer emlsmr(email);
	FeatureExtractor::writeStfile();
	string summary=emlsmr.summarizeEmail();
	
	*_retval=new char[summary.length()+1];
	strcpy(*_retval,summary.c_str());
    return NS_OK;
}