#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int zv_changed; int /*<<< orphan*/  zv_state_lock; int /*<<< orphan*/  zv_suspend_lock; int /*<<< orphan*/ * zv_objset; scalar_t__ zv_volsize; } ;
typedef  TYPE_1__ zvol_state_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_10__ {int /*<<< orphan*/  doi_data_block_size; } ;
typedef  TYPE_2__ dmu_object_info_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* zv_update_volsize ) (TYPE_1__*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  DMU_OST_ZVOL ; 
 int EROFS ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 scalar_t__ MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_READER ; 
 scalar_t__ RW_READ_HELD (int /*<<< orphan*/ *) ; 
 int SET_ERROR (int) ; 
 int /*<<< orphan*/  ZFS_PROP_READONLY ; 
 int /*<<< orphan*/  ZVOL_OBJ ; 
 int dmu_object_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int dmu_objset_own (char const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int dsl_prop_get_integer (char const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_5__* ops ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 
 int zvol_check_volsize (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* zvol_find_by_name (char const*,int /*<<< orphan*/ ) ; 
 int zvol_update_volsize (scalar_t__,int /*<<< orphan*/ *) ; 

int
zvol_set_volsize(const char *name, uint64_t volsize)
{
	objset_t *os = NULL;
	uint64_t readonly;
	int error;
	boolean_t owned = B_FALSE;

	error = dsl_prop_get_integer(name,
	    zfs_prop_to_name(ZFS_PROP_READONLY), &readonly, NULL);
	if (error != 0)
		return (SET_ERROR(error));
	if (readonly)
		return (SET_ERROR(EROFS));

	zvol_state_t *zv = zvol_find_by_name(name, RW_READER);

	ASSERT(zv == NULL || (MUTEX_HELD(&zv->zv_state_lock) &&
	    RW_READ_HELD(&zv->zv_suspend_lock)));

	if (zv == NULL || zv->zv_objset == NULL) {
		if (zv != NULL)
			rw_exit(&zv->zv_suspend_lock);
		if ((error = dmu_objset_own(name, DMU_OST_ZVOL, B_FALSE, B_TRUE,
		    FTAG, &os)) != 0) {
			if (zv != NULL)
				mutex_exit(&zv->zv_state_lock);
			return (SET_ERROR(error));
		}
		owned = B_TRUE;
		if (zv != NULL)
			zv->zv_objset = os;
	} else {
		os = zv->zv_objset;
	}

	dmu_object_info_t *doi = kmem_alloc(sizeof (*doi), KM_SLEEP);

	if ((error = dmu_object_info(os, ZVOL_OBJ, doi)) ||
	    (error = zvol_check_volsize(volsize, doi->doi_data_block_size)))
		goto out;

	error = zvol_update_volsize(volsize, os);
	if (error == 0 && zv != NULL) {
		zv->zv_volsize = volsize;
		zv->zv_changed = 1;
	}
out:
	kmem_free(doi, sizeof (dmu_object_info_t));

	if (owned) {
		dmu_objset_disown(os, B_TRUE, FTAG);
		if (zv != NULL)
			zv->zv_objset = NULL;
	} else {
		rw_exit(&zv->zv_suspend_lock);
	}

	if (zv != NULL)
		mutex_exit(&zv->zv_state_lock);

	if (error == 0 && zv != NULL)
		ops->zv_update_volsize(zv, volsize);

	return (SET_ERROR(error));
}