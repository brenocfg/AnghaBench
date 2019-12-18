#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_12__ {int /*<<< orphan*/  za_first_integer; int /*<<< orphan*/  za_name; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spacemap_zap ;
struct TYPE_13__ {int /*<<< orphan*/  spa_sm_logs_by_txg; int /*<<< orphan*/  spa_metaslabs_by_flushed; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_14__ {int /*<<< orphan*/  sls_mscount; int /*<<< orphan*/  sls_txg; } ;
typedef  TYPE_3__ spa_log_sm_t ;
typedef  int /*<<< orphan*/  metaslab_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * AVL_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_LOG_SPACEMAP_ZAP ; 
 int ENOENT ; 
 int /*<<< orphan*/  avl_add (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* avl_find (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_unflushed_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_load_failed (TYPE_2__*,char*,int,...) ; 
 TYPE_3__* spa_log_sm_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_meta_objset (TYPE_2__*) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int zap_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_strtonum (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
spa_ld_log_sm_metadata(spa_t *spa)
{
	int error;
	uint64_t spacemap_zap;

	ASSERT(avl_is_empty(&spa->spa_sm_logs_by_txg));

	error = zap_lookup(spa_meta_objset(spa), DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_LOG_SPACEMAP_ZAP, sizeof (spacemap_zap), 1, &spacemap_zap);
	if (error == ENOENT) {
		/* the space map ZAP doesn't exist yet */
		return (0);
	} else if (error != 0) {
		spa_load_failed(spa, "spa_ld_log_sm_metadata(): failed at "
		    "zap_lookup(DMU_POOL_DIRECTORY_OBJECT) [error %d]",
		    error);
		return (error);
	}

	zap_cursor_t zc;
	zap_attribute_t za;
	for (zap_cursor_init(&zc, spa_meta_objset(spa), spacemap_zap);
	    (error = zap_cursor_retrieve(&zc, &za)) == 0;
	    zap_cursor_advance(&zc)) {
		uint64_t log_txg = zfs_strtonum(za.za_name, NULL);
		spa_log_sm_t *sls =
		    spa_log_sm_alloc(za.za_first_integer, log_txg);
		avl_add(&spa->spa_sm_logs_by_txg, sls);
	}
	zap_cursor_fini(&zc);
	if (error != ENOENT) {
		spa_load_failed(spa, "spa_ld_log_sm_metadata(): failed at "
		    "zap_cursor_retrieve(spacemap_zap) [error %d]",
		    error);
		return (error);
	}

	for (metaslab_t *m = avl_first(&spa->spa_metaslabs_by_flushed);
	    m; m = AVL_NEXT(&spa->spa_metaslabs_by_flushed, m)) {
		spa_log_sm_t target = { .sls_txg = metaslab_unflushed_txg(m) };
		spa_log_sm_t *sls = avl_find(&spa->spa_sm_logs_by_txg,
		    &target, NULL);

		/*
		 * At this point if sls is zero it means that a bug occurred
		 * in ZFS the last time the pool was open or earlier in the
		 * import code path. In general, we would have placed a
		 * VERIFY() here or in this case just let the kernel panic
		 * with NULL pointer dereference when incrementing sls_mscount,
		 * but since this is the import code path we can be a bit more
		 * lenient. Thus, for DEBUG bits we always cause a panic, while
		 * in production we log the error and just fail the import.
		 */
		ASSERT(sls != NULL);
		if (sls == NULL) {
			spa_load_failed(spa, "spa_ld_log_sm_metadata(): bug "
			    "encountered: could not find log spacemap for "
			    "TXG %ld [error %d]",
			    metaslab_unflushed_txg(m), ENOENT);
			return (ENOENT);
		}
		sls->sls_mscount++;
	}

	return (0);
}