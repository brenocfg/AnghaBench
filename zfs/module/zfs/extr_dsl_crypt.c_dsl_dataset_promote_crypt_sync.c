#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_15__ {TYPE_2__* dp_spa; } ;
typedef  TYPE_3__ dsl_pool_t ;
struct TYPE_16__ {scalar_t__ dd_crypto_obj; int /*<<< orphan*/  dd_object; TYPE_3__* dd_pool; } ;
typedef  TYPE_4__ dsl_dir_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_17__ {int /*<<< orphan*/  dd_head_dataset_obj; } ;
struct TYPE_13__ {int /*<<< orphan*/  sk_wkeys_lock; } ;
struct TYPE_14__ {TYPE_1__ spa_keystore; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZAP_MAXVALUELEN ; 
 int /*<<< orphan*/  ZFS_PROP_KEYLOCATION ; 
 int /*<<< orphan*/  ZPROP_SRC_LOCAL ; 
 int /*<<< orphan*/  ZPROP_SRC_NONE ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_get_encryption_root_ddobj (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_dir_is_clone (TYPE_4__*) ; 
 TYPE_6__* dsl_dir_phys (TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_prop_get_dd (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_prop_set_sync_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,char*,int /*<<< orphan*/ *) ; 
 char* kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_keystore_change_key_sync_impl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 

void
dsl_dataset_promote_crypt_sync(dsl_dir_t *target, dsl_dir_t *origin,
    dmu_tx_t *tx)
{
	uint64_t rddobj;
	dsl_pool_t *dp = target->dd_pool;
	dsl_dataset_t *targetds;
	dsl_dataset_t *originds;
	char *keylocation;

	if (origin->dd_crypto_obj == 0)
		return;
	if (dsl_dir_is_clone(origin))
		return;

	VERIFY0(dsl_dir_get_encryption_root_ddobj(origin, &rddobj));

	if (rddobj != origin->dd_object)
		return;

	/*
	 * If the target is being promoted to the encryption root update the
	 * DSL Crypto Key and keylocation to reflect that. We also need to
	 * update the DSL Crypto Keys of all children inheritting their
	 * encryption root to point to the new target. Otherwise, the check
	 * function ensured that the encryption root will not change.
	 */
	keylocation = kmem_alloc(ZAP_MAXVALUELEN, KM_SLEEP);

	VERIFY0(dsl_dataset_hold_obj(dp,
	    dsl_dir_phys(target)->dd_head_dataset_obj, FTAG, &targetds));
	VERIFY0(dsl_dataset_hold_obj(dp,
	    dsl_dir_phys(origin)->dd_head_dataset_obj, FTAG, &originds));

	VERIFY0(dsl_prop_get_dd(origin, zfs_prop_to_name(ZFS_PROP_KEYLOCATION),
	    1, ZAP_MAXVALUELEN, keylocation, NULL, B_FALSE));
	dsl_prop_set_sync_impl(targetds, zfs_prop_to_name(ZFS_PROP_KEYLOCATION),
	    ZPROP_SRC_LOCAL, 1, strlen(keylocation) + 1, keylocation, tx);
	dsl_prop_set_sync_impl(originds, zfs_prop_to_name(ZFS_PROP_KEYLOCATION),
	    ZPROP_SRC_NONE, 0, 0, NULL, tx);

	rw_enter(&dp->dp_spa->spa_keystore.sk_wkeys_lock, RW_WRITER);
	spa_keystore_change_key_sync_impl(rddobj, origin->dd_object,
	    target->dd_object, NULL, B_FALSE, tx);
	rw_exit(&dp->dp_spa->spa_keystore.sk_wkeys_lock);

	dsl_dataset_rele(targetds, FTAG);
	dsl_dataset_rele(originds, FTAG);
	kmem_free(keylocation, ZAP_MAXVALUELEN);
}