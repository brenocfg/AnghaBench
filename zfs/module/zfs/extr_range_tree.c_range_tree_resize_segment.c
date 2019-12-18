#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_13__ {int /*<<< orphan*/  rt_space; int /*<<< orphan*/  rt_arg; TYPE_1__* rt_ops; } ;
typedef  TYPE_2__ range_tree_t ;
typedef  int /*<<< orphan*/  range_seg_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* rtop_add ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* rtop_remove ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  range_tree_stat_decr (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_stat_incr (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ rs_get_end (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ rs_get_start (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  rs_set_end (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  rs_set_start (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
range_tree_resize_segment(range_tree_t *rt, range_seg_t *rs,
    uint64_t newstart, uint64_t newsize)
{
	int64_t delta = newsize - (rs_get_end(rs, rt) - rs_get_start(rs, rt));

	range_tree_stat_decr(rt, rs);
	if (rt->rt_ops != NULL && rt->rt_ops->rtop_remove != NULL)
		rt->rt_ops->rtop_remove(rt, rs, rt->rt_arg);

	rs_set_start(rs, rt, newstart);
	rs_set_end(rs, rt, newstart + newsize);

	range_tree_stat_incr(rt, rs);
	if (rt->rt_ops != NULL && rt->rt_ops->rtop_add != NULL)
		rt->rt_ops->rtop_add(rt, rs, rt->rt_arg);

	rt->rt_space += delta;
}