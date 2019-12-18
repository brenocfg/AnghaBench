#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_wrapping_key_t ;
struct TYPE_5__ {scalar_t__ cp_cmd; scalar_t__ cp_crypt; int /*<<< orphan*/ * cp_wkey; int /*<<< orphan*/  cp_keylocation; } ;
typedef  TYPE_1__ dsl_crypto_params_t ;
typedef  void* dcp_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ DCP_CMD_MAX ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ WRAPPING_KEY_LEN ; 
 scalar_t__ ZFS_KEYFORMAT_FORMATS ; 
 scalar_t__ ZFS_KEYFORMAT_NONE ; 
 int /*<<< orphan*/  ZFS_PROP_ENCRYPTION ; 
 int /*<<< orphan*/  ZFS_PROP_KEYFORMAT ; 
 int /*<<< orphan*/  ZFS_PROP_KEYLOCATION ; 
 int /*<<< orphan*/  ZFS_PROP_PBKDF2_ITERS ; 
 int /*<<< orphan*/  ZFS_PROP_PBKDF2_SALT ; 
 scalar_t__ ZIO_CRYPT_FUNCTIONS ; 
 scalar_t__ ZIO_CRYPT_INHERIT ; 
 scalar_t__ ZIO_CRYPT_ON ; 
 scalar_t__ ZIO_CRYPT_ON_VALUE ; 
 int dsl_wrapping_key_create (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_wrapping_key_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  nvlist_lookup_uint8_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  nvlist_remove_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_strdup (char*) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_valid_keylocation (char*,int /*<<< orphan*/ ) ; 

int
dsl_crypto_params_create_nvlist(dcp_cmd_t cmd, nvlist_t *props,
    nvlist_t *crypto_args, dsl_crypto_params_t **dcp_out)
{
	int ret;
	uint64_t crypt = ZIO_CRYPT_INHERIT;
	uint64_t keyformat = ZFS_KEYFORMAT_NONE;
	uint64_t salt = 0, iters = 0;
	dsl_crypto_params_t *dcp = NULL;
	dsl_wrapping_key_t *wkey = NULL;
	uint8_t *wkeydata = NULL;
	uint_t wkeydata_len = 0;
	char *keylocation = NULL;

	dcp = kmem_zalloc(sizeof (dsl_crypto_params_t), KM_SLEEP);
	if (!dcp) {
		ret = SET_ERROR(ENOMEM);
		goto error;
	}

	dcp->cp_cmd = cmd;

	/* get relevant arguments from the nvlists */
	if (props != NULL) {
		(void) nvlist_lookup_uint64(props,
		    zfs_prop_to_name(ZFS_PROP_ENCRYPTION), &crypt);
		(void) nvlist_lookup_uint64(props,
		    zfs_prop_to_name(ZFS_PROP_KEYFORMAT), &keyformat);
		(void) nvlist_lookup_string(props,
		    zfs_prop_to_name(ZFS_PROP_KEYLOCATION), &keylocation);
		(void) nvlist_lookup_uint64(props,
		    zfs_prop_to_name(ZFS_PROP_PBKDF2_SALT), &salt);
		(void) nvlist_lookup_uint64(props,
		    zfs_prop_to_name(ZFS_PROP_PBKDF2_ITERS), &iters);

		dcp->cp_crypt = crypt;
	}

	if (crypto_args != NULL) {
		(void) nvlist_lookup_uint8_array(crypto_args, "wkeydata",
		    &wkeydata, &wkeydata_len);
	}

	/* check for valid command */
	if (dcp->cp_cmd >= DCP_CMD_MAX) {
		ret = SET_ERROR(EINVAL);
		goto error;
	} else {
		dcp->cp_cmd = cmd;
	}

	/* check for valid crypt */
	if (dcp->cp_crypt >= ZIO_CRYPT_FUNCTIONS) {
		ret = SET_ERROR(EINVAL);
		goto error;
	} else {
		dcp->cp_crypt = crypt;
	}

	/* check for valid keyformat */
	if (keyformat >= ZFS_KEYFORMAT_FORMATS) {
		ret = SET_ERROR(EINVAL);
		goto error;
	}

	/* check for a valid keylocation (of any kind) and copy it in */
	if (keylocation != NULL) {
		if (!zfs_prop_valid_keylocation(keylocation, B_FALSE)) {
			ret = SET_ERROR(EINVAL);
			goto error;
		}

		dcp->cp_keylocation = spa_strdup(keylocation);
	}

	/* check wrapping key length, if given */
	if (wkeydata != NULL && wkeydata_len != WRAPPING_KEY_LEN) {
		ret = SET_ERROR(EINVAL);
		goto error;
	}

	/* if the user asked for the default crypt, determine that now */
	if (dcp->cp_crypt == ZIO_CRYPT_ON)
		dcp->cp_crypt = ZIO_CRYPT_ON_VALUE;

	/* create the wrapping key from the raw data */
	if (wkeydata != NULL) {
		/* create the wrapping key with the verified parameters */
		ret = dsl_wrapping_key_create(wkeydata, keyformat, salt,
		    iters, &wkey);
		if (ret != 0)
			goto error;

		dcp->cp_wkey = wkey;
	}

	/*
	 * Remove the encryption properties from the nvlist since they are not
	 * maintained through the DSL.
	 */
	(void) nvlist_remove_all(props, zfs_prop_to_name(ZFS_PROP_ENCRYPTION));
	(void) nvlist_remove_all(props, zfs_prop_to_name(ZFS_PROP_KEYFORMAT));
	(void) nvlist_remove_all(props, zfs_prop_to_name(ZFS_PROP_PBKDF2_SALT));
	(void) nvlist_remove_all(props,
	    zfs_prop_to_name(ZFS_PROP_PBKDF2_ITERS));

	*dcp_out = dcp;

	return (0);

error:
	if (wkey != NULL)
		dsl_wrapping_key_free(wkey);
	if (dcp != NULL)
		kmem_free(dcp, sizeof (dsl_crypto_params_t));

	*dcp_out = NULL;
	return (ret);
}