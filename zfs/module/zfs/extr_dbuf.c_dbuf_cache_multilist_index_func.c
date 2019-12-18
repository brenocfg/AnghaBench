#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  multilist_t ;
struct TYPE_3__ {int /*<<< orphan*/  db_object; } ;
struct TYPE_4__ {int /*<<< orphan*/  db_blkid; int /*<<< orphan*/  db_level; TYPE_1__ db; int /*<<< orphan*/  db_objset; } ;
typedef  TYPE_2__ dmu_buf_impl_t ;

/* Variables and functions */
 unsigned int dbuf_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int multilist_get_num_sublists (int /*<<< orphan*/ *) ; 

unsigned int
dbuf_cache_multilist_index_func(multilist_t *ml, void *obj)
{
	dmu_buf_impl_t *db = obj;

	/*
	 * The assumption here, is the hash value for a given
	 * dmu_buf_impl_t will remain constant throughout it's lifetime
	 * (i.e. it's objset, object, level and blkid fields don't change).
	 * Thus, we don't need to store the dbuf's sublist index
	 * on insertion, as this index can be recalculated on removal.
	 *
	 * Also, the low order bits of the hash value are thought to be
	 * distributed evenly. Otherwise, in the case that the multilist
	 * has a power of two number of sublists, each sublists' usage
	 * would not be evenly distributed.
	 */
	return (dbuf_hash(db->db_objset, db->db.db_object,
	    db->db_level, db->db_blkid) %
	    multilist_get_num_sublists(ml));
}