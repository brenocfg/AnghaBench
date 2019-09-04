#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {double (* custom_group_estimate_func ) (int /*<<< orphan*/ *,TYPE_1__*,double) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  funcid; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ FuncExpr ;
typedef  TYPE_2__ CustomEstimateForFunctionInfo ;

/* Variables and functions */
 double INVALID_ESTIMATE ; 
 TYPE_2__* get_custom_estimate_func_info (int /*<<< orphan*/ ) ; 
 double stub1 (int /*<<< orphan*/ *,TYPE_1__*,double) ; 

__attribute__((used)) static double
custom_group_estimate_funcexpr(PlannerInfo *root, FuncExpr *custom_group_estimate_func,
							   double path_rows)
{
	CustomEstimateForFunctionInfo *func_est =
		get_custom_estimate_func_info(custom_group_estimate_func->funcid);

	if (NULL != func_est)
		return func_est->custom_group_estimate_func(root, custom_group_estimate_func, path_rows);
	return INVALID_ESTIMATE;
}