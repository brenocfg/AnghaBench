#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_12__ {int /*<<< orphan*/  za_first_integer; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_13__ {TYPE_6__* ds_dir; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_16__ {scalar_t__ ds_next_clones_obj; int ds_num_children; } ;
struct TYPE_15__ {TYPE_5__* dd_pool; } ;
struct TYPE_14__ {int /*<<< orphan*/ * dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 TYPE_8__* dsl_dataset_phys (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_name (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dsl_pool_config_held (TYPE_5__*) ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zap_count (int /*<<< orphan*/ *,scalar_t__,int*) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
get_clones_stat_impl(dsl_dataset_t *ds, nvlist_t *val)
{
	uint64_t count = 0;
	objset_t *mos = ds->ds_dir->dd_pool->dp_meta_objset;
	zap_cursor_t zc;
	zap_attribute_t za;

	ASSERT(dsl_pool_config_held(ds->ds_dir->dd_pool));

	/*
	 * There may be missing entries in ds_next_clones_obj
	 * due to a bug in a previous version of the code.
	 * Only trust it if it has the right number of entries.
	 */
	if (dsl_dataset_phys(ds)->ds_next_clones_obj != 0) {
		VERIFY0(zap_count(mos, dsl_dataset_phys(ds)->ds_next_clones_obj,
		    &count));
	}
	if (count != dsl_dataset_phys(ds)->ds_num_children - 1) {
		return (ENOENT);
	}
	for (zap_cursor_init(&zc, mos,
	    dsl_dataset_phys(ds)->ds_next_clones_obj);
	    zap_cursor_retrieve(&zc, &za) == 0;
	    zap_cursor_advance(&zc)) {
		dsl_dataset_t *clone;
		char buf[ZFS_MAX_DATASET_NAME_LEN];
		VERIFY0(dsl_dataset_hold_obj(ds->ds_dir->dd_pool,
		    za.za_first_integer, FTAG, &clone));
		dsl_dir_name(clone->ds_dir, buf);
		fnvlist_add_boolean(val, buf);
		dsl_dataset_rele(clone, FTAG);
	}
	zap_cursor_fini(&zc);
	return (0);
}