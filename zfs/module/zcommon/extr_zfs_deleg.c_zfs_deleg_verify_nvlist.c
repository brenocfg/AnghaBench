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
 int ENOENT ; 
 int nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int zfs_valid_permission_name (int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_validate_who (int /*<<< orphan*/ ) ; 

int
zfs_deleg_verify_nvlist(nvlist_t *nvp)
{
	nvpair_t *who, *perm_name;
	nvlist_t *perms;
	int error;

	if (nvp == NULL)
		return (-1);

	who = nvlist_next_nvpair(nvp, NULL);
	if (who == NULL)
		return (-1);

	do {
		if (zfs_validate_who(nvpair_name(who)))
			return (-1);

		error = nvlist_lookup_nvlist(nvp, nvpair_name(who), &perms);

		if (error && error != ENOENT)
			return (-1);
		if (error == ENOENT)
			continue;

		perm_name = nvlist_next_nvpair(perms, NULL);
		if (perm_name == NULL) {
			return (-1);
		}
		do {
			error = zfs_valid_permission_name(
			    nvpair_name(perm_name));
			if (error)
				return (-1);
		} while ((perm_name = nvlist_next_nvpair(perms, perm_name))
		    != NULL);
	} while ((who = nvlist_next_nvpair(nvp, who)) != NULL);
	return (0);
}