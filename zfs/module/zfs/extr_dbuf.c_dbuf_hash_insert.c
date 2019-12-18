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
typedef  size_t uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_9__ {size_t db_object; } ;
struct TYPE_10__ {int db_level; size_t db_blkid; scalar_t__ db_state; struct TYPE_10__* db_hash_next; int /*<<< orphan*/  db_mtx; TYPE_1__ db; int /*<<< orphan*/ * db_objset; } ;
typedef  TYPE_2__ dmu_buf_impl_t ;
struct TYPE_11__ {size_t hash_table_mask; TYPE_2__** hash_table; } ;
typedef  TYPE_3__ dbuf_hash_table_t ;

/* Variables and functions */
 scalar_t__ DBUF_EQUAL (TYPE_2__*,int /*<<< orphan*/ *,size_t,int,size_t) ; 
 int /*<<< orphan*/ * DBUF_HASH_MUTEX (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  DBUF_STAT_BUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBUF_STAT_MAX (int /*<<< orphan*/ ,int) ; 
 scalar_t__ DB_EVICTING ; 
 int /*<<< orphan*/  atomic_inc_64 (int*) ; 
 size_t dbuf_hash (int /*<<< orphan*/ *,size_t,int,size_t) ; 
 int dbuf_hash_count ; 
 TYPE_3__ dbuf_hash_table ; 
 int /*<<< orphan*/  hash_chain_max ; 
 int /*<<< orphan*/  hash_chains ; 
 int /*<<< orphan*/  hash_collisions ; 
 int /*<<< orphan*/  hash_elements_max ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static dmu_buf_impl_t *
dbuf_hash_insert(dmu_buf_impl_t *db)
{
	dbuf_hash_table_t *h = &dbuf_hash_table;
	objset_t *os = db->db_objset;
	uint64_t obj = db->db.db_object;
	int level = db->db_level;
	uint64_t blkid, hv, idx;
	dmu_buf_impl_t *dbf;
	uint32_t i;

	blkid = db->db_blkid;
	hv = dbuf_hash(os, obj, level, blkid);
	idx = hv & h->hash_table_mask;

	mutex_enter(DBUF_HASH_MUTEX(h, idx));
	for (dbf = h->hash_table[idx], i = 0; dbf != NULL;
	    dbf = dbf->db_hash_next, i++) {
		if (DBUF_EQUAL(dbf, os, obj, level, blkid)) {
			mutex_enter(&dbf->db_mtx);
			if (dbf->db_state != DB_EVICTING) {
				mutex_exit(DBUF_HASH_MUTEX(h, idx));
				return (dbf);
			}
			mutex_exit(&dbf->db_mtx);
		}
	}

	if (i > 0) {
		DBUF_STAT_BUMP(hash_collisions);
		if (i == 1)
			DBUF_STAT_BUMP(hash_chains);

		DBUF_STAT_MAX(hash_chain_max, i);
	}

	mutex_enter(&db->db_mtx);
	db->db_hash_next = h->hash_table[idx];
	h->hash_table[idx] = db;
	mutex_exit(DBUF_HASH_MUTEX(h, idx));
	atomic_inc_64(&dbuf_hash_count);
	DBUF_STAT_MAX(hash_elements_max, dbuf_hash_count);

	return (NULL);
}