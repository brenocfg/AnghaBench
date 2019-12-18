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
 scalar_t__ DATA_TYPE_STRING ; 
 int /*<<< orphan*/  E2BIG ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ZAP_MAXNAMELEN ; 
 scalar_t__ ZAP_MAXVALUELEN ; 
 char const* fnvpair_value_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_type (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  zfs_prop_user (char const*) ; 

__attribute__((used)) static int
zfs_check_userprops(nvlist_t *nvl)
{
	nvpair_t *pair = NULL;

	while ((pair = nvlist_next_nvpair(nvl, pair)) != NULL) {
		const char *propname = nvpair_name(pair);

		if (!zfs_prop_user(propname) ||
		    nvpair_type(pair) != DATA_TYPE_STRING)
			return (SET_ERROR(EINVAL));

		if (strlen(propname) >= ZAP_MAXNAMELEN)
			return (SET_ERROR(ENAMETOOLONG));

		if (strlen(fnvpair_value_string(pair)) >= ZAP_MAXVALUELEN)
			return (SET_ERROR(E2BIG));
	}
	return (0);
}