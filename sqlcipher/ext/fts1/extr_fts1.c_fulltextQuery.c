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
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_8__ {int nTerms; TYPE_1__* pTerms; } ;
struct TYPE_7__ {int nPhrase; int /*<<< orphan*/  iColumn; scalar_t__ isNot; scalar_t__ isOr; } ;
typedef  TYPE_1__ QueryTerm ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  DocList ;

/* Variables and functions */
 int /*<<< orphan*/  DL_DOCIDS ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  docListAndMerge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  docListDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  docListExceptMerge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * docListNew (int /*<<< orphan*/ ) ; 
 int docListOfTerm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  docListOrMerge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int parseQuery (int /*<<< orphan*/ *,char const*,int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  queryClear (TYPE_2__*) ; 

__attribute__((used)) static int fulltextQuery(
  fulltext_vtab *v,      /* The full text index */
  int iColumn,           /* Match against this column by default */
  const char *zInput,    /* The query string */
  int nInput,            /* Number of bytes in zInput[] */
  DocList **pResult,     /* Write the result doclist here */
  Query *pQuery          /* Put parsed query string here */
){
  int i, iNext, rc;
  DocList *pLeft = NULL;
  DocList *pRight, *pNew, *pOr;
  int nNot = 0;
  QueryTerm *aTerm;

  rc = parseQuery(v, zInput, nInput, iColumn, pQuery);
  if( rc!=SQLITE_OK ) return rc;

  /* Merge AND terms. */
  aTerm = pQuery->pTerms;
  for(i = 0; i<pQuery->nTerms; i=iNext){
    if( aTerm[i].isNot ){
      /* Handle all NOT terms in a separate pass */
      nNot++;
      iNext = i + aTerm[i].nPhrase+1;
      continue;
    }
    iNext = i + aTerm[i].nPhrase + 1;
    rc = docListOfTerm(v, aTerm[i].iColumn, &aTerm[i], &pRight);
    if( rc ){
      queryClear(pQuery);
      return rc;
    }
    while( iNext<pQuery->nTerms && aTerm[iNext].isOr ){
      rc = docListOfTerm(v, aTerm[iNext].iColumn, &aTerm[iNext], &pOr);
      iNext += aTerm[iNext].nPhrase + 1;
      if( rc ){
        queryClear(pQuery);
        return rc;
      }
      pNew = docListNew(DL_DOCIDS);
      docListOrMerge(pRight, pOr, pNew);
      docListDelete(pRight);
      docListDelete(pOr);
      pRight = pNew;
    }
    if( pLeft==0 ){
      pLeft = pRight;
    }else{
      pNew = docListNew(DL_DOCIDS);
      docListAndMerge(pLeft, pRight, pNew);
      docListDelete(pRight);
      docListDelete(pLeft);
      pLeft = pNew;
    }
  }

  if( nNot && pLeft==0 ){
    /* We do not yet know how to handle a query of only NOT terms */
    return SQLITE_ERROR;
  }

  /* Do the EXCEPT terms */
  for(i=0; i<pQuery->nTerms;  i += aTerm[i].nPhrase + 1){
    if( !aTerm[i].isNot ) continue;
    rc = docListOfTerm(v, aTerm[i].iColumn, &aTerm[i], &pRight);
    if( rc ){
      queryClear(pQuery);
      docListDelete(pLeft);
      return rc;
    }
    pNew = docListNew(DL_DOCIDS);
    docListExceptMerge(pLeft, pRight, pNew);
    docListDelete(pRight);
    docListDelete(pLeft);
    pLeft = pNew;
  }

  *pResult = pLeft;
  return rc;
}