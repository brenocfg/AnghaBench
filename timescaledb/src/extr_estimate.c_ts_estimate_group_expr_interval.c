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
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 double INVALID_ESTIMATE ; 
 int /*<<< orphan*/  IS_VALID_ESTIMATE (double) ; 
 double clamp_row_est (double) ; 
 double estimate_max_spread_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

double
ts_estimate_group_expr_interval(PlannerInfo *root, Expr *expr, double interval_period)
{
	double max_period;

	if (interval_period <= 0)
		return INVALID_ESTIMATE;

	max_period = estimate_max_spread_expr(root, expr);
	if (!IS_VALID_ESTIMATE(max_period))
		return INVALID_ESTIMATE;

	return clamp_row_est(max_period / interval_period);
}