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
struct TYPE_3__ {int /*<<< orphan*/  opno; int /*<<< orphan*/  args; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ OpExpr ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  Const ; 
 double INVALID_ESTIMATE ; 
 scalar_t__ IS_VALID_ESTIMATE (double) ; 
 scalar_t__ IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * eval_const_expressions (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 double group_estimate_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double) ; 
 double group_estimate_integer_division (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsecond (int /*<<< orphan*/ ) ; 

__attribute__((used)) static double
group_estimate_opexpr(PlannerInfo *root, OpExpr *opexpr, double path_rows)
{
	Node *first;
	Node *second;
	double estimate;

	if (list_length(opexpr->args) != 2)
		return INVALID_ESTIMATE;

	first = eval_const_expressions(root, linitial(opexpr->args));
	second = eval_const_expressions(root, lsecond(opexpr->args));

	estimate = group_estimate_integer_division(root, opexpr->opno, first, second);
	if (IS_VALID_ESTIMATE(estimate))
		return estimate;

	if (IsA(first, Const))
		return group_estimate_expr(root, second, path_rows);
	if (IsA(second, Const))
		return group_estimate_expr(root, first, path_rows);
	return INVALID_ESTIMATE;
}