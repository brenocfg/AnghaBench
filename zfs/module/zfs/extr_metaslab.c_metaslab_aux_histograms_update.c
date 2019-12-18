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
struct TYPE_5__ {int /*<<< orphan*/  sm_shift; } ;
typedef  TYPE_1__ space_map_t ;
struct TYPE_6__ {int /*<<< orphan*/  ms_freeing; int /*<<< orphan*/  ms_synchist; int /*<<< orphan*/ * ms_defer; int /*<<< orphan*/ * ms_deferhist; int /*<<< orphan*/  ms_freed; scalar_t__ ms_loaded; TYPE_1__* ms_sm; } ;
typedef  TYPE_2__ metaslab_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int TXG_DEFER_SIZE ; 
 int /*<<< orphan*/  metaslab_aux_histogram_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_aux_histograms_clear (TYPE_2__*) ; 

__attribute__((used)) static void
metaslab_aux_histograms_update(metaslab_t *msp)
{
	space_map_t *sm = msp->ms_sm;
	ASSERT(sm != NULL);

	/*
	 * This is similar to the metaslab's space map histogram updates
	 * that take place in metaslab_sync(). The only difference is that
	 * we only care about segments that haven't made it into the
	 * ms_allocatable tree yet.
	 */
	if (msp->ms_loaded) {
		metaslab_aux_histograms_clear(msp);

		metaslab_aux_histogram_add(msp->ms_synchist,
		    sm->sm_shift, msp->ms_freed);

		for (int t = 0; t < TXG_DEFER_SIZE; t++) {
			metaslab_aux_histogram_add(msp->ms_deferhist[t],
			    sm->sm_shift, msp->ms_defer[t]);
		}
	}

	metaslab_aux_histogram_add(msp->ms_synchist,
	    sm->sm_shift, msp->ms_freeing);
}