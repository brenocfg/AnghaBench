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
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  dd_pool; } ;
typedef  TYPE_1__ dsl_dir_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_10__ {int /*<<< orphan*/  doca_cred; int /*<<< orphan*/  doca_dcp; int /*<<< orphan*/  doca_name; } ;
typedef  TYPE_2__ dmu_objset_create_arg_t ;
struct TYPE_11__ {int /*<<< orphan*/  dd_head_dataset_obj; } ;

/* Variables and functions */
 scalar_t__ DMU_OST_ZFS ; 
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_ERR_WRONG_PARENT ; 
 scalar_t__ ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_FILESYSTEM_LIMIT ; 
 scalar_t__ dataset_nestcheck (int /*<<< orphan*/ ) ; 
 int dmu_objset_create_crypt_check (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dmu_objset_from_ds (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ dmu_objset_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_dir_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,char const**) ; 
 TYPE_5__* dsl_dir_phys (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dir_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dsl_fs_ss_limit_check (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dmu_objset_create_check(void *arg, dmu_tx_t *tx)
{
	dmu_objset_create_arg_t *doca = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dir_t *pdd;
	dsl_dataset_t *parentds;
	objset_t *parentos;
	const char *tail;
	int error;

	if (strchr(doca->doca_name, '@') != NULL)
		return (SET_ERROR(EINVAL));

	if (strlen(doca->doca_name) >= ZFS_MAX_DATASET_NAME_LEN)
		return (SET_ERROR(ENAMETOOLONG));

	if (dataset_nestcheck(doca->doca_name) != 0)
		return (SET_ERROR(ENAMETOOLONG));

	error = dsl_dir_hold(dp, doca->doca_name, FTAG, &pdd, &tail);
	if (error != 0)
		return (error);
	if (tail == NULL) {
		dsl_dir_rele(pdd, FTAG);
		return (SET_ERROR(EEXIST));
	}

	error = dmu_objset_create_crypt_check(pdd, doca->doca_dcp, NULL);
	if (error != 0) {
		dsl_dir_rele(pdd, FTAG);
		return (error);
	}

	error = dsl_fs_ss_limit_check(pdd, 1, ZFS_PROP_FILESYSTEM_LIMIT, NULL,
	    doca->doca_cred);
	if (error != 0) {
		dsl_dir_rele(pdd, FTAG);
		return (error);
	}

	/* can't create below anything but filesystems (eg. no ZVOLs) */
	error = dsl_dataset_hold_obj(pdd->dd_pool,
	    dsl_dir_phys(pdd)->dd_head_dataset_obj, FTAG, &parentds);
	if (error != 0) {
		dsl_dir_rele(pdd, FTAG);
		return (error);
	}
	error = dmu_objset_from_ds(parentds, &parentos);
	if (error != 0) {
		dsl_dataset_rele(parentds, FTAG);
		dsl_dir_rele(pdd, FTAG);
		return (error);
	}
	if (dmu_objset_type(parentos) != DMU_OST_ZFS) {
		dsl_dataset_rele(parentds, FTAG);
		dsl_dir_rele(pdd, FTAG);
		return (SET_ERROR(ZFS_ERR_WRONG_PARENT));
	}
	dsl_dataset_rele(parentds, FTAG);
	dsl_dir_rele(pdd, FTAG);

	return (error);
}