#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_name; int /*<<< orphan*/  zpool_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  prop_keylocation ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
#define  EACCES 132 
#define  EBUSY 131 
#define  EEXIST 130 
#define  EINVAL 129 
#define  EPERM 128 
 int /*<<< orphan*/  EZFS_CRYPTOFAILED ; 
 int MAXNAMELEN ; 
 int MAX_KEY_PROMPT_ATTEMPTS ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  WRAPPING_KEY_LEN ; 
 scalar_t__ ZFS_KEYFORMAT_NONE ; 
 scalar_t__ ZFS_KEYFORMAT_PASSPHRASE ; 
 scalar_t__ ZFS_KEYSTATUS_AVAILABLE ; 
 int /*<<< orphan*/  ZFS_PROP_KEYFORMAT ; 
 int /*<<< orphan*/  ZFS_PROP_KEYLOCATION ; 
 int /*<<< orphan*/  ZFS_PROP_KEYSTATUS ; 
 int /*<<< orphan*/  ZFS_PROP_PBKDF2_ITERS ; 
 int /*<<< orphan*/  ZFS_PROP_PBKDF2_SALT ; 
 int derive_key (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,size_t,scalar_t__,int /*<<< orphan*/ **) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  encryption_feature_is_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int get_key_material (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*,scalar_t__*) ; 
 int lzc_load_key (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int zfs_crypto_get_encryption_root (TYPE_1__*,scalar_t__*,char*) ; 
 int /*<<< orphan*/  zfs_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  zfs_get_name (TYPE_1__*) ; 
 int zfs_prop_get (TYPE_1__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ zfs_prop_get_int (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
zfs_crypto_load_key(zfs_handle_t *zhp, boolean_t noop, char *alt_keylocation)
{
	int ret, attempts = 0;
	char errbuf[1024];
	uint64_t keystatus, iters = 0, salt = 0;
	uint64_t keyformat = ZFS_KEYFORMAT_NONE;
	char prop_keylocation[MAXNAMELEN];
	char prop_encroot[MAXNAMELEN];
	char *keylocation = NULL;
	uint8_t *key_material = NULL, *key_data = NULL;
	size_t key_material_len;
	boolean_t is_encroot, can_retry = B_FALSE, correctible = B_FALSE;

	(void) snprintf(errbuf, sizeof (errbuf),
	    dgettext(TEXT_DOMAIN, "Key load error"));

	/* check that encryption is enabled for the pool */
	if (!encryption_feature_is_enabled(zhp->zpool_hdl)) {
		zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
		    "Encryption feature not enabled."));
		ret = EINVAL;
		goto error;
	}

	/* Fetch the keyformat. Check that the dataset is encrypted. */
	keyformat = zfs_prop_get_int(zhp, ZFS_PROP_KEYFORMAT);
	if (keyformat == ZFS_KEYFORMAT_NONE) {
		zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
		    "'%s' is not encrypted."), zfs_get_name(zhp));
		ret = EINVAL;
		goto error;
	}

	/*
	 * Fetch the key location. Check that we are working with an
	 * encryption root.
	 */
	ret = zfs_crypto_get_encryption_root(zhp, &is_encroot, prop_encroot);
	if (ret != 0) {
		zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
		    "Failed to get encryption root for '%s'."),
		    zfs_get_name(zhp));
		goto error;
	} else if (!is_encroot) {
		zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
		    "Keys must be loaded for encryption root of '%s' (%s)."),
		    zfs_get_name(zhp), prop_encroot);
		ret = EINVAL;
		goto error;
	}

	/*
	 * if the caller has elected to override the keylocation property
	 * use that instead
	 */
	if (alt_keylocation != NULL) {
		keylocation = alt_keylocation;
	} else {
		ret = zfs_prop_get(zhp, ZFS_PROP_KEYLOCATION, prop_keylocation,
		    sizeof (prop_keylocation), NULL, NULL, 0, B_TRUE);
		if (ret != 0) {
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Failed to get keylocation for '%s'."),
			    zfs_get_name(zhp));
			goto error;
		}

		keylocation = prop_keylocation;
	}

	/* check that the key is unloaded unless this is a noop */
	if (!noop) {
		keystatus = zfs_prop_get_int(zhp, ZFS_PROP_KEYSTATUS);
		if (keystatus == ZFS_KEYSTATUS_AVAILABLE) {
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Key already loaded for '%s'."), zfs_get_name(zhp));
			ret = EEXIST;
			goto error;
		}
	}

	/* passphrase formats require a salt and pbkdf2_iters property */
	if (keyformat == ZFS_KEYFORMAT_PASSPHRASE) {
		salt = zfs_prop_get_int(zhp, ZFS_PROP_PBKDF2_SALT);
		iters = zfs_prop_get_int(zhp, ZFS_PROP_PBKDF2_ITERS);
	}

try_again:
	/* fetching and deriving the key are correctable errors. set the flag */
	correctible = B_TRUE;

	/* get key material from key format and location */
	ret = get_key_material(zhp->zfs_hdl, B_FALSE, B_FALSE, keyformat,
	    keylocation, zfs_get_name(zhp), &key_material, &key_material_len,
	    &can_retry);
	if (ret != 0)
		goto error;

	/* derive a key from the key material */
	ret = derive_key(zhp->zfs_hdl, keyformat, iters, key_material,
	    key_material_len, salt, &key_data);
	if (ret != 0)
		goto error;

	correctible = B_FALSE;

	/* pass the wrapping key and noop flag to the ioctl */
	ret = lzc_load_key(zhp->zfs_name, noop, key_data, WRAPPING_KEY_LEN);
	if (ret != 0) {
		switch (ret) {
		case EPERM:
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Permission denied."));
			break;
		case EINVAL:
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Invalid parameters provided for dataset %s."),
			    zfs_get_name(zhp));
			break;
		case EEXIST:
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Key already loaded for '%s'."), zfs_get_name(zhp));
			break;
		case EBUSY:
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "'%s' is busy."), zfs_get_name(zhp));
			break;
		case EACCES:
			correctible = B_TRUE;
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Incorrect key provided for '%s'."),
			    zfs_get_name(zhp));
			break;
		}
		goto error;
	}

	free(key_material);
	free(key_data);

	return (0);

error:
	zfs_error(zhp->zfs_hdl, EZFS_CRYPTOFAILED, errbuf);
	if (key_material != NULL) {
		free(key_material);
		key_material = NULL;
	}
	if (key_data != NULL) {
		free(key_data);
		key_data = NULL;
	}

	/*
	 * Here we decide if it is ok to allow the user to retry entering their
	 * key. The can_retry flag will be set if the user is entering their
	 * key from an interactive prompt. The correctable flag will only be
	 * set if an error that occurred could be corrected by retrying. Both
	 * flags are needed to allow the user to attempt key entry again
	 */
	attempts++;
	if (can_retry && correctible && attempts < MAX_KEY_PROMPT_ATTEMPTS)
		goto try_again;

	return (ret);
}