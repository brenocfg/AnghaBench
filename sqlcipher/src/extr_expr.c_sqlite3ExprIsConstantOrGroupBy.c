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
struct TYPE_4__ {int /*<<< orphan*/ * pGroupBy; } ;
struct TYPE_5__ {int eCode; int /*<<< orphan*/ * pParse; TYPE_1__ u; scalar_t__ xSelectCallback; int /*<<< orphan*/  xExprCallback; } ;
typedef  TYPE_2__ Walker ;
typedef  int /*<<< orphan*/  Parse ;
typedef  int /*<<< orphan*/  ExprList ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  exprNodeIsConstantOrGroupBy ; 
 int /*<<< orphan*/  sqlite3WalkExpr (TYPE_2__*,int /*<<< orphan*/ *) ; 

int sqlite3ExprIsConstantOrGroupBy(Parse *pParse, Expr *p, ExprList *pGroupBy){
  Walker w;
  w.eCode = 1;
  w.xExprCallback = exprNodeIsConstantOrGroupBy;
  w.xSelectCallback = 0;
  w.u.pGroupBy = pGroupBy;
  w.pParse = pParse;
  sqlite3WalkExpr(&w, p);
  return w.eCode;
}