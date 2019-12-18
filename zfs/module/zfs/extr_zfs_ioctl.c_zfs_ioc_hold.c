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
typedef  scalar_t__ minor_t ;

/* Variables and functions */
 int EINVAL ; 
 int SET_ERROR (int) ; 
 int dsl_dataset_user_hold (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_lookup_int32 (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nvpair_value_string (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ strlen (char*) ; 
 int zfs_onexit_fd_hold (int,scalar_t__*) ; 
 int /*<<< orphan*/  zfs_onexit_fd_rele (int) ; 

__attribute__((used)) static int
zfs_ioc_hold(const char *pool, nvlist_t *args, nvlist_t *errlist)
{
	nvpair_t *pair;
	nvlist_t *holds;
	int cleanup_fd = -1;
	int error;
	minor_t minor = 0;

	holds = fnvlist_lookup_nvlist(args, "holds");

	/* make sure the user didn't pass us any invalid (empty) tags */
	for (pair = nvlist_next_nvpair(holds, NULL); pair != NULL;
	    pair = nvlist_next_nvpair(holds, pair)) {
		char *htag;

		error = nvpair_value_string(pair, &htag);
		if (error != 0)
			return (SET_ERROR(error));

		if (strlen(htag) == 0)
			return (SET_ERROR(EINVAL));
	}

	if (nvlist_lookup_int32(args, "cleanup_fd", &cleanup_fd) == 0) {
		error = zfs_onexit_fd_hold(cleanup_fd, &minor);
		if (error != 0)
			return (SET_ERROR(error));
	}

	error = dsl_dataset_user_hold(holds, minor, errlist);
	if (minor != 0)
		zfs_onexit_fd_rele(cleanup_fd);
	return (SET_ERROR(error));
}