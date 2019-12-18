#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ tx_txg; } ;
typedef  TYPE_2__ dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;
struct TYPE_9__ {scalar_t__ db_object; } ;
struct TYPE_11__ {scalar_t__ db_blkid; scalar_t__ db_level; TYPE_1__ db; int /*<<< orphan*/  db_holds; } ;
typedef  TYPE_3__ dmu_buf_impl_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DMU_BONUS_BLKID ; 
 scalar_t__ DMU_META_DNODE_OBJECT ; 
 int /*<<< orphan*/  dbuf_dirty (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dbuf_noread (TYPE_3__*) ; 
 scalar_t__ dmu_tx_private_ok (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_refcount_is_zero (int /*<<< orphan*/ *) ; 

void
dmu_buf_will_fill(dmu_buf_t *db_fake, dmu_tx_t *tx)
{
	dmu_buf_impl_t *db = (dmu_buf_impl_t *)db_fake;

	ASSERT(db->db_blkid != DMU_BONUS_BLKID);
	ASSERT(tx->tx_txg != 0);
	ASSERT(db->db_level == 0);
	ASSERT(!zfs_refcount_is_zero(&db->db_holds));

	ASSERT(db->db.db_object != DMU_META_DNODE_OBJECT ||
	    dmu_tx_private_ok(tx));

	dbuf_noread(db);
	(void) dbuf_dirty(db, tx);
}