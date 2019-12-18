#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  args; } ;
typedef  TYPE_1__ FuncExpr ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Var ; 
 scalar_t__ copyObject (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsecond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_bucket_has_const_period_and_offset (TYPE_1__*) ; 
 int /*<<< orphan*/ * ts_sort_transform_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Expr *
time_bucket_sort_transform(FuncExpr *func)
{
	/*
	 * time_bucket(const, var, const) => var
	 *
	 * proof: time_bucket(const1, time1) >= time_bucket(const1,time2) iff time1
	 * > time2
	 */
	Expr *second;

	Assert(list_length(func->args) >= 2);

	/*
	 * If period and offset are not constants we must not do the optimization
	 */
	if (!time_bucket_has_const_period_and_offset(func))
		return (Expr *) func;

	second = ts_sort_transform_expr(lsecond(func->args));

	if (!IsA(second, Var))
		return (Expr *) func;

	return (Expr *) copyObject(second);
}