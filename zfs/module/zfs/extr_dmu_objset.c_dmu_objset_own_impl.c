#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
struct TYPE_10__ {int /*<<< orphan*/  os_phys_buf; int /*<<< orphan*/  os_spa; TYPE_1__* os_phys; } ;
typedef  TYPE_2__ objset_t ;
struct TYPE_11__ {int /*<<< orphan*/  ds_object; int /*<<< orphan*/  ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  scalar_t__ dmu_objset_type_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_9__ {scalar_t__ os_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (scalar_t__) ; 
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ DMU_OST_ANY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EROFS ; 
 int /*<<< orphan*/  SET_BOOKMARK (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZB_ROOT_BLKID ; 
 int /*<<< orphan*/  ZB_ROOT_LEVEL ; 
 int /*<<< orphan*/  ZB_ROOT_OBJECT ; 
 scalar_t__ arc_is_unauthenticated (int /*<<< orphan*/ ) ; 
 int arc_untransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dmu_objset_from_ds (TYPE_3__*,TYPE_2__**) ; 
 scalar_t__ dsl_dataset_is_snapshot (TYPE_3__*) ; 
 scalar_t__ dsl_dir_incompatible_encryption_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dmu_objset_own_impl(dsl_dataset_t *ds, dmu_objset_type_t type,
    boolean_t readonly, boolean_t decrypt, void *tag, objset_t **osp)
{
	int err;

	err = dmu_objset_from_ds(ds, osp);
	if (err != 0) {
		return (err);
	} else if (type != DMU_OST_ANY && type != (*osp)->os_phys->os_type) {
		return (SET_ERROR(EINVAL));
	} else if (!readonly && dsl_dataset_is_snapshot(ds)) {
		return (SET_ERROR(EROFS));
	} else if (!readonly && decrypt &&
	    dsl_dir_incompatible_encryption_version(ds->ds_dir)) {
		return (SET_ERROR(EROFS));
	}

	/* if we are decrypting, we can now check MACs in os->os_phys_buf */
	if (decrypt && arc_is_unauthenticated((*osp)->os_phys_buf)) {
		zbookmark_phys_t zb;

		SET_BOOKMARK(&zb, ds->ds_object, ZB_ROOT_OBJECT,
		    ZB_ROOT_LEVEL, ZB_ROOT_BLKID);
		err = arc_untransform((*osp)->os_phys_buf, (*osp)->os_spa,
		    &zb, B_FALSE);
		if (err != 0)
			return (err);

		ASSERT0(arc_is_unauthenticated((*osp)->os_phys_buf));
	}

	return (0);
}