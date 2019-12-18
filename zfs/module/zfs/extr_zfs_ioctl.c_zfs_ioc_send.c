#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ zc_guid; int zc_flags; scalar_t__ zc_obj; int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_fromobj; int /*<<< orphan*/  zc_sendobj; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  zc_objset_type; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  offset_t ;
struct TYPE_14__ {int /*<<< orphan*/  f_offset; int /*<<< orphan*/  f_vnode; } ;
typedef  TYPE_2__ file_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_15__ {int /*<<< orphan*/  ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_16__ {int /*<<< orphan*/  dso_dryrun; int /*<<< orphan*/  dso_arg; int /*<<< orphan*/  dso_outfunc; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ dmu_send_outparams_t ;
typedef  int boolean_t ;
struct TYPE_17__ {int /*<<< orphan*/  dd_origin_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ VOP_SEEK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dmu_send_estimate_fast (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int dmu_send_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int dsl_dataset_hold_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_dir_is_clone (int /*<<< orphan*/ ) ; 
 TYPE_7__* dsl_dir_phys (int /*<<< orphan*/ ) ; 
 int dsl_pool_hold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_bytes ; 
 TYPE_2__* getf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  releasef (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_ioc_send(zfs_cmd_t *zc)
{
	int error;
	offset_t off;
	boolean_t estimate = (zc->zc_guid != 0);
	boolean_t embedok = (zc->zc_flags & 0x1);
	boolean_t large_block_ok = (zc->zc_flags & 0x2);
	boolean_t compressok = (zc->zc_flags & 0x4);
	boolean_t rawok = (zc->zc_flags & 0x8);

	if (zc->zc_obj != 0) {
		dsl_pool_t *dp;
		dsl_dataset_t *tosnap;

		error = dsl_pool_hold(zc->zc_name, FTAG, &dp);
		if (error != 0)
			return (error);

		error = dsl_dataset_hold_obj(dp, zc->zc_sendobj, FTAG, &tosnap);
		if (error != 0) {
			dsl_pool_rele(dp, FTAG);
			return (error);
		}

		if (dsl_dir_is_clone(tosnap->ds_dir))
			zc->zc_fromobj =
			    dsl_dir_phys(tosnap->ds_dir)->dd_origin_obj;
		dsl_dataset_rele(tosnap, FTAG);
		dsl_pool_rele(dp, FTAG);
	}

	if (estimate) {
		dsl_pool_t *dp;
		dsl_dataset_t *tosnap;
		dsl_dataset_t *fromsnap = NULL;

		error = dsl_pool_hold(zc->zc_name, FTAG, &dp);
		if (error != 0)
			return (error);

		error = dsl_dataset_hold_obj(dp, zc->zc_sendobj,
		    FTAG, &tosnap);
		if (error != 0) {
			dsl_pool_rele(dp, FTAG);
			return (error);
		}

		if (zc->zc_fromobj != 0) {
			error = dsl_dataset_hold_obj(dp, zc->zc_fromobj,
			    FTAG, &fromsnap);
			if (error != 0) {
				dsl_dataset_rele(tosnap, FTAG);
				dsl_pool_rele(dp, FTAG);
				return (error);
			}
		}

		error = dmu_send_estimate_fast(tosnap, fromsnap, NULL,
		    compressok || rawok, &zc->zc_objset_type);

		if (fromsnap != NULL)
			dsl_dataset_rele(fromsnap, FTAG);
		dsl_dataset_rele(tosnap, FTAG);
		dsl_pool_rele(dp, FTAG);
	} else {
		file_t *fp = getf(zc->zc_cookie);
		if (fp == NULL)
			return (SET_ERROR(EBADF));

		off = fp->f_offset;
		dmu_send_outparams_t out = {0};
		out.dso_outfunc = dump_bytes;
		out.dso_arg = fp->f_vnode;
		out.dso_dryrun = B_FALSE;
		error = dmu_send_obj(zc->zc_name, zc->zc_sendobj,
		    zc->zc_fromobj, embedok, large_block_ok, compressok, rawok,
		    zc->zc_cookie, &off, &out);

		if (VOP_SEEK(fp->f_vnode, fp->f_offset, &off, NULL) == 0)
			fp->f_offset = off;
		releasef(zc->zc_cookie);
	}
	return (error);
}