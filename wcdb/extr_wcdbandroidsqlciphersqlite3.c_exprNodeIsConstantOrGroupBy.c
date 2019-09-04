#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* pGroupBy; } ;
struct TYPE_9__ {scalar_t__ eCode; int /*<<< orphan*/  pParse; TYPE_1__ u; } ;
typedef  TYPE_3__ Walker ;
struct TYPE_10__ {int nExpr; TYPE_2__* a; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pExpr; } ;
typedef  TYPE_4__ ExprList ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  EP_xIsSelect ; 
 scalar_t__ ExprHasProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int WRC_Abort ; 
 int WRC_Prune ; 
 int exprNodeIsConstant (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int sqlite3ExprCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sqlite3ExprNNCollSeq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3IsBinary (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exprNodeIsConstantOrGroupBy(Walker *pWalker, Expr *pExpr){
  ExprList *pGroupBy = pWalker->u.pGroupBy;
  int i;

  /* Check if pExpr is identical to any GROUP BY term. If so, consider
  ** it constant.  */
  for(i=0; i<pGroupBy->nExpr; i++){
    Expr *p = pGroupBy->a[i].pExpr;
    if( sqlite3ExprCompare(0, pExpr, p, -1)<2 ){
      CollSeq *pColl = sqlite3ExprNNCollSeq(pWalker->pParse, p);
      if( sqlite3IsBinary(pColl) ){
        return WRC_Prune;
      }
    }
  }

  /* Check if pExpr is a sub-select. If so, consider it variable. */
  if( ExprHasProperty(pExpr, EP_xIsSelect) ){
    pWalker->eCode = 0;
    return WRC_Abort;
  }

  return exprNodeIsConstant(pWalker, pExpr);
}