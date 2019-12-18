#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_28__ {int /*<<< orphan*/  spa_root_vdev; int /*<<< orphan*/  spa_meta_objset; int /*<<< orphan*/  spa_deferred_bpobj; TYPE_2__* spa_dsl_pool; int /*<<< orphan*/  spa_uberblock; int /*<<< orphan*/  spa_config; } ;
typedef  TYPE_1__ spa_t ;
typedef  size_t spa_feature_t ;
typedef  int /*<<< orphan*/  longlong_t ;
struct TYPE_29__ {int /*<<< orphan*/  dp_bptree_obj; int /*<<< orphan*/  dp_obsolete_bpobj; int /*<<< orphan*/  dp_free_bpobj; int /*<<< orphan*/  dp_meta_objset; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_27__ {int fi_flags; char* fi_uname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT0 (scalar_t__) ; 
 int DS_FIND_CHILDREN ; 
 int DS_FIND_SNAPSHOTS ; 
 scalar_t__ ENOTSUP ; 
 int /*<<< orphan*/  RANGE_SEG64 ; 
 size_t SPA_FEATURES ; 
 int /*<<< orphan*/  SPA_FEATURE_ASYNC_DESTROY ; 
 size_t SPA_FEATURE_BOOKMARK_WRITTEN ; 
 size_t SPA_FEATURE_DEVICE_REMOVAL ; 
 size_t SPA_FEATURE_LIVELIST ; 
 size_t SPA_FEATURE_REDACTION_BOOKMARKS ; 
 scalar_t__ SPA_VERSION_DEADLISTS ; 
 scalar_t__ UINT64_MAX ; 
 int ZFEATURE_FLAG_PER_DATASET ; 
 scalar_t__ bpobj_is_open (int /*<<< orphan*/ *) ; 
 scalar_t__* dataset_feature_count ; 
 int /*<<< orphan*/  dmu_objset_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dump_all_ddts (TYPE_1__*) ; 
 int dump_block_stats (TYPE_1__*) ; 
 int /*<<< orphan*/  dump_bptree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dump_config (TYPE_1__*) ; 
 int /*<<< orphan*/  dump_debug_buffer () ; 
 int /*<<< orphan*/  dump_dtl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_full_bpobj (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_history (TYPE_1__*) ; 
 int /*<<< orphan*/  dump_log_spacemap_obsolete_stats (TYPE_1__*) ; 
 int /*<<< orphan*/  dump_log_spacemaps (TYPE_1__*) ; 
 int /*<<< orphan*/  dump_metaslab_groups (TYPE_1__*) ; 
 int /*<<< orphan*/  dump_metaslabs (TYPE_1__*) ; 
 int dump_mos_leaks (TYPE_1__*) ; 
 int /*<<< orphan*/  dump_nvlist (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_objset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_one_objset ; 
 int* dump_opt ; 
 int /*<<< orphan*/  dump_simulated_ddt (TYPE_1__*) ; 
 int /*<<< orphan*/  dump_uberblock (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ feature_get_refcount (TYPE_1__*,TYPE_10__*,scalar_t__*) ; 
 scalar_t__* global_feature_count ; 
 int /*<<< orphan*/  mos_refd_objs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  range_tree_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_pool_stats (TYPE_1__*) ; 
 scalar_t__ spa_feature_is_active (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (TYPE_1__*,size_t) ; 
 TYPE_10__* spa_feature_table ; 
 TYPE_2__* spa_get_dsl (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_name (TYPE_1__*) ; 
 scalar_t__ spa_version (TYPE_1__*) ; 
 int verify_checkpoint (TYPE_1__*) ; 
 int verify_device_removal_feature_counts (TYPE_1__*) ; 
 int verify_spacemap_refcounts (TYPE_1__*) ; 

__attribute__((used)) static void
dump_zpool(spa_t *spa)
{
	dsl_pool_t *dp = spa_get_dsl(spa);
	int rc = 0;

	if (dump_opt['S']) {
		dump_simulated_ddt(spa);
		return;
	}

	if (!dump_opt['e'] && dump_opt['C'] > 1) {
		(void) printf("\nCached configuration:\n");
		dump_nvlist(spa->spa_config, 8);
	}

	if (dump_opt['C'])
		dump_config(spa);

	if (dump_opt['u'])
		dump_uberblock(&spa->spa_uberblock, "\nUberblock:\n", "\n");

	if (dump_opt['D'])
		dump_all_ddts(spa);

	if (dump_opt['d'] > 2 || dump_opt['m'])
		dump_metaslabs(spa);
	if (dump_opt['M'])
		dump_metaslab_groups(spa);
	if (dump_opt['d'] > 2 || dump_opt['m']) {
		dump_log_spacemaps(spa);
		dump_log_spacemap_obsolete_stats(spa);
	}

	if (dump_opt['d'] || dump_opt['i']) {
		spa_feature_t f;
		mos_refd_objs = range_tree_create(NULL, RANGE_SEG64, NULL, 0,
		    0);
		dump_objset(dp->dp_meta_objset);

		if (dump_opt['d'] >= 3) {
			dsl_pool_t *dp = spa->spa_dsl_pool;
			dump_full_bpobj(&spa->spa_deferred_bpobj,
			    "Deferred frees", 0);
			if (spa_version(spa) >= SPA_VERSION_DEADLISTS) {
				dump_full_bpobj(&dp->dp_free_bpobj,
				    "Pool snapshot frees", 0);
			}
			if (bpobj_is_open(&dp->dp_obsolete_bpobj)) {
				ASSERT(spa_feature_is_enabled(spa,
				    SPA_FEATURE_DEVICE_REMOVAL));
				dump_full_bpobj(&dp->dp_obsolete_bpobj,
				    "Pool obsolete blocks", 0);
			}

			if (spa_feature_is_active(spa,
			    SPA_FEATURE_ASYNC_DESTROY)) {
				dump_bptree(spa->spa_meta_objset,
				    dp->dp_bptree_obj,
				    "Pool dataset frees");
			}
			dump_dtl(spa->spa_root_vdev, 0);
		}

		for (spa_feature_t f = 0; f < SPA_FEATURES; f++)
			global_feature_count[f] = UINT64_MAX;
		global_feature_count[SPA_FEATURE_REDACTION_BOOKMARKS] = 0;
		global_feature_count[SPA_FEATURE_BOOKMARK_WRITTEN] = 0;
		global_feature_count[SPA_FEATURE_LIVELIST] = 0;

		(void) dmu_objset_find(spa_name(spa), dump_one_objset,
		    NULL, DS_FIND_SNAPSHOTS | DS_FIND_CHILDREN);

		if (rc == 0 && !dump_opt['L'])
			rc = dump_mos_leaks(spa);

		for (f = 0; f < SPA_FEATURES; f++) {
			uint64_t refcount;

			uint64_t *arr;
			if (!(spa_feature_table[f].fi_flags &
			    ZFEATURE_FLAG_PER_DATASET)) {
				if (global_feature_count[f] == UINT64_MAX)
					continue;
				if (!spa_feature_is_enabled(spa, f)) {
					ASSERT0(global_feature_count[f]);
					continue;
				}
				arr = global_feature_count;
			} else {
				if (!spa_feature_is_enabled(spa, f)) {
					ASSERT0(dataset_feature_count[f]);
					continue;
				}
				arr = dataset_feature_count;
			}
			if (feature_get_refcount(spa, &spa_feature_table[f],
			    &refcount) == ENOTSUP)
				continue;
			if (arr[f] != refcount) {
				(void) printf("%s feature refcount mismatch: "
				    "%lld consumers != %lld refcount\n",
				    spa_feature_table[f].fi_uname,
				    (longlong_t)arr[f], (longlong_t)refcount);
				rc = 2;
			} else {
				(void) printf("Verified %s feature refcount "
				    "of %llu is correct\n",
				    spa_feature_table[f].fi_uname,
				    (longlong_t)refcount);
			}
		}

		if (rc == 0)
			rc = verify_device_removal_feature_counts(spa);
	}

	if (rc == 0 && (dump_opt['b'] || dump_opt['c']))
		rc = dump_block_stats(spa);

	if (rc == 0)
		rc = verify_spacemap_refcounts(spa);

	if (dump_opt['s'])
		show_pool_stats(spa);

	if (dump_opt['h'])
		dump_history(spa);

	if (rc == 0)
		rc = verify_checkpoint(spa);

	if (rc != 0) {
		dump_debug_buffer();
		exit(rc);
	}
}