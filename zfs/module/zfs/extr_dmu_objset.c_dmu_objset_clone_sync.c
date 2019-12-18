#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_17__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_18__ {int /*<<< orphan*/  dd_pool; } ;
typedef  TYPE_2__ dsl_dir_t ;
struct TYPE_19__ {scalar_t__ ds_object; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_20__ {int /*<<< orphan*/  doca_clone; int /*<<< orphan*/  doca_cred; int /*<<< orphan*/  doca_origin; } ;
typedef  TYPE_4__ dmu_objset_clone_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_create_sync (TYPE_2__*,char const*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_hold (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  dsl_dataset_name (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_hold (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,char const**) ; 
 int /*<<< orphan*/  dsl_dir_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_history_log_internal_ds (TYPE_3__*,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_create_minors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dmu_objset_clone_sync(void *arg, dmu_tx_t *tx)
{
	dmu_objset_clone_arg_t *doca = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dir_t *pdd;
	const char *tail;
	dsl_dataset_t *origin, *ds;
	uint64_t obj;
	char namebuf[ZFS_MAX_DATASET_NAME_LEN];

	VERIFY0(dsl_dir_hold(dp, doca->doca_clone, FTAG, &pdd, &tail));
	VERIFY0(dsl_dataset_hold(dp, doca->doca_origin, FTAG, &origin));

	obj = dsl_dataset_create_sync(pdd, tail, origin, 0,
	    doca->doca_cred, NULL, tx);

	VERIFY0(dsl_dataset_hold_obj(pdd->dd_pool, obj, FTAG, &ds));
	dsl_dataset_name(origin, namebuf);
	spa_history_log_internal_ds(ds, "clone", tx,
	    "origin=%s (%llu)", namebuf, (u_longlong_t)origin->ds_object);
	zvol_create_minors(dp->dp_spa, doca->doca_clone, B_TRUE);
	dsl_dataset_rele(ds, FTAG);
	dsl_dataset_rele(origin, FTAG);
	dsl_dir_rele(pdd, FTAG);
}