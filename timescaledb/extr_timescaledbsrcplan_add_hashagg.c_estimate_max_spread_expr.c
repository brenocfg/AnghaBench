#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Var ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  OpExpr ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 double INVALID_ESTIMATE ; 
#define  T_OpExpr 129 
#define  T_Var 128 
 double estimate_max_spread_opexpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double estimate_max_spread_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static double
estimate_max_spread_expr(PlannerInfo *root, Expr *expr)
{
	switch (nodeTag(expr))
	{
		case T_Var:
			return estimate_max_spread_var(root, (Var *) expr);
		case T_OpExpr:
			return estimate_max_spread_opexpr(root, (OpExpr *) expr);
		default:
			return INVALID_ESTIMATE;
	}
}