#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_16__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_14__* ks_data; } ;
typedef  TYPE_13__ kstat_t ;
struct TYPE_18__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_19__ {TYPE_11__ value; } ;
struct TYPE_31__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_17__ {TYPE_9__ value; } ;
struct TYPE_29__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_30__ {TYPE_7__ value; } ;
struct TYPE_27__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_28__ {TYPE_5__ value; } ;
struct TYPE_25__ {void* ui64; } ;
struct TYPE_26__ {TYPE_3__ value; } ;
struct TYPE_23__ {void* ui64; } ;
struct TYPE_24__ {TYPE_1__ value; } ;
struct TYPE_21__ {TYPE_12__ hash_elements; TYPE_10__ cache_lowater_bytes; TYPE_8__ cache_hiwater_bytes; TYPE_6__ cache_target_bytes; TYPE_4__ cache_size_bytes; TYPE_2__ metadata_cache_size_bytes; } ;
typedef  TYPE_14__ dbuf_stats_t ;
struct TYPE_22__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 size_t DB_DBUF_CACHE ; 
 size_t DB_DBUF_METADATA_CACHE ; 
 int /*<<< orphan*/  EACCES ; 
 int KSTAT_WRITE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbuf_cache_hiwater_bytes () ; 
 int /*<<< orphan*/  dbuf_cache_lowater_bytes () ; 
 int /*<<< orphan*/  dbuf_cache_target_bytes () ; 
 TYPE_16__* dbuf_caches ; 
 int /*<<< orphan*/  dbuf_hash_count ; 
 void* zfs_refcount_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dbuf_kstat_update(kstat_t *ksp, int rw)
{
	dbuf_stats_t *ds = ksp->ks_data;

	if (rw == KSTAT_WRITE) {
		return (SET_ERROR(EACCES));
	} else {
		ds->metadata_cache_size_bytes.value.ui64 = zfs_refcount_count(
		    &dbuf_caches[DB_DBUF_METADATA_CACHE].size);
		ds->cache_size_bytes.value.ui64 =
		    zfs_refcount_count(&dbuf_caches[DB_DBUF_CACHE].size);
		ds->cache_target_bytes.value.ui64 = dbuf_cache_target_bytes();
		ds->cache_hiwater_bytes.value.ui64 = dbuf_cache_hiwater_bytes();
		ds->cache_lowater_bytes.value.ui64 = dbuf_cache_lowater_bytes();
		ds->hash_elements.value.ui64 = dbuf_hash_count;
	}

	return (0);
}