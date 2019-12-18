#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* pNC; } ;
struct TYPE_7__ {scalar_t__ pParse; TYPE_1__ u; scalar_t__ walkerDepth; int /*<<< orphan*/  xSelectCallback2; int /*<<< orphan*/  xSelectCallback; int /*<<< orphan*/  xExprCallback; } ;
typedef  TYPE_2__ Walker ;
struct TYPE_8__ {scalar_t__ pSrcList; } ;
typedef  TYPE_3__ NameContext ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  analyzeAggregate ; 
 int /*<<< orphan*/  analyzeAggregatesInSelect ; 
 int /*<<< orphan*/  analyzeAggregatesInSelectEnd ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3WalkExpr (TYPE_2__*,int /*<<< orphan*/ *) ; 

void sqlite3ExprAnalyzeAggregates(NameContext *pNC, Expr *pExpr){
  Walker w;
  w.xExprCallback = analyzeAggregate;
  w.xSelectCallback = analyzeAggregatesInSelect;
  w.xSelectCallback2 = analyzeAggregatesInSelectEnd;
  w.walkerDepth = 0;
  w.u.pNC = pNC;
  w.pParse = 0;
  assert( pNC->pSrcList!=0 );
  sqlite3WalkExpr(&w, pExpr);
}