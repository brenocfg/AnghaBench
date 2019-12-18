#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_7__ {double* aFreq; int nPhrase; double* aIDF; double const avgdl; } ;
struct TYPE_6__ {int (* xInstCount ) (int /*<<< orphan*/ *,int*) ;int (* xInst ) (int /*<<< orphan*/ *,int,int*,int*,int*) ;int (* xColumnSize ) (int /*<<< orphan*/ *,int,int*) ;} ;
typedef  TYPE_1__ Fts5ExtensionApi ;
typedef  int /*<<< orphan*/  Fts5Context ;
typedef  TYPE_2__ Fts5Bm25Data ;

/* Variables and functions */
 int SQLITE_OK ; 
 int fts5Bm25GetData (TYPE_1__ const*,int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  memset (double*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_result_double (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int) ; 
 double sqlite3_value_double (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,int*) ; 
 int stub2 (int /*<<< orphan*/ *,int,int*,int*,int*) ; 
 int stub3 (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static void fts5Bm25Function(
  const Fts5ExtensionApi *pApi,   /* API offered by current FTS version */
  Fts5Context *pFts,              /* First arg to pass to pApi functions */
  sqlite3_context *pCtx,          /* Context for returning result/error */
  int nVal,                       /* Number of values in apVal[] array */
  sqlite3_value **apVal           /* Array of trailing arguments */
){
  const double k1 = 1.2;          /* Constant "k1" from BM25 formula */
  const double b = 0.75;          /* Constant "b" from BM25 formula */
  int rc = SQLITE_OK;             /* Error code */
  double score = 0.0;             /* SQL function return value */
  Fts5Bm25Data *pData;            /* Values allocated/calculated once only */
  int i;                          /* Iterator variable */
  int nInst = 0;                  /* Value returned by xInstCount() */
  double D = 0.0;                 /* Total number of tokens in row */
  double *aFreq = 0;              /* Array of phrase freq. for current row */

  /* Calculate the phrase frequency (symbol "f(qi,D)" in the documentation)
  ** for each phrase in the query for the current row. */
  rc = fts5Bm25GetData(pApi, pFts, &pData);
  if( rc==SQLITE_OK ){
    aFreq = pData->aFreq;
    memset(aFreq, 0, sizeof(double) * pData->nPhrase);
    rc = pApi->xInstCount(pFts, &nInst);
  }
  for(i=0; rc==SQLITE_OK && i<nInst; i++){
    int ip; int ic; int io;
    rc = pApi->xInst(pFts, i, &ip, &ic, &io);
    if( rc==SQLITE_OK ){
      double w = (nVal > ic) ? sqlite3_value_double(apVal[ic]) : 1.0;
      aFreq[ip] += w;
    }
  }

  /* Figure out the total size of the current row in tokens. */
  if( rc==SQLITE_OK ){
    int nTok;
    rc = pApi->xColumnSize(pFts, -1, &nTok);
    D = (double)nTok;
  }

  /* Determine the BM25 score for the current row. */
  for(i=0; rc==SQLITE_OK && i<pData->nPhrase; i++){
    score += pData->aIDF[i] * (
      ( aFreq[i] * (k1 + 1.0) ) / 
      ( aFreq[i] + k1 * (1 - b + b * D / pData->avgdl) )
    );
  }
  
  /* If no error has occurred, return the calculated score. Otherwise,
  ** throw an SQL exception.  */
  if( rc==SQLITE_OK ){
    sqlite3_result_double(pCtx, -1.0 * score);
  }else{
    sqlite3_result_error_code(pCtx, rc);
  }
}