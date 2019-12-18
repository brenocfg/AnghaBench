#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_6__ {TYPE_3__* ms_unflushed_allocs; TYPE_3__* ms_unflushed_frees; } ;
typedef  TYPE_2__ metaslab_t ;
struct TYPE_5__ {int bt_elem_size; } ;
struct TYPE_7__ {TYPE_1__ rt_root; } ;

/* Variables and functions */
 int range_tree_numsegs (TYPE_3__*) ; 

uint64_t
metaslab_unflushed_changes_memused(metaslab_t *ms)
{
	return ((range_tree_numsegs(ms->ms_unflushed_allocs) +
	    range_tree_numsegs(ms->ms_unflushed_frees)) *
	    ms->ms_unflushed_allocs->rt_root.bt_elem_size);
}