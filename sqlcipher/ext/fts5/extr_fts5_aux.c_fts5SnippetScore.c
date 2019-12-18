#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_int64 ;
struct TYPE_3__ {int (* xInstCount ) (int /*<<< orphan*/ *,int*) ;int (* xInst ) (int /*<<< orphan*/ *,int,int*,int*,int*) ;int (* xPhraseSize ) (int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_1__ Fts5ExtensionApi ;
typedef  int /*<<< orphan*/  Fts5Context ;

/* Variables and functions */
 int SQLITE_OK ; 
 int stub1 (int /*<<< orphan*/ *,int*) ; 
 int stub2 (int /*<<< orphan*/ *,int,int*,int*,int*) ; 
 int stub3 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fts5SnippetScore(
  const Fts5ExtensionApi *pApi,   /* API offered by current FTS version */
  Fts5Context *pFts,              /* First arg to pass to pApi functions */
  int nDocsize,                   /* Size of column in tokens */
  unsigned char *aSeen,           /* Array with one element per query phrase */
  int iCol,                       /* Column to score */
  int iPos,                       /* Starting offset to score */
  int nToken,                     /* Max tokens per snippet */
  int *pnScore,                   /* OUT: Score */
  int *piPos                      /* OUT: Adjusted offset */
){
  int rc;
  int i;
  int ip = 0;
  int ic = 0;
  int iOff = 0;
  int iFirst = -1;
  int nInst;
  int nScore = 0;
  int iLast = 0;
  sqlite3_int64 iEnd = (sqlite3_int64)iPos + nToken;

  rc = pApi->xInstCount(pFts, &nInst);
  for(i=0; i<nInst && rc==SQLITE_OK; i++){
    rc = pApi->xInst(pFts, i, &ip, &ic, &iOff);
    if( rc==SQLITE_OK && ic==iCol && iOff>=iPos && iOff<iEnd ){
      nScore += (aSeen[ip] ? 1 : 1000);
      aSeen[ip] = 1;
      if( iFirst<0 ) iFirst = iOff;
      iLast = iOff + pApi->xPhraseSize(pFts, ip);
    }
  }

  *pnScore = nScore;
  if( piPos ){
    sqlite3_int64 iAdj = iFirst - (nToken - (iLast-iFirst)) / 2;
    if( (iAdj+nToken)>nDocsize ) iAdj = nDocsize - nToken;
    if( iAdj<0 ) iAdj = 0;
    *piPos = (int)iAdj;
  }

  return rc;
}