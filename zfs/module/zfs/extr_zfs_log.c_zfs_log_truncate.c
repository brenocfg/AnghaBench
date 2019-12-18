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
struct TYPE_8__ {scalar_t__ z_sync_cnt; int /*<<< orphan*/  z_id; scalar_t__ z_unlinked; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zilog_t ;
typedef  void* uint64_t ;
struct TYPE_9__ {void* lr_length; void* lr_offset; int /*<<< orphan*/  lr_foid; } ;
typedef  TYPE_2__ lr_truncate_t ;
struct TYPE_10__ {int itx_sync; int /*<<< orphan*/  itx_lr; } ;
typedef  TYPE_3__ itx_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 scalar_t__ zfs_xattr_owner_unlinked (TYPE_1__*) ; 
 int /*<<< orphan*/  zil_itx_assign (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* zil_itx_create (int,int) ; 
 scalar_t__ zil_replaying (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
zfs_log_truncate(zilog_t *zilog, dmu_tx_t *tx, int txtype,
    znode_t *zp, uint64_t off, uint64_t len)
{
	itx_t *itx;
	lr_truncate_t *lr;

	if (zil_replaying(zilog, tx) || zp->z_unlinked ||
	    zfs_xattr_owner_unlinked(zp))
		return;

	itx = zil_itx_create(txtype, sizeof (*lr));
	lr = (lr_truncate_t *)&itx->itx_lr;
	lr->lr_foid = zp->z_id;
	lr->lr_offset = off;
	lr->lr_length = len;

	itx->itx_sync = (zp->z_sync_cnt != 0);
	zil_itx_assign(zilog, itx, tx);
}