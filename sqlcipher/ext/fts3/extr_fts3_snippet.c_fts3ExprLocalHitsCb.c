#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nCol; int /*<<< orphan*/ * aMatchinfo; int /*<<< orphan*/  pCursor; } ;
typedef  TYPE_1__ MatchInfo ;
typedef  int /*<<< orphan*/  Fts3Expr ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts3ColumnlistCount (char**) ; 
 int sqlite3Fts3EvalPhrasePoslist (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char**) ; 

__attribute__((used)) static int fts3ExprLocalHitsCb(
  Fts3Expr *pExpr,                /* Phrase expression node */
  int iPhrase,                    /* Phrase number */
  void *pCtx                      /* Pointer to MatchInfo structure */
){
  int rc = SQLITE_OK;
  MatchInfo *p = (MatchInfo *)pCtx;
  int iStart = iPhrase * p->nCol * 3;
  int i;

  for(i=0; i<p->nCol && rc==SQLITE_OK; i++){
    char *pCsr;
    rc = sqlite3Fts3EvalPhrasePoslist(p->pCursor, pExpr, i, &pCsr);
    if( pCsr ){
      p->aMatchinfo[iStart+i*3] = fts3ColumnlistCount(&pCsr);
    }else{
      p->aMatchinfo[iStart+i*3] = 0;
    }
  }

  return rc;
}