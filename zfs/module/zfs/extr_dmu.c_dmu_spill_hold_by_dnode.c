#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  dn_struct_rwlock; } ;
typedef  TYPE_1__ dnode_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;
struct TYPE_9__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ dmu_buf_impl_t ;

/* Variables and functions */
 int DB_RF_HAVESTRUCT ; 
 int /*<<< orphan*/  DMU_SPILL_BLKID ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  RW_READER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_2__* dbuf_hold (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int dbuf_read (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dbuf_rele (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 

int
dmu_spill_hold_by_dnode(dnode_t *dn, uint32_t flags, void *tag, dmu_buf_t **dbp)
{
	dmu_buf_impl_t *db = NULL;
	int err;

	if ((flags & DB_RF_HAVESTRUCT) == 0)
		rw_enter(&dn->dn_struct_rwlock, RW_READER);

	db = dbuf_hold(dn, DMU_SPILL_BLKID, tag);

	if ((flags & DB_RF_HAVESTRUCT) == 0)
		rw_exit(&dn->dn_struct_rwlock);

	if (db == NULL) {
		*dbp = NULL;
		return (SET_ERROR(EIO));
	}
	err = dbuf_read(db, NULL, flags);
	if (err == 0)
		*dbp = &db->db;
	else {
		dbuf_rele(db, tag);
		*dbp = NULL;
	}
	return (err);
}