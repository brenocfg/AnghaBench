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
typedef  int /*<<< orphan*/  zfs_ioc_t ;
typedef  int /*<<< orphan*/  pname ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int data_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
#define  DATA_TYPE_STRING 128 
 int MAXNAMELEN ; 
 int ZFS_ERR_IOC_ARG_BADTYPE ; 
 int ZFS_ERR_IOC_ARG_REQUIRED ; 
 int ZFS_ERR_IOC_ARG_UNAVAIL ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_remove (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fnvlist_remove_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzc_ioctl_run (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int nvpair_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lzc_ioctl_test(zfs_ioc_t ioc, const char *name, nvlist_t *required,
    nvlist_t *optional, int expected_error, boolean_t wildcard)
{
	nvlist_t *input = fnvlist_alloc();
	nvlist_t *future = fnvlist_alloc();
	int error = 0;

	if (required != NULL) {
		for (nvpair_t *pair = nvlist_next_nvpair(required, NULL);
		    pair != NULL; pair = nvlist_next_nvpair(required, pair)) {
			fnvlist_add_nvpair(input, pair);
		}
	}
	if (optional != NULL) {
		for (nvpair_t *pair = nvlist_next_nvpair(optional, NULL);
		    pair != NULL; pair = nvlist_next_nvpair(optional, pair)) {
			fnvlist_add_nvpair(input, pair);
		}
	}

	/*
	 * Generic input run with 'optional' nvlist pair
	 */
	if (!wildcard)
		fnvlist_add_nvlist(input, "optional", future);
	lzc_ioctl_run(ioc, name, input, expected_error);
	if (!wildcard)
		fnvlist_remove(input, "optional");

	/*
	 * Bogus input value
	 */
	if (!wildcard) {
		fnvlist_add_string(input, "bogus_input", "bogus");
		lzc_ioctl_run(ioc, name, input, ZFS_ERR_IOC_ARG_UNAVAIL);
		fnvlist_remove(input, "bogus_input");
	}

	/*
	 * Missing required inputs
	 */
	if (required != NULL) {
		nvlist_t *empty = fnvlist_alloc();
		lzc_ioctl_run(ioc, name, empty, ZFS_ERR_IOC_ARG_REQUIRED);
		nvlist_free(empty);
	}

	/*
	 * Wrong nvpair type
	 */
	if (required != NULL || optional != NULL) {
		/*
		 * switch the type of one of the input pairs
		 */
		for (nvpair_t *pair = nvlist_next_nvpair(input, NULL);
		    pair != NULL; pair = nvlist_next_nvpair(input, pair)) {
			char pname[MAXNAMELEN];
			data_type_t ptype;

			strlcpy(pname, nvpair_name(pair), sizeof (pname));
			pname[sizeof (pname) - 1] = '\0';
			ptype = nvpair_type(pair);
			fnvlist_remove_nvpair(input, pair);

			switch (ptype) {
			case DATA_TYPE_STRING:
				fnvlist_add_uint64(input, pname, 42);
				break;
			default:
				fnvlist_add_string(input, pname, "bogus");
				break;
			}
		}
		lzc_ioctl_run(ioc, name, input, ZFS_ERR_IOC_ARG_BADTYPE);
	}

	nvlist_free(future);
	nvlist_free(input);

	return (error);
}