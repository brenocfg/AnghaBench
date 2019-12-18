#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* dn_dbuf; int /*<<< orphan*/  dn_holds; } ;
typedef  TYPE_2__ dnode_t ;
struct TYPE_8__ {TYPE_2__* dnh_dnode; int /*<<< orphan*/  dnh_zrlock; } ;
typedef  TYPE_3__ dnode_handle_t ;
struct TYPE_6__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/ * dmu_buf_get_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dnode_destroy (TYPE_2__*) ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zrl_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zrl_destroy (int /*<<< orphan*/ *) ; 

void
dnode_special_close(dnode_handle_t *dnh)
{
	dnode_t *dn = dnh->dnh_dnode;

	/*
	 * Wait for final references to the dnode to clear.  This can
	 * only happen if the arc is asynchronously evicting state that
	 * has a hold on this dnode while we are trying to evict this
	 * dnode.
	 */
	while (zfs_refcount_count(&dn->dn_holds) > 0)
		delay(1);
	ASSERT(dn->dn_dbuf == NULL ||
	    dmu_buf_get_user(&dn->dn_dbuf->db) == NULL);
	zrl_add(&dnh->dnh_zrlock);
	dnode_destroy(dn); /* implicit zrl_remove() */
	zrl_destroy(&dnh->dnh_zrlock);
	dnh->dnh_dnode = NULL;
}