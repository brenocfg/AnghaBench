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
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 char const* ZFS_DELEG_PERM_ALLOW ; 
 int dsl_deleg_access (char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

int
dsl_deleg_can_allow(char *ddname, nvlist_t *nvp, cred_t *cr)
{
	nvpair_t *whopair = NULL;
	int error;

	if ((error = dsl_deleg_access(ddname, ZFS_DELEG_PERM_ALLOW, cr)) != 0)
		return (error);

	while ((whopair = nvlist_next_nvpair(nvp, whopair))) {
		nvlist_t *perms;
		nvpair_t *permpair = NULL;

		VERIFY(nvpair_value_nvlist(whopair, &perms) == 0);

		while ((permpair = nvlist_next_nvpair(perms, permpair))) {
			const char *perm = nvpair_name(permpair);

			if (strcmp(perm, ZFS_DELEG_PERM_ALLOW) == 0)
				return (SET_ERROR(EPERM));

			if ((error = dsl_deleg_access(ddname, perm, cr)) != 0)
				return (error);
		}
	}
	return (0);
}