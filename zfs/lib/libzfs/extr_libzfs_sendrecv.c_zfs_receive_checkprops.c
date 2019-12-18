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
typedef  scalar_t__ zfs_prop_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 scalar_t__ ZFS_PROP_ENCRYPTION ; 
 scalar_t__ ZFS_PROP_ORIGIN ; 
 scalar_t__ ZFS_PROP_VERSION ; 
 scalar_t__ ZFS_PROP_VOLSIZE ; 
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ zfs_name_to_prop (char const*) ; 
 scalar_t__ zfs_prop_encryption_key_param (scalar_t__) ; 
 scalar_t__ zfs_prop_readonly (scalar_t__) ; 
 int /*<<< orphan*/  zfs_prop_user (char const*) ; 

__attribute__((used)) static boolean_t
zfs_receive_checkprops(libzfs_handle_t *hdl, nvlist_t *props,
    const char *errbuf)
{
	nvpair_t *nvp;
	zfs_prop_t prop;
	const char *name;

	nvp = NULL;
	while ((nvp = nvlist_next_nvpair(props, nvp)) != NULL) {
		name = nvpair_name(nvp);
		prop = zfs_name_to_prop(name);

		if (prop == ZPROP_INVAL) {
			if (!zfs_prop_user(name)) {
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "invalid property '%s'"), name);
				return (B_FALSE);
			}
			continue;
		}
		/*
		 * "origin" is readonly but is used to receive datasets as
		 * clones so we don't raise an error here
		 */
		if (prop == ZFS_PROP_ORIGIN)
			continue;

		/* encryption params have their own verification later */
		if (prop == ZFS_PROP_ENCRYPTION ||
		    zfs_prop_encryption_key_param(prop))
			continue;

		/*
		 * cannot override readonly, set-once and other specific
		 * settable properties
		 */
		if (zfs_prop_readonly(prop) || prop == ZFS_PROP_VERSION ||
		    prop == ZFS_PROP_VOLSIZE) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "invalid property '%s'"), name);
			return (B_FALSE);
		}
	}

	return (B_TRUE);
}