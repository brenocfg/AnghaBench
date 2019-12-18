#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct mssa_arg {int /*<<< orphan*/ * mra; int /*<<< orphan*/ * rt; } ;
typedef  int /*<<< orphan*/  range_tree_t ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ range_seg_max_t ;
typedef  int /*<<< orphan*/  metaslab_rt_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  metaslab_rt_add (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rs_set_end (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rs_set_start (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
metaslab_size_sorted_add(void *arg, uint64_t start, uint64_t size)
{
	struct mssa_arg *mssap = arg;
	range_tree_t *rt = mssap->rt;
	metaslab_rt_arg_t *mrap = mssap->mra;
	range_seg_max_t seg = {0};
	rs_set_start(&seg, rt, start);
	rs_set_end(&seg, rt, start + size);
	metaslab_rt_add(rt, &seg, mrap);
}