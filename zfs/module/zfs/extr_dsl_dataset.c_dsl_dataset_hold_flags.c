#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dir_t ;
struct TYPE_7__ {scalar_t__* ds_snapname; int /*<<< orphan*/  ds_lock; } ;
typedef  TYPE_1__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  ds_hold_flags_t ;
struct TYPE_8__ {scalar_t__ dd_head_dataset_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,char const*) ; 
 int dsl_dataset_hold_obj_flags (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,void*,TYPE_1__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele_flags (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int dsl_dataset_snap_lookup (TYPE_1__*,char const*,scalar_t__*) ; 
 int dsl_dir_hold (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const**) ; 
 TYPE_2__* dsl_dir_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (scalar_t__*,char const*,int) ; 

int
dsl_dataset_hold_flags(dsl_pool_t *dp, const char *name, ds_hold_flags_t flags,
    void *tag, dsl_dataset_t **dsp)
{
	dsl_dir_t *dd;
	const char *snapname;
	uint64_t obj;
	int err = 0;
	dsl_dataset_t *ds;

	err = dsl_dir_hold(dp, name, FTAG, &dd, &snapname);
	if (err != 0)
		return (err);

	ASSERT(dsl_pool_config_held(dp));
	obj = dsl_dir_phys(dd)->dd_head_dataset_obj;
	if (obj != 0)
		err = dsl_dataset_hold_obj_flags(dp, obj, flags, tag, &ds);
	else
		err = SET_ERROR(ENOENT);

	/* we may be looking for a snapshot */
	if (err == 0 && snapname != NULL) {
		dsl_dataset_t *snap_ds;

		if (*snapname++ != '@') {
			dsl_dataset_rele_flags(ds, flags, tag);
			dsl_dir_rele(dd, FTAG);
			return (SET_ERROR(ENOENT));
		}

		dprintf("looking for snapshot '%s'\n", snapname);
		err = dsl_dataset_snap_lookup(ds, snapname, &obj);
		if (err == 0) {
			err = dsl_dataset_hold_obj_flags(dp, obj, flags, tag,
			    &snap_ds);
		}
		dsl_dataset_rele_flags(ds, flags, tag);

		if (err == 0) {
			mutex_enter(&snap_ds->ds_lock);
			if (snap_ds->ds_snapname[0] == 0)
				(void) strlcpy(snap_ds->ds_snapname, snapname,
				    sizeof (snap_ds->ds_snapname));
			mutex_exit(&snap_ds->ds_lock);
			ds = snap_ds;
		}
	}
	if (err == 0)
		*dsp = ds;
	dsl_dir_rele(dd, FTAG);
	return (err);
}