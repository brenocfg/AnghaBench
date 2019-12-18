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
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  OpExpr ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  FuncExpr ;

/* Variables and functions */
 double INVALID_ESTIMATE ; 
#define  T_FuncExpr 129 
#define  T_OpExpr 128 
 double group_estimate_funcexpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double) ; 
 double group_estimate_opexpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static double
group_estimate_expr(PlannerInfo *root, Node *expr, double path_rows)
{
	switch (nodeTag(expr))
	{
		case T_FuncExpr:
			return group_estimate_funcexpr(root, (FuncExpr *) expr, path_rows);
		case T_OpExpr:
			return group_estimate_opexpr(root, (OpExpr *) expr, path_rows);
		default:
			return INVALID_ESTIMATE;
	}
}