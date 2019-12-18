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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRED () ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  EXDEV ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_VERSION_SNAP_PROPS ; 
 int /*<<< orphan*/  ZFS_DELEG_PERM_USERPROP ; 
 int dsl_dataset_snapshot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_lookup_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char const* nvpair_name (int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 int zfs_check_userprops (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_component_namecheck (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_earlier_version (char const*,int /*<<< orphan*/ ) ; 
 int zfs_secpolicy_write_perms (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_ioc_snapshot(const char *poolname, nvlist_t *innvl, nvlist_t *outnvl)
{
	nvlist_t *snaps;
	nvlist_t *props = NULL;
	int error, poollen;
	nvpair_t *pair;

	(void) nvlist_lookup_nvlist(innvl, "props", &props);
	if (!nvlist_empty(props) &&
	    zfs_earlier_version(poolname, SPA_VERSION_SNAP_PROPS))
		return (SET_ERROR(ENOTSUP));
	if ((error = zfs_check_userprops(props)) != 0)
		return (error);

	snaps = fnvlist_lookup_nvlist(innvl, "snaps");
	poollen = strlen(poolname);
	for (pair = nvlist_next_nvpair(snaps, NULL); pair != NULL;
	    pair = nvlist_next_nvpair(snaps, pair)) {
		const char *name = nvpair_name(pair);
		char *cp = strchr(name, '@');

		/*
		 * The snap name must contain an @, and the part after it must
		 * contain only valid characters.
		 */
		if (cp == NULL ||
		    zfs_component_namecheck(cp + 1, NULL, NULL) != 0)
			return (SET_ERROR(EINVAL));

		/*
		 * The snap must be in the specified pool.
		 */
		if (strncmp(name, poolname, poollen) != 0 ||
		    (name[poollen] != '/' && name[poollen] != '@'))
			return (SET_ERROR(EXDEV));

		/*
		 * Check for permission to set the properties on the fs.
		 */
		if (!nvlist_empty(props)) {
			*cp = '\0';
			error = zfs_secpolicy_write_perms(name,
			    ZFS_DELEG_PERM_USERPROP, CRED());
			*cp = '@';
			if (error != 0)
				return (error);
		}

		/* This must be the only snap of this fs. */
		for (nvpair_t *pair2 = nvlist_next_nvpair(snaps, pair);
		    pair2 != NULL; pair2 = nvlist_next_nvpair(snaps, pair2)) {
			if (strncmp(name, nvpair_name(pair2), cp - name + 1)
			    == 0) {
				return (SET_ERROR(EXDEV));
			}
		}
	}

	error = dsl_dataset_snapshot(snaps, props, outnvl);

	return (error);
}