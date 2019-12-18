#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ds_dir; int /*<<< orphan*/  ds_bookmarks_obj; int /*<<< orphan*/  ds_object; } ;
typedef  TYPE_1__ dsl_dataset_t ;
struct TYPE_7__ {int /*<<< orphan*/  ds_snapnames_zapobj; int /*<<< orphan*/  ds_userrefs_obj; int /*<<< orphan*/  ds_props_obj; int /*<<< orphan*/  ds_next_clones_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  count_dir_mos_objects (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_is_snapshot (TYPE_1__*) ; 
 TYPE_2__* dsl_dataset_phys (TYPE_1__*) ; 
 int /*<<< orphan*/  mos_obj_refd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
count_ds_mos_objects(dsl_dataset_t *ds)
{
	mos_obj_refd(ds->ds_object);
	mos_obj_refd(dsl_dataset_phys(ds)->ds_next_clones_obj);
	mos_obj_refd(dsl_dataset_phys(ds)->ds_props_obj);
	mos_obj_refd(dsl_dataset_phys(ds)->ds_userrefs_obj);
	mos_obj_refd(dsl_dataset_phys(ds)->ds_snapnames_zapobj);
	mos_obj_refd(ds->ds_bookmarks_obj);

	if (!dsl_dataset_is_snapshot(ds)) {
		count_dir_mos_objects(ds->ds_dir);
	}
}