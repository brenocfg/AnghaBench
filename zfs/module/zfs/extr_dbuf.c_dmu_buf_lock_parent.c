#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krw_t ;
typedef  enum db_lock_type { ____Placeholder_db_lock_type } db_lock_type ;
struct TYPE_6__ {int /*<<< orphan*/  db_objset; TYPE_1__* db_parent; } ;
typedef  TYPE_2__ dmu_buf_impl_t ;
typedef  int db_lock_type_t ;
struct TYPE_7__ {int /*<<< orphan*/  ds_bp_rwlock; } ;
struct TYPE_5__ {int /*<<< orphan*/  db_rwlock; } ;

/* Variables and functions */
 int DLT_NONE ; 
 int DLT_OBJSET ; 
 int DLT_PARENT ; 
 TYPE_3__* dmu_objset_ds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

db_lock_type_t
dmu_buf_lock_parent(dmu_buf_impl_t *db, krw_t rw, void *tag)
{
	enum db_lock_type ret = DLT_NONE;
	if (db->db_parent != NULL) {
		rw_enter(&db->db_parent->db_rwlock, rw);
		ret = DLT_PARENT;
	} else if (dmu_objset_ds(db->db_objset) != NULL) {
		rrw_enter(&dmu_objset_ds(db->db_objset)->ds_bp_rwlock, rw,
		    tag);
		ret = DLT_OBJSET;
	}
	/*
	 * We only return a DLT_NONE lock when it's the top-most indirect block
	 * of the meta-dnode of the MOS.
	 */
	return (ret);
}