#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  zfs_type_t ;
typedef  scalar_t__ zfs_prop_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
#define  DATA_TYPE_BOOLEAN 129 
#define  DATA_TYPE_STRING 128 
 int /*<<< orphan*/  EZFS_BADPROP ; 
 int /*<<< orphan*/  EZFS_CRYPTOFAILED ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 scalar_t__ ZFS_PROP_ENCRYPTION ; 
 scalar_t__ ZFS_PROP_ORIGIN ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  ZPROP_SOURCE ; 
 int /*<<< orphan*/  ZPROP_SOURCE_VAL_RECVD ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fnvlist_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_remove (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int nvpair_type (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_crypto_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_dataset_exists (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ zfs_name_to_prop (char const*) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_encryption_key_param (scalar_t__) ; 
 int /*<<< orphan*/  zfs_prop_inheritable (scalar_t__) ; 
 int /*<<< orphan*/  zfs_prop_user (char const*) ; 
 int /*<<< orphan*/  zfs_prop_valid_for_type (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_valid_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
zfs_setup_cmdline_props(libzfs_handle_t *hdl, zfs_type_t type,
    char *fsname, boolean_t zoned, boolean_t recursive, boolean_t newfs,
    boolean_t raw, boolean_t toplevel, nvlist_t *recvprops, nvlist_t *cmdprops,
    nvlist_t *origprops, nvlist_t **oxprops, uint8_t **wkeydata_out,
    uint_t *wkeylen_out, const char *errbuf)
{
	nvpair_t *nvp;
	nvlist_t *oprops, *voprops;
	zfs_handle_t *zhp = NULL;
	zpool_handle_t *zpool_hdl = NULL;
	char *cp;
	int ret = 0;
	char namebuf[ZFS_MAX_DATASET_NAME_LEN];

	if (nvlist_empty(cmdprops))
		return (0); /* No properties to override or exclude */

	*oxprops = fnvlist_alloc();
	oprops = fnvlist_alloc();

	strlcpy(namebuf, fsname, ZFS_MAX_DATASET_NAME_LEN);

	/*
	 * Get our dataset handle. The target dataset may not exist yet.
	 */
	if (zfs_dataset_exists(hdl, namebuf, ZFS_TYPE_DATASET)) {
		zhp = zfs_open(hdl, namebuf, ZFS_TYPE_DATASET);
		if (zhp == NULL) {
			ret = -1;
			goto error;
		}
	}

	/* open the zpool handle */
	cp = strchr(namebuf, '/');
	if (cp != NULL)
		*cp = '\0';
	zpool_hdl = zpool_open(hdl, namebuf);
	if (zpool_hdl == NULL) {
		ret = -1;
		goto error;
	}

	/* restore namebuf to match fsname for later use */
	if (cp != NULL)
		*cp = '/';

	/*
	 * first iteration: process excluded (-x) properties now and gather
	 * added (-o) properties to be later processed by zfs_valid_proplist()
	 */
	nvp = NULL;
	while ((nvp = nvlist_next_nvpair(cmdprops, nvp)) != NULL) {
		const char *name = nvpair_name(nvp);
		zfs_prop_t prop = zfs_name_to_prop(name);

		/* "origin" is processed separately, don't handle it here */
		if (prop == ZFS_PROP_ORIGIN)
			continue;

		/*
		 * we're trying to override or exclude a property that does not
		 * make sense for this type of dataset, but we don't want to
		 * fail if the receive is recursive: this comes in handy when
		 * the send stream contains, for instance, a child ZVOL and
		 * we're trying to receive it with "-o atime=on"
		 */
		if (!zfs_prop_valid_for_type(prop, type, B_FALSE) &&
		    !zfs_prop_user(name)) {
			if (recursive)
				continue;
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "property '%s' does not apply to datasets of this "
			    "type"), name);
			ret = zfs_error(hdl, EZFS_BADPROP, errbuf);
			goto error;
		}

		/* raw streams can't override encryption properties */
		if ((zfs_prop_encryption_key_param(prop) ||
		    prop == ZFS_PROP_ENCRYPTION) && raw) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "encryption property '%s' cannot "
			    "be set or excluded for raw streams."), name);
			ret = zfs_error(hdl, EZFS_BADPROP, errbuf);
			goto error;
		}

		/* incremental streams can only exclude encryption properties */
		if ((zfs_prop_encryption_key_param(prop) ||
		    prop == ZFS_PROP_ENCRYPTION) && !newfs &&
		    nvpair_type(nvp) != DATA_TYPE_BOOLEAN) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "encryption property '%s' cannot "
			    "be set for incremental streams."), name);
			ret = zfs_error(hdl, EZFS_BADPROP, errbuf);
			goto error;
		}

		switch (nvpair_type(nvp)) {
		case DATA_TYPE_BOOLEAN: /* -x property */
			/*
			 * DATA_TYPE_BOOLEAN is the way we're asked to "exclude"
			 * a property: this is done by forcing an explicit
			 * inherit on the destination so the effective value is
			 * not the one we received from the send stream.
			 * We do this only if the property is not already
			 * locally-set, in which case its value will take
			 * priority over the received anyway.
			 */
			if (nvlist_exists(origprops, name)) {
				nvlist_t *attrs;
				char *source = NULL;

				attrs = fnvlist_lookup_nvlist(origprops, name);
				if (nvlist_lookup_string(attrs,
				    ZPROP_SOURCE, &source) == 0 &&
				    strcmp(source, ZPROP_SOURCE_VAL_RECVD) != 0)
					continue;
			}
			/*
			 * We can't force an explicit inherit on non-inheritable
			 * properties: if we're asked to exclude this kind of
			 * values we remove them from "recvprops" input nvlist.
			 */
			if (!zfs_prop_inheritable(prop) &&
			    !zfs_prop_user(name) && /* can be inherited too */
			    nvlist_exists(recvprops, name))
				fnvlist_remove(recvprops, name);
			else
				fnvlist_add_nvpair(*oxprops, nvp);
			break;
		case DATA_TYPE_STRING: /* -o property=value */
			fnvlist_add_nvpair(oprops, nvp);
			break;
		default:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "property '%s' must be a string or boolean"), name);
			ret = zfs_error(hdl, EZFS_BADPROP, errbuf);
			goto error;
		}
	}

	if (toplevel) {
		/* convert override strings properties to native */
		if ((voprops = zfs_valid_proplist(hdl, ZFS_TYPE_DATASET,
		    oprops, zoned, zhp, zpool_hdl, B_FALSE, errbuf)) == NULL) {
			ret = zfs_error(hdl, EZFS_BADPROP, errbuf);
			goto error;
		}

		/*
		 * zfs_crypto_create() requires the parent name. Get it
		 * by truncating the fsname copy stored in namebuf.
		 */
		cp = strrchr(namebuf, '/');
		if (cp != NULL)
			*cp = '\0';

		if (!raw && zfs_crypto_create(hdl, namebuf, voprops, NULL,
		    B_FALSE, wkeydata_out, wkeylen_out) != 0) {
			fnvlist_free(voprops);
			ret = zfs_error(hdl, EZFS_CRYPTOFAILED, errbuf);
			goto error;
		}

		/* second pass: process "-o" properties */
		fnvlist_merge(*oxprops, voprops);
		fnvlist_free(voprops);
	} else {
		/* override props on child dataset are inherited */
		nvp = NULL;
		while ((nvp = nvlist_next_nvpair(oprops, nvp)) != NULL) {
			const char *name = nvpair_name(nvp);
			fnvlist_add_boolean(*oxprops, name);
		}
	}

error:
	if (zhp != NULL)
		zfs_close(zhp);
	if (zpool_hdl != NULL)
		zpool_close(zpool_hdl);
	fnvlist_free(oprops);
	return (ret);
}