#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dn_tx_holds; int /*<<< orphan*/  dn_holds; } ;
typedef  TYPE_1__ dnode_t ;
struct TYPE_8__ {TYPE_1__* dnh_dnode; int /*<<< orphan*/  dnh_zrlock; } ;
typedef  TYPE_2__ dnode_handle_t ;
struct TYPE_9__ {int dnc_count; TYPE_2__* dnc_children; } ;
typedef  TYPE_3__ dnode_children_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DNODE_STAT_BUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DN_SLOT_IS_PTR (TYPE_1__*) ; 
 void* DN_SLOT_UNINIT ; 
 int /*<<< orphan*/  dnode_buf_evict ; 
 int /*<<< orphan*/  dnode_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 int /*<<< orphan*/  zfs_refcount_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zrl_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zrl_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dnode_buf_evict_async(void *dbu)
{
	dnode_children_t *dnc = dbu;

	DNODE_STAT_BUMP(dnode_buf_evict);

	for (int i = 0; i < dnc->dnc_count; i++) {
		dnode_handle_t *dnh = &dnc->dnc_children[i];
		dnode_t *dn;

		/*
		 * The dnode handle lock guards against the dnode moving to
		 * another valid address, so there is no need here to guard
		 * against changes to or from NULL.
		 */
		if (!DN_SLOT_IS_PTR(dnh->dnh_dnode)) {
			zrl_destroy(&dnh->dnh_zrlock);
			dnh->dnh_dnode = DN_SLOT_UNINIT;
			continue;
		}

		zrl_add(&dnh->dnh_zrlock);
		dn = dnh->dnh_dnode;
		/*
		 * If there are holds on this dnode, then there should
		 * be holds on the dnode's containing dbuf as well; thus
		 * it wouldn't be eligible for eviction and this function
		 * would not have been called.
		 */
		ASSERT(zfs_refcount_is_zero(&dn->dn_holds));
		ASSERT(zfs_refcount_is_zero(&dn->dn_tx_holds));

		dnode_destroy(dn); /* implicit zrl_remove() for first slot */
		zrl_destroy(&dnh->dnh_zrlock);
		dnh->dnh_dnode = DN_SLOT_UNINIT;
	}
	kmem_free(dnc, sizeof (dnode_children_t) +
	    dnc->dnc_count * sizeof (dnode_handle_t));
}