#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* member_0; char* zc_name; void* zc_cookie; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  tryname ;
struct TYPE_11__ {scalar_t__ verbose; scalar_t__ isprefix; int /*<<< orphan*/  force; scalar_t__ dryrun; } ;
typedef  TYPE_2__ recvflags_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int boolean_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int B_FALSE ; 
 void* B_TRUE ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZFS_IOC_SET_PROP ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int created_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fsavl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fsavl_find (int /*<<< orphan*/ *,scalar_t__,char**) ; 
 int gather_nvlist (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ *,int,void*,int,int,int,int,int,void*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_boolean (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ nvpair_value_uint64 (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int recv_destroy (int /*<<< orphan*/ *,char*,scalar_t__,char*,TYPE_2__*) ; 
 int recv_promote (int /*<<< orphan*/ *,char*,char*,TYPE_2__*) ; 
 int recv_rename (int /*<<< orphan*/ *,char*,char*,scalar_t__,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_1__*) ; 
 scalar_t__ zcmd_write_src_nvlist (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
recv_incremental_replication(libzfs_handle_t *hdl, const char *tofs,
    recvflags_t *flags, nvlist_t *stream_nv, avl_tree_t *stream_avl,
    nvlist_t *renamed)
{
	nvlist_t *local_nv, *deleted = NULL;
	avl_tree_t *local_avl;
	nvpair_t *fselem, *nextfselem;
	char *fromsnap;
	char newname[ZFS_MAX_DATASET_NAME_LEN];
	char guidname[32];
	int error;
	boolean_t needagain, progress, recursive;
	char *s1, *s2;

	VERIFY(0 == nvlist_lookup_string(stream_nv, "fromsnap", &fromsnap));

	recursive = (nvlist_lookup_boolean(stream_nv, "not_recursive") ==
	    ENOENT);

	if (flags->dryrun)
		return (0);

again:
	needagain = progress = B_FALSE;

	VERIFY(0 == nvlist_alloc(&deleted, NV_UNIQUE_NAME, 0));

	if ((error = gather_nvlist(hdl, tofs, fromsnap, NULL,
	    recursive, B_TRUE, B_FALSE, recursive, B_FALSE, B_FALSE,
	    B_FALSE, B_TRUE, &local_nv, &local_avl)) != 0)
		return (error);

	/*
	 * Process deletes and renames
	 */
	for (fselem = nvlist_next_nvpair(local_nv, NULL);
	    fselem; fselem = nextfselem) {
		nvlist_t *nvfs, *snaps;
		nvlist_t *stream_nvfs = NULL;
		nvpair_t *snapelem, *nextsnapelem;
		uint64_t fromguid = 0;
		uint64_t originguid = 0;
		uint64_t stream_originguid = 0;
		uint64_t parent_fromsnap_guid, stream_parent_fromsnap_guid;
		char *fsname, *stream_fsname;

		nextfselem = nvlist_next_nvpair(local_nv, fselem);

		VERIFY(0 == nvpair_value_nvlist(fselem, &nvfs));
		VERIFY(0 == nvlist_lookup_nvlist(nvfs, "snaps", &snaps));
		VERIFY(0 == nvlist_lookup_string(nvfs, "name", &fsname));
		VERIFY(0 == nvlist_lookup_uint64(nvfs, "parentfromsnap",
		    &parent_fromsnap_guid));
		(void) nvlist_lookup_uint64(nvfs, "origin", &originguid);

		/*
		 * First find the stream's fs, so we can check for
		 * a different origin (due to "zfs promote")
		 */
		for (snapelem = nvlist_next_nvpair(snaps, NULL);
		    snapelem; snapelem = nvlist_next_nvpair(snaps, snapelem)) {
			uint64_t thisguid;

			VERIFY(0 == nvpair_value_uint64(snapelem, &thisguid));
			stream_nvfs = fsavl_find(stream_avl, thisguid, NULL);

			if (stream_nvfs != NULL)
				break;
		}

		/* check for promote */
		(void) nvlist_lookup_uint64(stream_nvfs, "origin",
		    &stream_originguid);
		if (stream_nvfs && originguid != stream_originguid) {
			switch (created_before(hdl, local_avl,
			    stream_originguid, originguid)) {
			case 1: {
				/* promote it! */
				nvlist_t *origin_nvfs;
				char *origin_fsname;

				origin_nvfs = fsavl_find(local_avl, originguid,
				    NULL);
				VERIFY(0 == nvlist_lookup_string(origin_nvfs,
				    "name", &origin_fsname));
				error = recv_promote(hdl, fsname, origin_fsname,
				    flags);
				if (error == 0)
					progress = B_TRUE;
				break;
			}
			default:
				break;
			case -1:
				fsavl_destroy(local_avl);
				nvlist_free(local_nv);
				return (-1);
			}
			/*
			 * We had/have the wrong origin, therefore our
			 * list of snapshots is wrong.  Need to handle
			 * them on the next pass.
			 */
			needagain = B_TRUE;
			continue;
		}

		for (snapelem = nvlist_next_nvpair(snaps, NULL);
		    snapelem; snapelem = nextsnapelem) {
			uint64_t thisguid;
			char *stream_snapname;
			nvlist_t *found, *props;

			nextsnapelem = nvlist_next_nvpair(snaps, snapelem);

			VERIFY(0 == nvpair_value_uint64(snapelem, &thisguid));
			found = fsavl_find(stream_avl, thisguid,
			    &stream_snapname);

			/* check for delete */
			if (found == NULL) {
				char name[ZFS_MAX_DATASET_NAME_LEN];

				if (!flags->force)
					continue;

				(void) snprintf(name, sizeof (name), "%s@%s",
				    fsname, nvpair_name(snapelem));

				error = recv_destroy(hdl, name,
				    strlen(fsname)+1, newname, flags);
				if (error)
					needagain = B_TRUE;
				else
					progress = B_TRUE;
				sprintf(guidname, "%llu",
				    (u_longlong_t)thisguid);
				nvlist_add_boolean(deleted, guidname);
				continue;
			}

			stream_nvfs = found;

			if (0 == nvlist_lookup_nvlist(stream_nvfs, "snapprops",
			    &props) && 0 == nvlist_lookup_nvlist(props,
			    stream_snapname, &props)) {
				zfs_cmd_t zc = {"\0"};

				zc.zc_cookie = B_TRUE; /* received */
				(void) snprintf(zc.zc_name, sizeof (zc.zc_name),
				    "%s@%s", fsname, nvpair_name(snapelem));
				if (zcmd_write_src_nvlist(hdl, &zc,
				    props) == 0) {
					(void) zfs_ioctl(hdl,
					    ZFS_IOC_SET_PROP, &zc);
					zcmd_free_nvlists(&zc);
				}
			}

			/* check for different snapname */
			if (strcmp(nvpair_name(snapelem),
			    stream_snapname) != 0) {
				char name[ZFS_MAX_DATASET_NAME_LEN];
				char tryname[ZFS_MAX_DATASET_NAME_LEN];

				(void) snprintf(name, sizeof (name), "%s@%s",
				    fsname, nvpair_name(snapelem));
				(void) snprintf(tryname, sizeof (name), "%s@%s",
				    fsname, stream_snapname);

				error = recv_rename(hdl, name, tryname,
				    strlen(fsname)+1, newname, flags);
				if (error)
					needagain = B_TRUE;
				else
					progress = B_TRUE;
			}

			if (strcmp(stream_snapname, fromsnap) == 0)
				fromguid = thisguid;
		}

		/* check for delete */
		if (stream_nvfs == NULL) {
			if (!flags->force)
				continue;

			error = recv_destroy(hdl, fsname, strlen(tofs)+1,
			    newname, flags);
			if (error)
				needagain = B_TRUE;
			else
				progress = B_TRUE;
			sprintf(guidname, "%llu",
			    (u_longlong_t)parent_fromsnap_guid);
			nvlist_add_boolean(deleted, guidname);
			continue;
		}

		if (fromguid == 0) {
			if (flags->verbose) {
				(void) printf("local fs %s does not have "
				    "fromsnap (%s in stream); must have "
				    "been deleted locally; ignoring\n",
				    fsname, fromsnap);
			}
			continue;
		}

		VERIFY(0 == nvlist_lookup_string(stream_nvfs,
		    "name", &stream_fsname));
		VERIFY(0 == nvlist_lookup_uint64(stream_nvfs,
		    "parentfromsnap", &stream_parent_fromsnap_guid));

		s1 = strrchr(fsname, '/');
		s2 = strrchr(stream_fsname, '/');

		/*
		 * Check if we're going to rename based on parent guid change
		 * and the current parent guid was also deleted. If it was then
		 * rename will fail and is likely unneeded, so avoid this and
		 * force an early retry to determine the new
		 * parent_fromsnap_guid.
		 */
		if (stream_parent_fromsnap_guid != 0 &&
		    parent_fromsnap_guid != 0 &&
		    stream_parent_fromsnap_guid != parent_fromsnap_guid) {
			sprintf(guidname, "%llu",
			    (u_longlong_t)parent_fromsnap_guid);
			if (nvlist_exists(deleted, guidname)) {
				progress = B_TRUE;
				needagain = B_TRUE;
				goto doagain;
			}
		}

		/*
		 * Check for rename. If the exact receive path is specified, it
		 * does not count as a rename, but we still need to check the
		 * datasets beneath it.
		 */
		if ((stream_parent_fromsnap_guid != 0 &&
		    parent_fromsnap_guid != 0 &&
		    stream_parent_fromsnap_guid != parent_fromsnap_guid) ||
		    ((flags->isprefix || strcmp(tofs, fsname) != 0) &&
		    (s1 != NULL) && (s2 != NULL) && strcmp(s1, s2) != 0)) {
			nvlist_t *parent;
			char tryname[ZFS_MAX_DATASET_NAME_LEN];

			parent = fsavl_find(local_avl,
			    stream_parent_fromsnap_guid, NULL);
			/*
			 * NB: parent might not be found if we used the
			 * tosnap for stream_parent_fromsnap_guid,
			 * because the parent is a newly-created fs;
			 * we'll be able to rename it after we recv the
			 * new fs.
			 */
			if (parent != NULL) {
				char *pname;

				VERIFY(0 == nvlist_lookup_string(parent, "name",
				    &pname));
				(void) snprintf(tryname, sizeof (tryname),
				    "%s%s", pname, strrchr(stream_fsname, '/'));
			} else {
				tryname[0] = '\0';
				if (flags->verbose) {
					(void) printf("local fs %s new parent "
					    "not found\n", fsname);
				}
			}

			newname[0] = '\0';

			error = recv_rename(hdl, fsname, tryname,
			    strlen(tofs)+1, newname, flags);

			if (renamed != NULL && newname[0] != '\0') {
				VERIFY(0 == nvlist_add_boolean(renamed,
				    newname));
			}

			if (error)
				needagain = B_TRUE;
			else
				progress = B_TRUE;
		}
	}

doagain:
	fsavl_destroy(local_avl);
	nvlist_free(local_nv);
	nvlist_free(deleted);

	if (needagain && progress) {
		/* do another pass to fix up temporary names */
		if (flags->verbose)
			(void) printf("another pass:\n");
		goto again;
	}

	return (needagain || error != 0);
}