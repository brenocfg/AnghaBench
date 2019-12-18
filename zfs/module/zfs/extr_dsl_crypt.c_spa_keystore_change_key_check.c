#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_14__ {int /*<<< orphan*/  skcka_dsname; TYPE_5__* skcka_cp; } ;
typedef  TYPE_2__ spa_keystore_change_key_args_t ;
struct TYPE_15__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_3__ dsl_pool_t ;
struct TYPE_16__ {scalar_t__ dd_crypto_obj; scalar_t__ dd_object; struct TYPE_16__* dd_parent; } ;
typedef  TYPE_4__ dsl_dir_t ;
struct TYPE_17__ {scalar_t__ cp_cmd; scalar_t__ cp_crypt; TYPE_1__* cp_wkey; int /*<<< orphan*/ * cp_keylocation; } ;
typedef  TYPE_5__ dsl_crypto_params_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_13__ {scalar_t__ wk_keyformat; scalar_t__ wk_salt; scalar_t__ wk_iters; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ DCP_CMD_FORCE_INHERIT ; 
 scalar_t__ DCP_CMD_FORCE_NEW_KEY ; 
 scalar_t__ DCP_CMD_INHERIT ; 
 scalar_t__ DCP_CMD_NEW_KEY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ MIN_PBKDF2_ITERATIONS ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_ENCRYPTION ; 
 scalar_t__ ZFS_KEYFORMAT_FORMATS ; 
 scalar_t__ ZFS_KEYFORMAT_NONE ; 
 scalar_t__ ZFS_KEYFORMAT_PASSPHRASE ; 
 scalar_t__ ZIO_CRYPT_INHERIT ; 
 int dmu_objset_check_wkey_loaded (TYPE_4__*) ; 
 TYPE_3__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_dir_get_encryption_root_ddobj (TYPE_4__*,scalar_t__*) ; 
 int dsl_dir_hold (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__**,int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_dir_is_clone (TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_dir_rele (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_valid_keylocation (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spa_keystore_change_key_check(void *arg, dmu_tx_t *tx)
{
	int ret;
	dsl_dir_t *dd = NULL;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	spa_keystore_change_key_args_t *skcka = arg;
	dsl_crypto_params_t *dcp = skcka->skcka_cp;
	uint64_t rddobj;

	/* check for the encryption feature */
	if (!spa_feature_is_enabled(dp->dp_spa, SPA_FEATURE_ENCRYPTION)) {
		ret = SET_ERROR(ENOTSUP);
		goto error;
	}

	/* check for valid key change command */
	if (dcp->cp_cmd != DCP_CMD_NEW_KEY &&
	    dcp->cp_cmd != DCP_CMD_INHERIT &&
	    dcp->cp_cmd != DCP_CMD_FORCE_NEW_KEY &&
	    dcp->cp_cmd != DCP_CMD_FORCE_INHERIT) {
		ret = SET_ERROR(EINVAL);
		goto error;
	}

	/* hold the dd */
	ret = dsl_dir_hold(dp, skcka->skcka_dsname, FTAG, &dd, NULL);
	if (ret != 0) {
		dd = NULL;
		goto error;
	}

	/* verify that the dataset is encrypted */
	if (dd->dd_crypto_obj == 0) {
		ret = SET_ERROR(EINVAL);
		goto error;
	}

	/* clones must always use their origin's key */
	if (dsl_dir_is_clone(dd)) {
		ret = SET_ERROR(EINVAL);
		goto error;
	}

	/* lookup the ddobj we are inheriting the keylocation from */
	ret = dsl_dir_get_encryption_root_ddobj(dd, &rddobj);
	if (ret != 0)
		goto error;

	/* Handle inheritance */
	if (dcp->cp_cmd == DCP_CMD_INHERIT ||
	    dcp->cp_cmd == DCP_CMD_FORCE_INHERIT) {
		/* no other encryption params should be given */
		if (dcp->cp_crypt != ZIO_CRYPT_INHERIT ||
		    dcp->cp_keylocation != NULL ||
		    dcp->cp_wkey != NULL) {
			ret = SET_ERROR(EINVAL);
			goto error;
		}

		/* check that this is an encryption root */
		if (dd->dd_object != rddobj) {
			ret = SET_ERROR(EINVAL);
			goto error;
		}

		/* check that the parent is encrypted */
		if (dd->dd_parent->dd_crypto_obj == 0) {
			ret = SET_ERROR(EINVAL);
			goto error;
		}

		/* if we are rewrapping check that both keys are loaded */
		if (dcp->cp_cmd == DCP_CMD_INHERIT) {
			ret = dmu_objset_check_wkey_loaded(dd);
			if (ret != 0)
				goto error;

			ret = dmu_objset_check_wkey_loaded(dd->dd_parent);
			if (ret != 0)
				goto error;
		}

		dsl_dir_rele(dd, FTAG);
		return (0);
	}

	/* handle forcing an encryption root without rewrapping */
	if (dcp->cp_cmd == DCP_CMD_FORCE_NEW_KEY) {
		/* no other encryption params should be given */
		if (dcp->cp_crypt != ZIO_CRYPT_INHERIT ||
		    dcp->cp_keylocation != NULL ||
		    dcp->cp_wkey != NULL) {
			ret = SET_ERROR(EINVAL);
			goto error;
		}

		/* check that this is not an encryption root */
		if (dd->dd_object == rddobj) {
			ret = SET_ERROR(EINVAL);
			goto error;
		}

		dsl_dir_rele(dd, FTAG);
		return (0);
	}

	/* crypt cannot be changed after creation */
	if (dcp->cp_crypt != ZIO_CRYPT_INHERIT) {
		ret = SET_ERROR(EINVAL);
		goto error;
	}

	/* we are not inheritting our parent's wkey so we need one ourselves */
	if (dcp->cp_wkey == NULL) {
		ret = SET_ERROR(EINVAL);
		goto error;
	}

	/* check for a valid keyformat for the new wrapping key */
	if (dcp->cp_wkey->wk_keyformat >= ZFS_KEYFORMAT_FORMATS ||
	    dcp->cp_wkey->wk_keyformat == ZFS_KEYFORMAT_NONE) {
		ret = SET_ERROR(EINVAL);
		goto error;
	}

	/*
	 * If this dataset is not currently an encryption root we need a new
	 * keylocation for this dataset's new wrapping key. Otherwise we can
	 * just keep the one we already had.
	 */
	if (dd->dd_object != rddobj && dcp->cp_keylocation == NULL) {
		ret = SET_ERROR(EINVAL);
		goto error;
	}

	/* check that the keylocation is valid if it is not NULL */
	if (dcp->cp_keylocation != NULL &&
	    !zfs_prop_valid_keylocation(dcp->cp_keylocation, B_TRUE)) {
		ret = SET_ERROR(EINVAL);
		goto error;
	}

	/* passphrases require pbkdf2 salt and iters */
	if (dcp->cp_wkey->wk_keyformat == ZFS_KEYFORMAT_PASSPHRASE) {
		if (dcp->cp_wkey->wk_salt == 0 ||
		    dcp->cp_wkey->wk_iters < MIN_PBKDF2_ITERATIONS) {
			ret = SET_ERROR(EINVAL);
			goto error;
		}
	} else {
		if (dcp->cp_wkey->wk_salt != 0 || dcp->cp_wkey->wk_iters != 0) {
			ret = SET_ERROR(EINVAL);
			goto error;
		}
	}

	/* make sure the dd's wkey is loaded */
	ret = dmu_objset_check_wkey_loaded(dd);
	if (ret != 0)
		goto error;

	dsl_dir_rele(dd, FTAG);

	return (0);

error:
	if (dd != NULL)
		dsl_dir_rele(dd, FTAG);

	return (ret);
}