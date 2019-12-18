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
struct TYPE_2__ {int /*<<< orphan*/ * pExpr; } ;
typedef  TYPE_1__ LcsIterator ;
typedef  int /*<<< orphan*/  Fts3Expr ;

/* Variables and functions */
 int SQLITE_OK ; 

__attribute__((used)) static int fts3MatchinfoLcsCb(
  Fts3Expr *pExpr,                /* Phrase expression node */
  int iPhrase,                    /* Phrase number (numbered from zero) */
  void *pCtx                      /* Pointer to MatchInfo structure */
){
  LcsIterator *aIter = (LcsIterator *)pCtx;
  aIter[iPhrase].pExpr = pExpr;
  return SQLITE_OK;
}