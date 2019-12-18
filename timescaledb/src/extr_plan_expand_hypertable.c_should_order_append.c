#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* parse; } ;
struct TYPE_5__ {scalar_t__ sortClause; } ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  TYPE_2__ PlannerInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Hypertable ;

/* Variables and functions */
 scalar_t__ NIL ; 
 scalar_t__ ts_guc_disable_optimizations ; 
 int /*<<< orphan*/  ts_guc_enable_chunk_append ; 
 int /*<<< orphan*/  ts_guc_enable_ordered_append ; 
 int ts_ordered_append_should_optimize (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static bool
should_order_append(PlannerInfo *root, RelOptInfo *rel, Hypertable *ht, List *join_conditions,
					int *order_attno, bool *reverse)
{
	/* check if optimizations are enabled */
	if (ts_guc_disable_optimizations || !ts_guc_enable_ordered_append ||
		!ts_guc_enable_chunk_append)
		return false;

	/*
	 * only do this optimization for hypertables with 1 dimension and queries
	 * with an ORDER BY clause
	 */
	if (root->parse->sortClause == NIL)
		return false;

	return ts_ordered_append_should_optimize(root, rel, ht, join_conditions, order_attno, reverse);
}