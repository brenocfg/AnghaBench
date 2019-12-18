#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/ * dmu_tx_ksp ; 
 int /*<<< orphan*/  kstat_delete (int /*<<< orphan*/ *) ; 

void
dmu_tx_fini(void)
{
	if (dmu_tx_ksp != NULL) {
		kstat_delete(dmu_tx_ksp);
		dmu_tx_ksp = NULL;
	}
}