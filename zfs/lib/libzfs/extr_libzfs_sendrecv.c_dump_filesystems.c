#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  fss; int /*<<< orphan*/  fsavl; int /*<<< orphan*/  replicate; } ;
typedef  TYPE_2__ send_dump_data_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int dump_filesystem (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * fsavl_find (int /*<<< orphan*/ ,scalar_t__,char**) ; 
 scalar_t__ nvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_lookup_boolean (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_remove_all (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 TYPE_1__* zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_filesystems(zfs_handle_t *rzhp, void *arg)
{
	send_dump_data_t *sdd = arg;
	nvpair_t *fspair;
	boolean_t needagain, progress;

	if (!sdd->replicate)
		return (dump_filesystem(rzhp, sdd));

	/* Mark the clone origin snapshots. */
	for (fspair = nvlist_next_nvpair(sdd->fss, NULL); fspair;
	    fspair = nvlist_next_nvpair(sdd->fss, fspair)) {
		nvlist_t *nvfs;
		uint64_t origin_guid = 0;

		VERIFY(0 == nvpair_value_nvlist(fspair, &nvfs));
		(void) nvlist_lookup_uint64(nvfs, "origin", &origin_guid);
		if (origin_guid != 0) {
			char *snapname;
			nvlist_t *origin_nv = fsavl_find(sdd->fsavl,
			    origin_guid, &snapname);
			if (origin_nv != NULL) {
				nvlist_t *snapprops;
				VERIFY(0 == nvlist_lookup_nvlist(origin_nv,
				    "snapprops", &snapprops));
				VERIFY(0 == nvlist_lookup_nvlist(snapprops,
				    snapname, &snapprops));
				VERIFY(0 == nvlist_add_boolean(
				    snapprops, "is_clone_origin"));
			}
		}
	}
again:
	needagain = progress = B_FALSE;
	for (fspair = nvlist_next_nvpair(sdd->fss, NULL); fspair;
	    fspair = nvlist_next_nvpair(sdd->fss, fspair)) {
		nvlist_t *fslist, *parent_nv;
		char *fsname;
		zfs_handle_t *zhp;
		int err;
		uint64_t origin_guid = 0;
		uint64_t parent_guid = 0;

		VERIFY(nvpair_value_nvlist(fspair, &fslist) == 0);
		if (nvlist_lookup_boolean(fslist, "sent") == 0)
			continue;

		VERIFY(nvlist_lookup_string(fslist, "name", &fsname) == 0);
		(void) nvlist_lookup_uint64(fslist, "origin", &origin_guid);
		(void) nvlist_lookup_uint64(fslist, "parentfromsnap",
		    &parent_guid);

		if (parent_guid != 0) {
			parent_nv = fsavl_find(sdd->fsavl, parent_guid, NULL);
			if (!nvlist_exists(parent_nv, "sent")) {
				/* parent has not been sent; skip this one */
				needagain = B_TRUE;
				continue;
			}
		}

		if (origin_guid != 0) {
			nvlist_t *origin_nv = fsavl_find(sdd->fsavl,
			    origin_guid, NULL);
			if (origin_nv != NULL &&
			    !nvlist_exists(origin_nv, "sent")) {
				/*
				 * origin has not been sent yet;
				 * skip this clone.
				 */
				needagain = B_TRUE;
				continue;
			}
		}

		zhp = zfs_open(rzhp->zfs_hdl, fsname, ZFS_TYPE_DATASET);
		if (zhp == NULL)
			return (-1);
		err = dump_filesystem(zhp, sdd);
		VERIFY(nvlist_add_boolean(fslist, "sent") == 0);
		progress = B_TRUE;
		zfs_close(zhp);
		if (err)
			return (err);
	}
	if (needagain) {
		assert(progress);
		goto again;
	}

	/* clean out the sent flags in case we reuse this fss */
	for (fspair = nvlist_next_nvpair(sdd->fss, NULL); fspair;
	    fspair = nvlist_next_nvpair(sdd->fss, fspair)) {
		nvlist_t *fslist;

		VERIFY(nvpair_value_nvlist(fspair, &fslist) == 0);
		(void) nvlist_remove_all(fslist, "sent");
	}

	return (0);
}