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
struct TYPE_3__ {int /*<<< orphan*/  args; } ;
typedef  TYPE_1__ FuncExpr ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  Const ; 
 int /*<<< orphan*/  IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Var ; 
 scalar_t__ copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsecond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_sort_transform_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Expr *
date_trunc_sort_transform(FuncExpr *func)
{
	/*
	 * date_trunc (const, var) => var
	 *
	 * proof: date_trunc(c, time1) >= date_trunc(c,time2) iff time1 > time2
	 */
	Expr *second;

	if (list_length(func->args) != 2 || !IsA(linitial(func->args), Const))
		return (Expr *) func;

	second = ts_sort_transform_expr(lsecond(func->args));

	if (!IsA(second, Var))
		return (Expr *) func;

	return (Expr *) copyObject(second);
}