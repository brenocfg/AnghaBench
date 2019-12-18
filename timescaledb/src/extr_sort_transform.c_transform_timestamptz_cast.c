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
 int /*<<< orphan*/  IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Var ; 
 scalar_t__ copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_sort_transform_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Expr *
transform_timestamptz_cast(FuncExpr *func)
{
	/*
	 * Transform cast from date to timestamptz, or timestamp to timestamptz,
	 * or abstime to timestamptz Handles only single-argument versions of the
	 * cast to avoid explicit timezone specifiers
	 *
	 *
	 * timestamptz(var) => var
	 *
	 * proof: timestamptz(time1) >= timestamptz(time2) iff time1 > time2
	 *
	 */

	Expr *first;

	if (list_length(func->args) != 1)
		return (Expr *) func;

	first = ts_sort_transform_expr(linitial(func->args));
	if (!IsA(first, Var))
		return (Expr *) func;

	return (Expr *) copyObject(first);
}