#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t spa_feature_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_11__ {scalar_t__ zbm_redaction_obj; int zbm_flags; } ;
struct TYPE_13__ {TYPE_1__ dbn_phys; } ;
typedef  TYPE_3__ dsl_bookmark_node_t ;
struct TYPE_15__ {TYPE_2__* ds_dir; int /*<<< orphan*/  ds_bookmarks; } ;
struct TYPE_14__ {int fi_flags; } ;
struct TYPE_12__ {int /*<<< orphan*/  dd_livelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_3__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  FTAG ; 
 size_t SPA_FEATURES ; 
 size_t SPA_FEATURE_BOOKMARK_WRITTEN ; 
 size_t SPA_FEATURE_LIVELIST ; 
 size_t SPA_FEATURE_REDACTION_BOOKMARKS ; 
 int ZBM_FLAG_HAS_FBN ; 
 int ZFEATURE_FLAG_PER_DATASET ; 
 TYPE_3__* avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_objset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dataset_feature_count ; 
 TYPE_5__* dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_is_snapshot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_feature_is_active (TYPE_5__*,size_t) ; 
 scalar_t__ dsl_dataset_remap_deadlist_exists (TYPE_5__*) ; 
 scalar_t__ dsl_deadlist_is_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_objset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuid_table_destroy () ; 
 int /*<<< orphan*/ * global_feature_count ; 
 int /*<<< orphan*/  mos_obj_refd (scalar_t__) ; 
 int open_objset (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  remap_deadlist_count ; 
 TYPE_4__* spa_feature_table ; 

__attribute__((used)) static int
dump_one_objset(const char *dsname, void *arg)
{
	int error;
	objset_t *os;
	spa_feature_t f;

	error = open_objset(dsname, FTAG, &os);
	if (error != 0)
		return (0);

	for (f = 0; f < SPA_FEATURES; f++) {
		if (!dsl_dataset_feature_is_active(dmu_objset_ds(os), f))
			continue;
		ASSERT(spa_feature_table[f].fi_flags &
		    ZFEATURE_FLAG_PER_DATASET);
		dataset_feature_count[f]++;
	}

	if (dsl_dataset_remap_deadlist_exists(dmu_objset_ds(os))) {
		remap_deadlist_count++;
	}

	for (dsl_bookmark_node_t *dbn =
	    avl_first(&dmu_objset_ds(os)->ds_bookmarks); dbn != NULL;
	    dbn = AVL_NEXT(&dmu_objset_ds(os)->ds_bookmarks, dbn)) {
		mos_obj_refd(dbn->dbn_phys.zbm_redaction_obj);
		if (dbn->dbn_phys.zbm_redaction_obj != 0)
			global_feature_count[SPA_FEATURE_REDACTION_BOOKMARKS]++;
		if (dbn->dbn_phys.zbm_flags & ZBM_FLAG_HAS_FBN)
			global_feature_count[SPA_FEATURE_BOOKMARK_WRITTEN]++;
	}

	if (dsl_deadlist_is_open(&dmu_objset_ds(os)->ds_dir->dd_livelist) &&
	    !dmu_objset_is_snapshot(os)) {
		global_feature_count[SPA_FEATURE_LIVELIST]++;
	}

	dump_objset(os);
	close_objset(os, FTAG);
	fuid_table_destroy();
	return (0);
}