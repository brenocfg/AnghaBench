#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_17__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zprop_source_t ;
struct TYPE_21__ {int vdev_state; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int uint64_t ;
struct TYPE_20__ {int sci_dspace; } ;
struct TYPE_22__ {char* spa_comment; char* spa_root; int /*<<< orphan*/  spa_config_list; TYPE_1__ spa_checkpoint_info; int /*<<< orphan*/  spa_props_lock; TYPE_5__* spa_dsl_pool; TYPE_2__* spa_root_vdev; } ;
typedef  TYPE_3__ spa_t ;
struct TYPE_23__ {char* scd_path; } ;
typedef  TYPE_4__ spa_config_dirent_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  metaslab_class_t ;
struct TYPE_24__ {int /*<<< orphan*/ * dp_leak_dir; int /*<<< orphan*/ * dp_free_dir; } ;
typedef  TYPE_5__ dsl_pool_t ;
struct TYPE_19__ {int dd_used_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int DNODE_MAX_SIZE ; 
 int DNODE_MIN_SIZE ; 
 scalar_t__ FREAD ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPA_FEATURE_LARGE_BLOCKS ; 
 int /*<<< orphan*/  SPA_FEATURE_LARGE_DNODE ; 
 int /*<<< orphan*/  SPA_MAXBLOCKSIZE ; 
 int SPA_OLD_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  ZPOOL_PROP_ALLOCATED ; 
 int /*<<< orphan*/  ZPOOL_PROP_ALTROOT ; 
 int /*<<< orphan*/  ZPOOL_PROP_CACHEFILE ; 
 int /*<<< orphan*/  ZPOOL_PROP_CAPACITY ; 
 int /*<<< orphan*/  ZPOOL_PROP_CHECKPOINT ; 
 int /*<<< orphan*/  ZPOOL_PROP_COMMENT ; 
 int /*<<< orphan*/  ZPOOL_PROP_DEDUPRATIO ; 
 int /*<<< orphan*/  ZPOOL_PROP_EXPANDSZ ; 
 int /*<<< orphan*/  ZPOOL_PROP_FRAGMENTATION ; 
 int /*<<< orphan*/  ZPOOL_PROP_FREE ; 
 int /*<<< orphan*/  ZPOOL_PROP_FREEING ; 
 int /*<<< orphan*/  ZPOOL_PROP_GUID ; 
 int /*<<< orphan*/  ZPOOL_PROP_HEALTH ; 
 int /*<<< orphan*/  ZPOOL_PROP_LEAKED ; 
 int /*<<< orphan*/  ZPOOL_PROP_LOAD_GUID ; 
 int /*<<< orphan*/  ZPOOL_PROP_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  ZPOOL_PROP_MAXDNODESIZE ; 
 int /*<<< orphan*/  ZPOOL_PROP_NAME ; 
 int /*<<< orphan*/  ZPOOL_PROP_READONLY ; 
 int /*<<< orphan*/  ZPOOL_PROP_SIZE ; 
 int /*<<< orphan*/  ZPOOL_PROP_VERSION ; 
 int /*<<< orphan*/  const ZPROP_SRC_DEFAULT ; 
 int /*<<< orphan*/  const ZPROP_SRC_LOCAL ; 
 int /*<<< orphan*/  const ZPROP_SRC_NONE ; 
 int ddt_get_pool_dedup_ratio (TYPE_3__*) ; 
 TYPE_17__* dsl_dir_phys (int /*<<< orphan*/ *) ; 
 TYPE_4__* list_head (int /*<<< orphan*/ *) ; 
 int metaslab_class_expandable_space (int /*<<< orphan*/ *) ; 
 int metaslab_class_fragmentation (int /*<<< orphan*/ *) ; 
 int metaslab_class_get_alloc (int /*<<< orphan*/ *) ; 
 int metaslab_class_get_space (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_path ; 
 int /*<<< orphan*/ * spa_dedup_class (TYPE_3__*) ; 
 scalar_t__ spa_feature_is_enabled (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int spa_guid (TYPE_3__*) ; 
 int spa_load_guid (TYPE_3__*) ; 
 scalar_t__ spa_mode (TYPE_3__*) ; 
 char* spa_name (TYPE_3__*) ; 
 int /*<<< orphan*/ * spa_normal_class (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_prop_add_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * spa_special_class (TYPE_3__*) ; 
 int spa_version (TYPE_3__*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_max_recordsize ; 
 int zpool_prop_default_numeric (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_prop_get_config(spa_t *spa, nvlist_t **nvp)
{
	vdev_t *rvd = spa->spa_root_vdev;
	dsl_pool_t *pool = spa->spa_dsl_pool;
	uint64_t size, alloc, cap, version;
	const zprop_source_t src = ZPROP_SRC_NONE;
	spa_config_dirent_t *dp;
	metaslab_class_t *mc = spa_normal_class(spa);

	ASSERT(MUTEX_HELD(&spa->spa_props_lock));

	if (rvd != NULL) {
		alloc = metaslab_class_get_alloc(mc);
		alloc += metaslab_class_get_alloc(spa_special_class(spa));
		alloc += metaslab_class_get_alloc(spa_dedup_class(spa));

		size = metaslab_class_get_space(mc);
		size += metaslab_class_get_space(spa_special_class(spa));
		size += metaslab_class_get_space(spa_dedup_class(spa));

		spa_prop_add_list(*nvp, ZPOOL_PROP_NAME, spa_name(spa), 0, src);
		spa_prop_add_list(*nvp, ZPOOL_PROP_SIZE, NULL, size, src);
		spa_prop_add_list(*nvp, ZPOOL_PROP_ALLOCATED, NULL, alloc, src);
		spa_prop_add_list(*nvp, ZPOOL_PROP_FREE, NULL,
		    size - alloc, src);
		spa_prop_add_list(*nvp, ZPOOL_PROP_CHECKPOINT, NULL,
		    spa->spa_checkpoint_info.sci_dspace, src);

		spa_prop_add_list(*nvp, ZPOOL_PROP_FRAGMENTATION, NULL,
		    metaslab_class_fragmentation(mc), src);
		spa_prop_add_list(*nvp, ZPOOL_PROP_EXPANDSZ, NULL,
		    metaslab_class_expandable_space(mc), src);
		spa_prop_add_list(*nvp, ZPOOL_PROP_READONLY, NULL,
		    (spa_mode(spa) == FREAD), src);

		cap = (size == 0) ? 0 : (alloc * 100 / size);
		spa_prop_add_list(*nvp, ZPOOL_PROP_CAPACITY, NULL, cap, src);

		spa_prop_add_list(*nvp, ZPOOL_PROP_DEDUPRATIO, NULL,
		    ddt_get_pool_dedup_ratio(spa), src);

		spa_prop_add_list(*nvp, ZPOOL_PROP_HEALTH, NULL,
		    rvd->vdev_state, src);

		version = spa_version(spa);
		if (version == zpool_prop_default_numeric(ZPOOL_PROP_VERSION)) {
			spa_prop_add_list(*nvp, ZPOOL_PROP_VERSION, NULL,
			    version, ZPROP_SRC_DEFAULT);
		} else {
			spa_prop_add_list(*nvp, ZPOOL_PROP_VERSION, NULL,
			    version, ZPROP_SRC_LOCAL);
		}
		spa_prop_add_list(*nvp, ZPOOL_PROP_LOAD_GUID,
		    NULL, spa_load_guid(spa), src);
	}

	if (pool != NULL) {
		/*
		 * The $FREE directory was introduced in SPA_VERSION_DEADLISTS,
		 * when opening pools before this version freedir will be NULL.
		 */
		if (pool->dp_free_dir != NULL) {
			spa_prop_add_list(*nvp, ZPOOL_PROP_FREEING, NULL,
			    dsl_dir_phys(pool->dp_free_dir)->dd_used_bytes,
			    src);
		} else {
			spa_prop_add_list(*nvp, ZPOOL_PROP_FREEING,
			    NULL, 0, src);
		}

		if (pool->dp_leak_dir != NULL) {
			spa_prop_add_list(*nvp, ZPOOL_PROP_LEAKED, NULL,
			    dsl_dir_phys(pool->dp_leak_dir)->dd_used_bytes,
			    src);
		} else {
			spa_prop_add_list(*nvp, ZPOOL_PROP_LEAKED,
			    NULL, 0, src);
		}
	}

	spa_prop_add_list(*nvp, ZPOOL_PROP_GUID, NULL, spa_guid(spa), src);

	if (spa->spa_comment != NULL) {
		spa_prop_add_list(*nvp, ZPOOL_PROP_COMMENT, spa->spa_comment,
		    0, ZPROP_SRC_LOCAL);
	}

	if (spa->spa_root != NULL)
		spa_prop_add_list(*nvp, ZPOOL_PROP_ALTROOT, spa->spa_root,
		    0, ZPROP_SRC_LOCAL);

	if (spa_feature_is_enabled(spa, SPA_FEATURE_LARGE_BLOCKS)) {
		spa_prop_add_list(*nvp, ZPOOL_PROP_MAXBLOCKSIZE, NULL,
		    MIN(zfs_max_recordsize, SPA_MAXBLOCKSIZE), ZPROP_SRC_NONE);
	} else {
		spa_prop_add_list(*nvp, ZPOOL_PROP_MAXBLOCKSIZE, NULL,
		    SPA_OLD_MAXBLOCKSIZE, ZPROP_SRC_NONE);
	}

	if (spa_feature_is_enabled(spa, SPA_FEATURE_LARGE_DNODE)) {
		spa_prop_add_list(*nvp, ZPOOL_PROP_MAXDNODESIZE, NULL,
		    DNODE_MAX_SIZE, ZPROP_SRC_NONE);
	} else {
		spa_prop_add_list(*nvp, ZPOOL_PROP_MAXDNODESIZE, NULL,
		    DNODE_MIN_SIZE, ZPROP_SRC_NONE);
	}

	if ((dp = list_head(&spa->spa_config_list)) != NULL) {
		if (dp->scd_path == NULL) {
			spa_prop_add_list(*nvp, ZPOOL_PROP_CACHEFILE,
			    "none", 0, ZPROP_SRC_LOCAL);
		} else if (strcmp(dp->scd_path, spa_config_path) != 0) {
			spa_prop_add_list(*nvp, ZPOOL_PROP_CACHEFILE,
			    dp->scd_path, 0, ZPROP_SRC_LOCAL);
		}
	}
}