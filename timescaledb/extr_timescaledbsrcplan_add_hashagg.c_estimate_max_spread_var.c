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
typedef  scalar_t__ int64 ;
typedef  int /*<<< orphan*/  VariableStatData ;
struct TYPE_3__ {int /*<<< orphan*/  vartype; } ;
typedef  TYPE_1__ Var ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  FlushErrorState () ; 
 double INVALID_ESTIMATE ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  ReleaseVariableStats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  examine_variable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_sort_group_operators (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ts_get_variable_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ts_time_value_to_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static double
estimate_max_spread_var(PlannerInfo *root, Var *var)
{
	VariableStatData vardata;
	Oid ltop;
	Datum max_datum, min_datum;
	volatile int64 max, min;
	volatile bool valid;

	examine_variable(root, (Node *) var, 0, &vardata);
	get_sort_group_operators(var->vartype, true, false, false, &ltop, NULL, NULL, NULL);
	valid = ts_get_variable_range(root, &vardata, ltop, &min_datum, &max_datum);
	ReleaseVariableStats(vardata);

	if (!valid)
		return INVALID_ESTIMATE;

	PG_TRY();
	{
		max = ts_time_value_to_internal(max_datum, var->vartype);
		min = ts_time_value_to_internal(min_datum, var->vartype);
	}
	PG_CATCH();
	{
		valid = false;
		FlushErrorState();
	}
	PG_END_TRY();

	if (!valid)
		return INVALID_ESTIMATE;

	return (double) (max - min);
}