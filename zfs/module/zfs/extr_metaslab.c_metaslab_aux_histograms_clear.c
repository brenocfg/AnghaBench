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
struct TYPE_3__ {int /*<<< orphan*/ * ms_deferhist; int /*<<< orphan*/  ms_synchist; int /*<<< orphan*/  ms_loaded; } ;
typedef  TYPE_1__ metaslab_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int TXG_DEFER_SIZE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
metaslab_aux_histograms_clear(metaslab_t *msp)
{
	/*
	 * Auxiliary histograms are only cleared when resetting them,
	 * which can only happen while the metaslab is loaded.
	 */
	ASSERT(msp->ms_loaded);

	bzero(msp->ms_synchist, sizeof (msp->ms_synchist));
	for (int t = 0; t < TXG_DEFER_SIZE; t++)
		bzero(msp->ms_deferhist[t], sizeof (msp->ms_deferhist[t]));
}