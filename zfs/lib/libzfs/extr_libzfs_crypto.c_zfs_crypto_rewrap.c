#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_name; int /*<<< orphan*/  zpool_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  prop_keylocation ;
typedef  int /*<<< orphan*/  parent_name ;
typedef  int /*<<< orphan*/  origin_name ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  dcp_cmd_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DCP_CMD_INHERIT ; 
 int /*<<< orphan*/  DCP_CMD_NEW_KEY ; 
#define  EACCES 130 
#define  EINVAL 129 
 int ENOENT ; 
#define  EPERM 128 
 int /*<<< orphan*/  EZFS_CRYPTOFAILED ; 
 int MAXNAMELEN ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 scalar_t__ ZFS_KEYFORMAT_NONE ; 
 scalar_t__ ZFS_KEYSTATUS_UNAVAILABLE ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_ENCRYPTION ; 
 int /*<<< orphan*/  ZFS_PROP_KEYFORMAT ; 
 int /*<<< orphan*/  ZFS_PROP_KEYLOCATION ; 
 int /*<<< orphan*/  ZFS_PROP_KEYSTATUS ; 
 int /*<<< orphan*/  ZFS_PROP_ORIGIN ; 
 scalar_t__ ZIO_CRYPT_OFF ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  encryption_feature_is_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int lzc_change_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* make_dataset_handle (int /*<<< orphan*/ ,char*) ; 
 int nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int populate_create_encryption_params_nvlists (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 int zfs_crypto_get_encryption_root (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int zfs_crypto_verify_rewrap_nvlist (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  zfs_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  zfs_get_name (TYPE_1__*) ; 
 int zfs_parent_name (TYPE_1__*,char*,int) ; 
 int zfs_prop_get (TYPE_1__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 

int
zfs_crypto_rewrap(zfs_handle_t *zhp, nvlist_t *raw_props, boolean_t inheritkey)
{
	int ret;
	char errbuf[1024];
	boolean_t is_encroot;
	nvlist_t *props = NULL;
	uint8_t *wkeydata = NULL;
	uint_t wkeylen = 0;
	dcp_cmd_t cmd = (inheritkey) ? DCP_CMD_INHERIT : DCP_CMD_NEW_KEY;
	uint64_t crypt, pcrypt, keystatus, pkeystatus;
	uint64_t keyformat = ZFS_KEYFORMAT_NONE;
	zfs_handle_t *pzhp = NULL;
	char *keylocation = NULL;
	char origin_name[MAXNAMELEN];
	char prop_keylocation[MAXNAMELEN];
	char parent_name[ZFS_MAX_DATASET_NAME_LEN];

	(void) snprintf(errbuf, sizeof (errbuf),
	    dgettext(TEXT_DOMAIN, "Key change error"));

	/* check that encryption is enabled for the pool */
	if (!encryption_feature_is_enabled(zhp->zpool_hdl)) {
		zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
		    "Encryption feature not enabled."));
		ret = EINVAL;
		goto error;
	}

	/* get crypt from dataset */
	crypt = zfs_prop_get_int(zhp, ZFS_PROP_ENCRYPTION);
	if (crypt == ZIO_CRYPT_OFF) {
		zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
		    "Dataset not encrypted."));
		ret = EINVAL;
		goto error;
	}

	/* get the encryption root of the dataset */
	ret = zfs_crypto_get_encryption_root(zhp, &is_encroot, NULL);
	if (ret != 0) {
		zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
		    "Failed to get encryption root for '%s'."),
		    zfs_get_name(zhp));
		goto error;
	}

	/* Clones use their origin's key and cannot rewrap it */
	ret = zfs_prop_get(zhp, ZFS_PROP_ORIGIN, origin_name,
	    sizeof (origin_name), NULL, NULL, 0, B_TRUE);
	if (ret == 0 && strcmp(origin_name, "") != 0) {
		zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
		    "Keys cannot be changed on clones."));
		ret = EINVAL;
		goto error;
	}

	/*
	 * If the user wants to use the inheritkey variant of this function
	 * we don't need to collect any crypto arguments.
	 */
	if (!inheritkey) {
		/* validate the provided properties */
		ret = zfs_crypto_verify_rewrap_nvlist(zhp, raw_props, &props,
		    errbuf);
		if (ret != 0)
			goto error;

		/*
		 * Load keyformat and keylocation from the nvlist. Fetch from
		 * the dataset properties if not specified.
		 */
		(void) nvlist_lookup_uint64(props,
		    zfs_prop_to_name(ZFS_PROP_KEYFORMAT), &keyformat);
		(void) nvlist_lookup_string(props,
		    zfs_prop_to_name(ZFS_PROP_KEYLOCATION), &keylocation);

		if (is_encroot) {
			/*
			 * If this is already an encryption root, just keep
			 * any properties not set by the user.
			 */
			if (keyformat == ZFS_KEYFORMAT_NONE) {
				keyformat = zfs_prop_get_int(zhp,
				    ZFS_PROP_KEYFORMAT);
				ret = nvlist_add_uint64(props,
				    zfs_prop_to_name(ZFS_PROP_KEYFORMAT),
				    keyformat);
				if (ret != 0) {
					zfs_error_aux(zhp->zfs_hdl,
					    dgettext(TEXT_DOMAIN, "Failed to "
					    "get existing keyformat "
					    "property."));
					goto error;
				}
			}

			if (keylocation == NULL) {
				ret = zfs_prop_get(zhp, ZFS_PROP_KEYLOCATION,
				    prop_keylocation, sizeof (prop_keylocation),
				    NULL, NULL, 0, B_TRUE);
				if (ret != 0) {
					zfs_error_aux(zhp->zfs_hdl,
					    dgettext(TEXT_DOMAIN, "Failed to "
					    "get existing keylocation "
					    "property."));
					goto error;
				}

				keylocation = prop_keylocation;
			}
		} else {
			/* need a new key for non-encryption roots */
			if (keyformat == ZFS_KEYFORMAT_NONE) {
				ret = EINVAL;
				zfs_error_aux(zhp->zfs_hdl,
				    dgettext(TEXT_DOMAIN, "Keyformat required "
				    "for new encryption root."));
				goto error;
			}

			/* default to prompt if no keylocation is specified */
			if (keylocation == NULL) {
				keylocation = "prompt";
				ret = nvlist_add_string(props,
				    zfs_prop_to_name(ZFS_PROP_KEYLOCATION),
				    keylocation);
				if (ret != 0)
					goto error;
			}
		}

		/* fetch the new wrapping key and associated properties */
		ret = populate_create_encryption_params_nvlists(zhp->zfs_hdl,
		    zhp, B_TRUE, keyformat, keylocation, props, &wkeydata,
		    &wkeylen);
		if (ret != 0)
			goto error;
	} else {
		/* check that zhp is an encryption root */
		if (!is_encroot) {
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Key inheritting can only be performed on "
			    "encryption roots."));
			ret = EINVAL;
			goto error;
		}

		/* get the parent's name */
		ret = zfs_parent_name(zhp, parent_name, sizeof (parent_name));
		if (ret != 0) {
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Root dataset cannot inherit key."));
			ret = EINVAL;
			goto error;
		}

		/* get a handle to the parent */
		pzhp = make_dataset_handle(zhp->zfs_hdl, parent_name);
		if (pzhp == NULL) {
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Failed to lookup parent."));
			ret = ENOENT;
			goto error;
		}

		/* parent must be encrypted */
		pcrypt = zfs_prop_get_int(pzhp, ZFS_PROP_ENCRYPTION);
		if (pcrypt == ZIO_CRYPT_OFF) {
			zfs_error_aux(pzhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Parent must be encrypted."));
			ret = EINVAL;
			goto error;
		}

		/* check that the parent's key is loaded */
		pkeystatus = zfs_prop_get_int(pzhp, ZFS_PROP_KEYSTATUS);
		if (pkeystatus == ZFS_KEYSTATUS_UNAVAILABLE) {
			zfs_error_aux(pzhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Parent key must be loaded."));
			ret = EACCES;
			goto error;
		}
	}

	/* check that the key is loaded */
	keystatus = zfs_prop_get_int(zhp, ZFS_PROP_KEYSTATUS);
	if (keystatus == ZFS_KEYSTATUS_UNAVAILABLE) {
		zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
		    "Key must be loaded."));
		ret = EACCES;
		goto error;
	}

	/* call the ioctl */
	ret = lzc_change_key(zhp->zfs_name, cmd, props, wkeydata, wkeylen);
	if (ret != 0) {
		switch (ret) {
		case EPERM:
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Permission denied."));
			break;
		case EINVAL:
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Invalid properties for key change."));
			break;
		case EACCES:
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Key is not currently loaded."));
			break;
		}
		zfs_error(zhp->zfs_hdl, EZFS_CRYPTOFAILED, errbuf);
	}

	if (pzhp != NULL)
		zfs_close(pzhp);
	if (props != NULL)
		nvlist_free(props);
	if (wkeydata != NULL)
		free(wkeydata);

	return (ret);

error:
	if (pzhp != NULL)
		zfs_close(pzhp);
	if (props != NULL)
		nvlist_free(props);
	if (wkeydata != NULL)
		free(wkeydata);

	zfs_error(zhp->zfs_hdl, EZFS_CRYPTOFAILED, errbuf);
	return (ret);
}