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
struct TYPE_3__ {scalar_t__ zl_sync; int /*<<< orphan*/  zl_replaying_seq; int /*<<< orphan*/ * zl_replayed_seq; int /*<<< orphan*/  zl_os; scalar_t__ zl_replay; } ;
typedef  TYPE_1__ zilog_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 size_t TXG_MASK ; 
 scalar_t__ ZFS_SYNC_DISABLED ; 
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ ) ; 
 size_t dmu_tx_get_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

boolean_t
zil_replaying(zilog_t *zilog, dmu_tx_t *tx)
{
	if (zilog->zl_sync == ZFS_SYNC_DISABLED)
		return (B_TRUE);

	if (zilog->zl_replay) {
		dsl_dataset_dirty(dmu_objset_ds(zilog->zl_os), tx);
		zilog->zl_replayed_seq[dmu_tx_get_txg(tx) & TXG_MASK] =
		    zilog->zl_replaying_seq;
		return (B_TRUE);
	}

	return (B_FALSE);
}