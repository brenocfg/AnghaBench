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
typedef  int /*<<< orphan*/  Walker ;
struct TYPE_3__ {int nExpr; struct ExprList_item* a; } ;
typedef  TYPE_1__ ExprList ;

/* Variables and functions */
 int WRC_Abort ; 
 int WRC_Continue ; 
 scalar_t__ sqlite3WalkExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sqlite3WalkExprList(Walker *pWalker, ExprList *p){
  int i;
  struct ExprList_item *pItem;
  if( p ){
    for(i=p->nExpr, pItem=p->a; i>0; i--, pItem++){
      if( sqlite3WalkExpr(pWalker, pItem->pExpr) ) return WRC_Abort;
    }
  }
  return WRC_Continue;
}