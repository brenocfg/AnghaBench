#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* space; } ;
struct TYPE_11__ {TYPE_2__* parse; } ;
struct TYPE_10__ {scalar_t__ sortClause; } ;
struct TYPE_9__ {int num_dimensions; } ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  TYPE_3__ PlannerInfo ;
typedef  TYPE_4__ Hypertable ;

/* Variables and functions */
 scalar_t__ NIL ; 
 scalar_t__ ts_guc_disable_optimizations ; 
 int /*<<< orphan*/  ts_guc_enable_ordered_append ; 
 int ts_ordered_append_should_optimize (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*,int*) ; 

__attribute__((used)) static bool
should_order_append(PlannerInfo *root, RelOptInfo *rel, Hypertable *ht, bool *reverse)
{
	/* check if optimizations are enabled */
	if (ts_guc_disable_optimizations || !ts_guc_enable_ordered_append)
		return false;

	/*
	 * only do this optimization for hypertables with 1 dimension and queries
	 * with an ORDER BY clause
	 */
	if (ht->space->num_dimensions != 1 || root->parse->sortClause == NIL)
		return false;

	return ts_ordered_append_should_optimize(root, rel, ht, reverse);
}