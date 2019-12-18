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
typedef  int uint64_t ;
struct TYPE_5__ {int ms_weight; int /*<<< orphan*/  ms_group; int /*<<< orphan*/  ms_lock; } ;
typedef  TYPE_1__ metaslab_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int METASLAB_ACTIVE_MASK ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_group_sort (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int metaslab_weight (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
metaslab_recalculate_weight_and_sort(metaslab_t *msp)
{
	ASSERT(MUTEX_HELD(&msp->ms_lock));

	/* note: we preserve the mask (e.g. indication of primary, etc..) */
	uint64_t was_active = msp->ms_weight & METASLAB_ACTIVE_MASK;
	metaslab_group_sort(msp->ms_group, msp,
	    metaslab_weight(msp, B_FALSE) | was_active);
}