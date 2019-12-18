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
struct TYPE_5__ {scalar_t__ ms_disabled; int ms_allocator; int ms_weight; int /*<<< orphan*/ * ms_allocating; int /*<<< orphan*/  ms_loaded; } ;
typedef  TYPE_1__ metaslab_t ;

/* Variables and functions */
 int METASLAB_ACTIVE_MASK ; 
 int TXG_CONCURRENT_STATES ; 
 int TXG_MASK ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_debug_unload ; 
 int /*<<< orphan*/  metaslab_passivate (TYPE_1__*,int) ; 
 int /*<<< orphan*/  metaslab_unload (TYPE_1__*) ; 
 int /*<<< orphan*/  range_tree_space (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
metaslab_evict(metaslab_t *msp, uint64_t txg)
{
	if (!msp->ms_loaded || msp->ms_disabled != 0)
		return;

	for (int t = 1; t < TXG_CONCURRENT_STATES; t++) {
		VERIFY0(range_tree_space(
		    msp->ms_allocating[(txg + t) & TXG_MASK]));
	}
	if (msp->ms_allocator != -1)
		metaslab_passivate(msp, msp->ms_weight & ~METASLAB_ACTIVE_MASK);

	if (!metaslab_debug_unload)
		metaslab_unload(msp);
}