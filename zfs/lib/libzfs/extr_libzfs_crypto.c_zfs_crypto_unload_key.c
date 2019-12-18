#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_name; int /*<<< orphan*/  zpool_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
#define  EACCES 130 
#define  EBUSY 129 
 int EINVAL ; 
#define  EPERM 128 
 int /*<<< orphan*/  EZFS_CRYPTOFAILED ; 
 int MAXNAMELEN ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 scalar_t__ ZFS_KEYFORMAT_NONE ; 
 scalar_t__ ZFS_KEYSTATUS_UNAVAILABLE ; 
 int /*<<< orphan*/  ZFS_PROP_KEYFORMAT ; 
 int /*<<< orphan*/  ZFS_PROP_KEYSTATUS ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  encryption_feature_is_enabled (int /*<<< orphan*/ ) ; 
 int lzc_unload_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int zfs_crypto_get_encryption_root (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zfs_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  zfs_get_name (TYPE_1__*) ; 
 scalar_t__ zfs_prop_get_int (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
zfs_crypto_unload_key(zfs_handle_t *zhp)
{
	int ret;
	char errbuf[1024];
	char prop_encroot[MAXNAMELEN];
	uint64_t keystatus, keyformat;
	boolean_t is_encroot;

	(void) snprintf(errbuf, sizeof (errbuf),
	    dgettext(TEXT_DOMAIN, "Key unload error"));

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
		    "Keys must be unloaded for encryption root of '%s' (%s)."),
		    zfs_get_name(zhp), prop_encroot);
		ret = EINVAL;
		goto error;
	}

	/* check that the key is loaded */
	keystatus = zfs_prop_get_int(zhp, ZFS_PROP_KEYSTATUS);
	if (keystatus == ZFS_KEYSTATUS_UNAVAILABLE) {
		zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
		    "Key already unloaded for '%s'."), zfs_get_name(zhp));
		ret = EACCES;
		goto error;
	}

	/* call the ioctl */
	ret = lzc_unload_key(zhp->zfs_name);

	if (ret != 0) {
		switch (ret) {
		case EPERM:
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Permission denied."));
			break;
		case EACCES:
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Key already unloaded for '%s'."),
			    zfs_get_name(zhp));
			break;
		case EBUSY:
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "'%s' is busy."), zfs_get_name(zhp));
			break;
		}
		zfs_error(zhp->zfs_hdl, EZFS_CRYPTOFAILED, errbuf);
	}

	return (ret);

error:
	zfs_error(zhp->zfs_hdl, EZFS_CRYPTOFAILED, errbuf);
	return (ret);
}