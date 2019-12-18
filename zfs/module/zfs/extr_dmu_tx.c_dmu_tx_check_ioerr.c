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
typedef  int /*<<< orphan*/  zio_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  dn_struct_rwlock; } ;
typedef  TYPE_1__ dnode_t ;
typedef  int /*<<< orphan*/  dmu_buf_impl_t ;

/* Variables and functions */
 int DB_RF_CANFAIL ; 
 int DB_RF_NOPREFETCH ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dbuf_hold_level (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dbuf_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dbuf_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dmu_tx_check_ioerr(zio_t *zio, dnode_t *dn, int level, uint64_t blkid)
{
	int err;
	dmu_buf_impl_t *db;

	rw_enter(&dn->dn_struct_rwlock, RW_READER);
	db = dbuf_hold_level(dn, level, blkid, FTAG);
	rw_exit(&dn->dn_struct_rwlock);
	if (db == NULL)
		return (SET_ERROR(EIO));
	err = dbuf_read(db, zio, DB_RF_CANFAIL | DB_RF_NOPREFETCH);
	dbuf_rele(db, FTAG);
	return (err);
}