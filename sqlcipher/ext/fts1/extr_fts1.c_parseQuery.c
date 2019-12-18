#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pTokenizer; } ;
typedef  TYPE_1__ fulltext_vtab ;
struct TYPE_8__ {int nextColumn; int dfltColumn; TYPE_1__* pFts; scalar_t__ nextIsOr; int /*<<< orphan*/ * pTerms; scalar_t__ nTerms; } ;
typedef  TYPE_2__ Query ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  queryClear (TYPE_2__*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  tokenizeSegment (int /*<<< orphan*/ ,char const*,int,int,TYPE_2__*) ; 

__attribute__((used)) static int parseQuery(
  fulltext_vtab *v,        /* The fulltext index */
  const char *zInput,      /* Input text of the query string */
  int nInput,              /* Size of the input text */
  int dfltColumn,          /* Default column of the index to match against */
  Query *pQuery            /* Write the parse results here. */
){
  int iInput, inPhrase = 0;

  if( zInput==0 ) nInput = 0;
  if( nInput<0 ) nInput = strlen(zInput);
  pQuery->nTerms = 0;
  pQuery->pTerms = NULL;
  pQuery->nextIsOr = 0;
  pQuery->nextColumn = dfltColumn;
  pQuery->dfltColumn = dfltColumn;
  pQuery->pFts = v;

  for(iInput=0; iInput<nInput; ++iInput){
    int i;
    for(i=iInput; i<nInput && zInput[i]!='"'; ++i){}
    if( i>iInput ){
      tokenizeSegment(v->pTokenizer, zInput+iInput, i-iInput, inPhrase,
                       pQuery);
    }
    iInput = i;
    if( i<nInput ){
      assert( zInput[i]=='"' );
      inPhrase = !inPhrase;
    }
  }

  if( inPhrase ){
    /* unmatched quote */
    queryClear(pQuery);
    return SQLITE_ERROR;
  }
  return SQLITE_OK;
}