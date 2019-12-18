#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_7__ {scalar_t__ db_state; int /*<<< orphan*/  db_mtx; struct TYPE_7__* db_hash_next; } ;
typedef  TYPE_1__ dmu_buf_impl_t ;
struct TYPE_8__ {size_t hash_table_mask; TYPE_1__** hash_table; } ;
typedef  TYPE_2__ dbuf_hash_table_t ;

/* Variables and functions */
 scalar_t__ DBUF_EQUAL (TYPE_1__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * DBUF_HASH_MUTEX (TYPE_2__*,size_t) ; 
 scalar_t__ DB_EVICTING ; 
 size_t dbuf_hash (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t) ; 
 TYPE_2__ dbuf_hash_table ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

dmu_buf_impl_t *
dbuf_find(objset_t *os, uint64_t obj, uint8_t level, uint64_t blkid)
{
	dbuf_hash_table_t *h = &dbuf_hash_table;
	uint64_t hv;
	uint64_t idx;
	dmu_buf_impl_t *db;

	hv = dbuf_hash(os, obj, level, blkid);
	idx = hv & h->hash_table_mask;

	mutex_enter(DBUF_HASH_MUTEX(h, idx));
	for (db = h->hash_table[idx]; db != NULL; db = db->db_hash_next) {
		if (DBUF_EQUAL(db, os, obj, level, blkid)) {
			mutex_enter(&db->db_mtx);
			if (db->db_state != DB_EVICTING) {
				mutex_exit(DBUF_HASH_MUTEX(h, idx));
				return (db);
			}
			mutex_exit(&db->db_mtx);
		}
	}
	mutex_exit(DBUF_HASH_MUTEX(h, idx));
	return (NULL);
}