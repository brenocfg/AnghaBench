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
struct ExprList_item {int /*<<< orphan*/  pExpr; } ;
struct TYPE_3__ {int nExpr; struct ExprList_item* a; } ;
typedef  int /*<<< orphan*/  NameContext ;
typedef  TYPE_1__ ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3ExprAnalyzeAggregates (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sqlite3ExprAnalyzeAggList(NameContext *pNC, ExprList *pList){
  struct ExprList_item *pItem;
  int i;
  if( pList ){
    for(pItem=pList->a, i=0; i<pList->nExpr; i++, pItem++){
      sqlite3ExprAnalyzeAggregates(pNC, pItem->pExpr);
    }
  }
}