#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* pPrior; TYPE_2__* pWith; int /*<<< orphan*/  pLimit; int /*<<< orphan*/  pOrderBy; int /*<<< orphan*/  pHaving; int /*<<< orphan*/  pGroupBy; int /*<<< orphan*/  pWhere; int /*<<< orphan*/  pSrc; int /*<<< orphan*/  pEList; } ;
struct TYPE_6__ {int nCte; TYPE_1__* a; } ;
struct TYPE_5__ {TYPE_3__* pSelect; } ;
typedef  TYPE_3__ Select ;
typedef  int /*<<< orphan*/  DbFixer ;

/* Variables and functions */
 scalar_t__ sqlite3FixExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3FixExprList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3FixSrcList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sqlite3FixSelect(
  DbFixer *pFix,       /* Context of the fixation */
  Select *pSelect      /* The SELECT statement to be fixed to one database */
){
  while( pSelect ){
    if( sqlite3FixExprList(pFix, pSelect->pEList) ){
      return 1;
    }
    if( sqlite3FixSrcList(pFix, pSelect->pSrc) ){
      return 1;
    }
    if( sqlite3FixExpr(pFix, pSelect->pWhere) ){
      return 1;
    }
    if( sqlite3FixExprList(pFix, pSelect->pGroupBy) ){
      return 1;
    }
    if( sqlite3FixExpr(pFix, pSelect->pHaving) ){
      return 1;
    }
    if( sqlite3FixExprList(pFix, pSelect->pOrderBy) ){
      return 1;
    }
    if( sqlite3FixExpr(pFix, pSelect->pLimit) ){
      return 1;
    }
    if( pSelect->pWith ){
      int i;
      for(i=0; i<pSelect->pWith->nCte; i++){
        if( sqlite3FixSelect(pFix, pSelect->pWith->a[i].pSelect) ){
          return 1;
        }
      }
    }
    pSelect = pSelect->pPrior;
  }
  return 0;
}