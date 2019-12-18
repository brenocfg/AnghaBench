#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int (* xOpen ) (TYPE_4__*,char const*,int,TYPE_3__**) ;int (* xNext ) (TYPE_3__*,char const**,int*,int*,int*,int*) ;int (* xClose ) (TYPE_3__*) ;} ;
typedef  TYPE_2__ sqlite3_tokenizer_module ;
struct TYPE_15__ {TYPE_4__* pTokenizer; } ;
typedef  TYPE_3__ sqlite3_tokenizer_cursor ;
struct TYPE_16__ {TYPE_2__* pModule; } ;
typedef  TYPE_4__ sqlite3_tokenizer ;
struct TYPE_17__ {int nTerms; int nextColumn; int nextIsOr; TYPE_1__* pTerms; int /*<<< orphan*/  pFts; } ;
struct TYPE_13__ {int isNot; int isPrefix; int iPhrase; int nPhrase; } ;
typedef  TYPE_5__ Query ;

/* Variables and functions */
 int SQLITE_OK ; 
 int checkColumnSpecifier (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  queryAdd (TYPE_5__*,char const*,int) ; 
 int stub1 (TYPE_4__*,char const*,int,TYPE_3__**) ; 
 int stub2 (TYPE_3__*,char const**,int*,int*,int*,int*) ; 
 int stub3 (TYPE_3__*) ; 

__attribute__((used)) static int tokenizeSegment(
  sqlite3_tokenizer *pTokenizer,          /* The tokenizer to use */
  const char *pSegment, int nSegment,     /* Query expression being parsed */
  int inPhrase,                           /* True if within "..." */
  Query *pQuery                           /* Append results here */
){
  const sqlite3_tokenizer_module *pModule = pTokenizer->pModule;
  sqlite3_tokenizer_cursor *pCursor;
  int firstIndex = pQuery->nTerms;
  int iCol;
  int nTerm = 1;
  
  int rc = pModule->xOpen(pTokenizer, pSegment, nSegment, &pCursor);
  if( rc!=SQLITE_OK ) return rc;
  pCursor->pTokenizer = pTokenizer;

  while( 1 ){
    const char *pToken;
    int nToken, iBegin, iEnd, iPos;

    rc = pModule->xNext(pCursor,
                        &pToken, &nToken,
                        &iBegin, &iEnd, &iPos);
    if( rc!=SQLITE_OK ) break;
    if( !inPhrase &&
        pSegment[iEnd]==':' &&
         (iCol = checkColumnSpecifier(pQuery->pFts, pToken, nToken))>=0 ){
      pQuery->nextColumn = iCol;
      continue;
    }
    if( !inPhrase && pQuery->nTerms>0 && nToken==2
         && pSegment[iBegin]=='O' && pSegment[iBegin+1]=='R' ){
      pQuery->nextIsOr = 1;
      continue;
    }
    queryAdd(pQuery, pToken, nToken);
    if( !inPhrase && iBegin>0 && pSegment[iBegin-1]=='-' ){
      pQuery->pTerms[pQuery->nTerms-1].isNot = 1;
    }
    if( iEnd<nSegment && pSegment[iEnd]=='*' ){
      pQuery->pTerms[pQuery->nTerms-1].isPrefix = 1;
    }
    pQuery->pTerms[pQuery->nTerms-1].iPhrase = nTerm;
    if( inPhrase ){
      nTerm++;
    }
  }

  if( inPhrase && pQuery->nTerms>firstIndex ){
    pQuery->pTerms[firstIndex].nPhrase = pQuery->nTerms - firstIndex - 1;
  }

  return pModule->xClose(pCursor);
}