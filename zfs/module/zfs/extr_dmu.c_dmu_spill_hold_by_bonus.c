#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  dnode_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;
typedef  int /*<<< orphan*/  dmu_buf_impl_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DB_DNODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DB_DNODE_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DB_DNODE_EXIT (int /*<<< orphan*/ *) ; 
 int DB_RF_CANFAIL ; 
 int DB_RF_NO_DECRYPT ; 
 int DMU_READ_NO_DECRYPT ; 
 int dmu_spill_hold_by_dnode (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ **) ; 

int
dmu_spill_hold_by_bonus(dmu_buf_t *bonus, uint32_t flags, void *tag,
    dmu_buf_t **dbp)
{
	dmu_buf_impl_t *db = (dmu_buf_impl_t *)bonus;
	dnode_t *dn;
	int err;
	uint32_t db_flags = DB_RF_CANFAIL;

	if (flags & DMU_READ_NO_DECRYPT)
		db_flags |= DB_RF_NO_DECRYPT;

	DB_DNODE_ENTER(db);
	dn = DB_DNODE(db);
	err = dmu_spill_hold_by_dnode(dn, db_flags, tag, dbp);
	DB_DNODE_EXIT(db);

	return (err);
}