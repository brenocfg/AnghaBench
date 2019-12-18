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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EZFS_ISL2CACHE ; 
 scalar_t__ EZFS_ISSPARE ; 
 scalar_t__ EZFS_NODEVICE ; 
 int MAXNAMELEN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  fnvlist_add_int64 (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ fnvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zpool_find_vdev (int /*<<< orphan*/ *,char*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zpool_translate_vdev_guids(zpool_handle_t *zhp, nvlist_t *vds,
    nvlist_t *vdev_guids, nvlist_t *guids_to_paths, nvlist_t **vd_errlist)
{
	nvlist_t *errlist = NULL;
	int error = 0;

	for (nvpair_t *elem = nvlist_next_nvpair(vds, NULL); elem != NULL;
	    elem = nvlist_next_nvpair(vds, elem)) {
		boolean_t spare, cache;

		char *vd_path = nvpair_name(elem);
		nvlist_t *tgt = zpool_find_vdev(zhp, vd_path, &spare, &cache,
		    NULL);

		if ((tgt == NULL) || cache || spare) {
			if (errlist == NULL) {
				errlist = fnvlist_alloc();
				error = EINVAL;
			}

			uint64_t err = (tgt == NULL) ? EZFS_NODEVICE :
			    (spare ? EZFS_ISSPARE : EZFS_ISL2CACHE);
			fnvlist_add_int64(errlist, vd_path, err);
			continue;
		}

		uint64_t guid = fnvlist_lookup_uint64(tgt, ZPOOL_CONFIG_GUID);
		fnvlist_add_uint64(vdev_guids, vd_path, guid);

		char msg[MAXNAMELEN];
		(void) snprintf(msg, sizeof (msg), "%llu", (u_longlong_t)guid);
		fnvlist_add_string(guids_to_paths, msg, vd_path);
	}

	if (error != 0) {
		verify(errlist != NULL);
		if (vd_errlist != NULL)
			*vd_errlist = errlist;
		else
			fnvlist_free(errlist);
	}

	return (error);
}