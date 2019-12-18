#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {struct TYPE_4__* zSpan; int /*<<< orphan*/  pUpsert; int /*<<< orphan*/  pIdList; int /*<<< orphan*/  pSelect; int /*<<< orphan*/  pExprList; int /*<<< orphan*/  pWhere; struct TYPE_4__* pNext; } ;
typedef  TYPE_1__ TriggerStep ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3IdListDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SelectDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3UpsertDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sqlite3DeleteTriggerStep(sqlite3 *db, TriggerStep *pTriggerStep){
  while( pTriggerStep ){
    TriggerStep * pTmp = pTriggerStep;
    pTriggerStep = pTriggerStep->pNext;

    sqlite3ExprDelete(db, pTmp->pWhere);
    sqlite3ExprListDelete(db, pTmp->pExprList);
    sqlite3SelectDelete(db, pTmp->pSelect);
    sqlite3IdListDelete(db, pTmp->pIdList);
    sqlite3UpsertDelete(db, pTmp->pUpsert);
    sqlite3DbFree(db, pTmp->zSpan);

    sqlite3DbFree(db, pTmp);
  }
}