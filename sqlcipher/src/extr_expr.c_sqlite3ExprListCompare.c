#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_5__ {scalar_t__ sortOrder; int /*<<< orphan*/ * pExpr; } ;
typedef  TYPE_2__ ExprList ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ sqlite3ExprCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int sqlite3ExprListCompare(ExprList *pA, ExprList *pB, int iTab){
  int i;
  if( pA==0 && pB==0 ) return 0;
  if( pA==0 || pB==0 ) return 1;
  if( pA->nExpr!=pB->nExpr ) return 1;
  for(i=0; i<pA->nExpr; i++){
    Expr *pExprA = pA->a[i].pExpr;
    Expr *pExprB = pB->a[i].pExpr;
    if( pA->a[i].sortOrder!=pB->a[i].sortOrder ) return 1;
    if( sqlite3ExprCompare(0, pExprA, pExprB, iTab) ) return 1;
  }
  return 0;
}