#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  z_id; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zilog_t ;
typedef  int uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  lr_doid; } ;
typedef  TYPE_2__ lr_remove_t ;
struct TYPE_10__ {int itx_oid; int /*<<< orphan*/  itx_lr; } ;
typedef  TYPE_3__ itx_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int TX_CI ; 
 int TX_REMOVE ; 
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 int strlen (char*) ; 
 scalar_t__ zfs_xattr_owner_unlinked (TYPE_1__*) ; 
 int /*<<< orphan*/  zil_itx_assign (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* zil_itx_create (int,int) ; 
 int /*<<< orphan*/  zil_remove_async (int /*<<< orphan*/ *,int) ; 
 scalar_t__ zil_replaying (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
zfs_log_remove(zilog_t *zilog, dmu_tx_t *tx, uint64_t txtype,
    znode_t *dzp, char *name, uint64_t foid, boolean_t unlinked)
{
	itx_t *itx;
	lr_remove_t *lr;
	size_t namesize = strlen(name) + 1;

	if (zil_replaying(zilog, tx) || zfs_xattr_owner_unlinked(dzp))
		return;

	itx = zil_itx_create(txtype, sizeof (*lr) + namesize);
	lr = (lr_remove_t *)&itx->itx_lr;
	lr->lr_doid = dzp->z_id;
	bcopy(name, (char *)(lr + 1), namesize);

	itx->itx_oid = foid;

	/*
	 * Object ids can be re-instantiated in the next txg so
	 * remove any async transactions to avoid future leaks.
	 * This can happen if a fsync occurs on the re-instantiated
	 * object for a WR_INDIRECT or WR_NEED_COPY write, which gets
	 * the new file data and flushes a write record for the old object.
	 */
	if (unlinked) {
		ASSERT((txtype & ~TX_CI) == TX_REMOVE);
		zil_remove_async(zilog, foid);
	}
	zil_itx_assign(zilog, itx, tx);
}