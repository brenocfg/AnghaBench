#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int iCur; } ;
struct TYPE_10__ {int eCode; TYPE_1__ u; scalar_t__ xSelectCallback2; scalar_t__ xSelectCallback; int /*<<< orphan*/  xExprCallback; } ;
typedef  TYPE_2__ Walker ;
struct TYPE_11__ {scalar_t__ op; struct TYPE_11__* pRight; struct TYPE_11__* pLeft; } ;
typedef  TYPE_3__ Expr ;

/* Variables and functions */
 scalar_t__ TK_AND ; 
 scalar_t__ TK_NOTNULL ; 
 int /*<<< orphan*/  impliesNotNullRow ; 
 TYPE_3__* sqlite3ExprSkipCollate (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3WalkExpr (TYPE_2__*,TYPE_3__*) ; 

int sqlite3ExprImpliesNonNullRow(Expr *p, int iTab){
  Walker w;
  p = sqlite3ExprSkipCollate(p);
  while( p ){
    if( p->op==TK_NOTNULL ){
      p = p->pLeft;
    }else if( p->op==TK_AND ){
      if( sqlite3ExprImpliesNonNullRow(p->pLeft, iTab) ) return 1;
      p = p->pRight;
    }else{
      break;
    }
  }
  w.xExprCallback = impliesNotNullRow;
  w.xSelectCallback = 0;
  w.xSelectCallback2 = 0;
  w.eCode = 0;
  w.u.iCur = iTab;
  sqlite3WalkExpr(&w, p);
  return w.eCode;
}