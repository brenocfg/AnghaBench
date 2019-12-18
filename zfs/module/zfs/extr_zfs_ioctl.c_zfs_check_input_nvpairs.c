#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int zvec_nvl_key_count; TYPE_2__* zvec_nvl_keys; } ;
typedef  TYPE_1__ zfs_ioc_vec_t ;
struct TYPE_5__ {int zkey_flags; char* zkey_name; scalar_t__ zkey_type; } ;
typedef  TYPE_2__ zfs_ioc_key_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ data_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ DATA_TYPE_ANY ; 
 scalar_t__ DATA_TYPE_NVLIST ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_ERR_IOC_ARG_BADTYPE ; 
 int /*<<< orphan*/  ZFS_ERR_IOC_ARG_REQUIRED ; 
 int /*<<< orphan*/  ZFS_ERR_IOC_ARG_UNAVAIL ; 
 int ZK_OPTIONAL ; 
 int ZK_WILDCARDLIST ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_type (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
zfs_check_input_nvpairs(nvlist_t *innvl, const zfs_ioc_vec_t *vec)
{
	const zfs_ioc_key_t *nvl_keys = vec->zvec_nvl_keys;
	boolean_t required_keys_found = B_FALSE;

	/*
	 * examine each input pair
	 */
	for (nvpair_t *pair = nvlist_next_nvpair(innvl, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(innvl, pair)) {
		char *name = nvpair_name(pair);
		data_type_t type = nvpair_type(pair);
		boolean_t identified = B_FALSE;

		/*
		 * check pair against the documented names and type
		 */
		for (int k = 0; k < vec->zvec_nvl_key_count; k++) {
			/* if not a wild card name, check for an exact match */
			if ((nvl_keys[k].zkey_flags & ZK_WILDCARDLIST) == 0 &&
			    strcmp(nvl_keys[k].zkey_name, name) != 0)
				continue;

			identified = B_TRUE;

			if (nvl_keys[k].zkey_type != DATA_TYPE_ANY &&
			    nvl_keys[k].zkey_type != type) {
				return (SET_ERROR(ZFS_ERR_IOC_ARG_BADTYPE));
			}

			if (nvl_keys[k].zkey_flags & ZK_OPTIONAL)
				continue;

			required_keys_found = B_TRUE;
			break;
		}

		/* allow an 'optional' key, everything else is invalid */
		if (!identified &&
		    (strcmp(name, "optional") != 0 ||
		    type != DATA_TYPE_NVLIST)) {
			return (SET_ERROR(ZFS_ERR_IOC_ARG_UNAVAIL));
		}
	}

	/* verify that all required keys were found */
	for (int k = 0; k < vec->zvec_nvl_key_count; k++) {
		if (nvl_keys[k].zkey_flags & ZK_OPTIONAL)
			continue;

		if (nvl_keys[k].zkey_flags & ZK_WILDCARDLIST) {
			/* at least one non-optional key is expected here */
			if (!required_keys_found)
				return (SET_ERROR(ZFS_ERR_IOC_ARG_REQUIRED));
			continue;
		}

		if (!nvlist_exists(innvl, nvl_keys[k].zkey_name))
			return (SET_ERROR(ZFS_ERR_IOC_ARG_REQUIRED));
	}

	return (0);
}