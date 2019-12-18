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
typedef  int /*<<< orphan*/  dmu_object_type_t ;
typedef  int /*<<< orphan*/  dmu_buf_impl_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  dn_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DBUF_STAT_BUMP (int /*<<< orphan*/ ) ; 
 size_t DB_DBUF_METADATA_CACHE ; 
 TYPE_2__* DB_DNODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DB_DNODE_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DB_DNODE_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DMU_OT_IS_METADATA (int /*<<< orphan*/ ) ; 
 scalar_t__ DMU_OT_IS_METADATA_CACHED (int /*<<< orphan*/ ) ; 
 TYPE_1__* dbuf_caches ; 
 scalar_t__ dbuf_metadata_cache_max_bytes ; 
 int /*<<< orphan*/  metadata_cache_overflow ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static boolean_t
dbuf_include_in_metadata_cache(dmu_buf_impl_t *db)
{
	DB_DNODE_ENTER(db);
	dmu_object_type_t type = DB_DNODE(db)->dn_type;
	DB_DNODE_EXIT(db);

	/* Check if this dbuf is one of the types we care about */
	if (DMU_OT_IS_METADATA_CACHED(type)) {
		/* If we hit this, then we set something up wrong in dmu_ot */
		ASSERT(DMU_OT_IS_METADATA(type));

		/*
		 * Sanity check for small-memory systems: don't allocate too
		 * much memory for this purpose.
		 */
		if (zfs_refcount_count(
		    &dbuf_caches[DB_DBUF_METADATA_CACHE].size) >
		    dbuf_metadata_cache_max_bytes) {
			DBUF_STAT_BUMP(metadata_cache_overflow);
			return (B_FALSE);
		}

		return (B_TRUE);
	}

	return (B_FALSE);
}