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
 int sqlite3Fts3EvalPhraseStats (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3ExprGlobalHitsCb(
  Fts3Expr *pExpr,                /* Phrase expression node */
  int iPhrase,                    /* Phrase number (numbered from zero) */
  void *pCtx                      /* Pointer to MatchInfo structure */
){
  MatchInfo *p = (MatchInfo *)pCtx;
  return sqlite3Fts3EvalPhraseStats(
      p->pCursor, pExpr, &p->aMatchinfo[3*iPhrase*p->nCol]
  );
}