#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  dn_struct_rwlock; TYPE_9__* dn_phys; TYPE_3__* dn_dbuf; } ;
typedef  TYPE_2__ dnode_t ;
struct TYPE_11__ {scalar_t__ db_data; } ;
struct TYPE_13__ {scalar_t__ db_blkid; int db_level; TYPE_1__ db; int /*<<< orphan*/ * db_blkptr; struct TYPE_13__* db_parent; int /*<<< orphan*/  db_mtx; } ;
typedef  TYPE_3__ dmu_buf_impl_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
struct TYPE_14__ {int dn_nlevels; scalar_t__ dn_nblkptr; int dn_indblkshift; int /*<<< orphan*/ * dn_blkptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BP_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DBUF_VERIFY (TYPE_3__*) ; 
 scalar_t__ DMU_SPILL_BLKID ; 
 int /*<<< orphan*/ * DN_SPILL_BLKPTR (TYPE_9__*) ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_READER ; 
 int SPA_BLKPTRSHIFT ; 
 TYPE_3__* dbuf_hold_level (TYPE_2__*,int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dbuf_check_blkptr(dnode_t *dn, dmu_buf_impl_t *db)
{
	/* ASSERT(dmu_tx_is_syncing(tx) */
	ASSERT(MUTEX_HELD(&db->db_mtx));

	if (db->db_blkptr != NULL)
		return;

	if (db->db_blkid == DMU_SPILL_BLKID) {
		db->db_blkptr = DN_SPILL_BLKPTR(dn->dn_phys);
		BP_ZERO(db->db_blkptr);
		return;
	}
	if (db->db_level == dn->dn_phys->dn_nlevels-1) {
		/*
		 * This buffer was allocated at a time when there was
		 * no available blkptrs from the dnode, or it was
		 * inappropriate to hook it in (i.e., nlevels mismatch).
		 */
		ASSERT(db->db_blkid < dn->dn_phys->dn_nblkptr);
		ASSERT(db->db_parent == NULL);
		db->db_parent = dn->dn_dbuf;
		db->db_blkptr = &dn->dn_phys->dn_blkptr[db->db_blkid];
		DBUF_VERIFY(db);
	} else {
		dmu_buf_impl_t *parent = db->db_parent;
		int epbs = dn->dn_phys->dn_indblkshift - SPA_BLKPTRSHIFT;

		ASSERT(dn->dn_phys->dn_nlevels > 1);
		if (parent == NULL) {
			mutex_exit(&db->db_mtx);
			rw_enter(&dn->dn_struct_rwlock, RW_READER);
			parent = dbuf_hold_level(dn, db->db_level + 1,
			    db->db_blkid >> epbs, db);
			rw_exit(&dn->dn_struct_rwlock);
			mutex_enter(&db->db_mtx);
			db->db_parent = parent;
		}
		db->db_blkptr = (blkptr_t *)parent->db.db_data +
		    (db->db_blkid & ((1ULL << epbs) - 1));
		DBUF_VERIFY(db);
	}
}