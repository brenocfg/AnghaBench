#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  ms_lock; } ;
typedef  TYPE_1__ metaslab_t ;
struct TYPE_8__ {int /*<<< orphan*/  mg_lock; } ;
typedef  TYPE_2__ metaslab_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 scalar_t__ SPA_MINBLOCKSIZE ; 
 int /*<<< orphan*/  metaslab_group_sort_impl (TYPE_2__*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
metaslab_group_sort(metaslab_group_t *mg, metaslab_t *msp, uint64_t weight)
{
	/*
	 * Although in principle the weight can be any value, in
	 * practice we do not use values in the range [1, 511].
	 */
	ASSERT(weight >= SPA_MINBLOCKSIZE || weight == 0);
	ASSERT(MUTEX_HELD(&msp->ms_lock));

	mutex_enter(&mg->mg_lock);
	metaslab_group_sort_impl(mg, msp, weight);
	mutex_exit(&mg->mg_lock);
}