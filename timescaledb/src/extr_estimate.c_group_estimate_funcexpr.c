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
struct TYPE_7__ {int /*<<< orphan*/  funcid; } ;
struct TYPE_6__ {double (* group_estimate ) (int /*<<< orphan*/ *,TYPE_2__*,double) ;} ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ FuncInfo ;
typedef  TYPE_2__ FuncExpr ;

/* Variables and functions */
 double INVALID_ESTIMATE ; 
 double stub1 (int /*<<< orphan*/ *,TYPE_2__*,double) ; 
 TYPE_1__* ts_func_cache_get_bucketing_func (int /*<<< orphan*/ ) ; 

__attribute__((used)) static double
group_estimate_funcexpr(PlannerInfo *root, FuncExpr *group_estimate_func, double path_rows)
{
	FuncInfo *func_est = ts_func_cache_get_bucketing_func(group_estimate_func->funcid);

	if (NULL != func_est)
		return func_est->group_estimate(root, group_estimate_func, path_rows);
	return INVALID_ESTIMATE;
}