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
struct TYPE_3__ {int /*<<< orphan*/  args; int /*<<< orphan*/  opno; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ OpExpr ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  Const ; 
 double INVALID_ESTIMATE ; 
 scalar_t__ IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 double estimate_max_spread_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* get_opname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lsecond (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static double
estimate_max_spread_opexpr(PlannerInfo *root, OpExpr *opexpr)
{
	char *function_name = get_opname(opexpr->opno);
	Expr *left;
	Expr *right;
	Expr *nonconst;

	if (list_length(opexpr->args) != 2 || strlen(function_name) != 1)
		return INVALID_ESTIMATE;

	left = linitial(opexpr->args);
	right = lsecond(opexpr->args);

	if (IsA(left, Const))
		nonconst = right;
	else if (IsA(right, Const))
		nonconst = left;
	else
		return INVALID_ESTIMATE;

	/* adding or subtracting a constant doesn't affect the range */
	if (function_name[0] == '-' || function_name[0] == '+')
		return estimate_max_spread_expr(root, nonconst);

	return INVALID_ESTIMATE;
}