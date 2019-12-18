#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  vdev_mg; int /*<<< orphan*/  vdev_ms_list; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  metaslab_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXG_CLEAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_sync_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_sync_reassess (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_list_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * txg_list_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_is_concrete (TYPE_1__*) ; 

void
vdev_sync_done(vdev_t *vd, uint64_t txg)
{
	metaslab_t *msp;
	boolean_t reassess = !txg_list_empty(&vd->vdev_ms_list, TXG_CLEAN(txg));

	ASSERT(vdev_is_concrete(vd));

	while ((msp = txg_list_remove(&vd->vdev_ms_list, TXG_CLEAN(txg)))
	    != NULL)
		metaslab_sync_done(msp, txg);

	if (reassess)
		metaslab_sync_reassess(vd->vdev_mg);
}