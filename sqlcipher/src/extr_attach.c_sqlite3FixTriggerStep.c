#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pUpsertWhere; int /*<<< orphan*/  pUpsertSet; int /*<<< orphan*/  pUpsertTargetWhere; int /*<<< orphan*/  pUpsertTarget; } ;
typedef  TYPE_1__ Upsert ;
struct TYPE_5__ {struct TYPE_5__* pNext; TYPE_1__* pUpsert; int /*<<< orphan*/  pExprList; int /*<<< orphan*/  pWhere; int /*<<< orphan*/  pSelect; } ;
typedef  TYPE_2__ TriggerStep ;
typedef  int /*<<< orphan*/  DbFixer ;

/* Variables and functions */
 scalar_t__ sqlite3FixExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3FixExprList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3FixSelect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sqlite3FixTriggerStep(
  DbFixer *pFix,     /* Context of the fixation */
  TriggerStep *pStep /* The trigger step be fixed to one database */
){
  while( pStep ){
    if( sqlite3FixSelect(pFix, pStep->pSelect) ){
      return 1;
    }
    if( sqlite3FixExpr(pFix, pStep->pWhere) ){
      return 1;
    }
    if( sqlite3FixExprList(pFix, pStep->pExprList) ){
      return 1;
    }
#ifndef SQLITE_OMIT_UPSERT
    if( pStep->pUpsert ){
      Upsert *pUp = pStep->pUpsert;
      if( sqlite3FixExprList(pFix, pUp->pUpsertTarget)
       || sqlite3FixExpr(pFix, pUp->pUpsertTargetWhere)
       || sqlite3FixExprList(pFix, pUp->pUpsertSet)
       || sqlite3FixExpr(pFix, pUp->pUpsertWhere)
      ){
        return 1;
      }
    }
#endif
    pStep = pStep->pNext;
  }
  return 0;
}