#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct mnttab {int /*<<< orphan*/  mnt_mntopts; int /*<<< orphan*/  mnt_fstype; int /*<<< orphan*/  mnt_mountp; int /*<<< orphan*/  mnt_special; } ;
struct TYPE_11__ {TYPE_2__* mnt_mntopts; TYPE_2__* mnt_fstype; TYPE_2__* mnt_mountp; TYPE_2__* mnt_special; } ;
struct TYPE_12__ {TYPE_1__ mtn_mt; } ;
typedef  TYPE_2__ mnttab_node_t ;
struct TYPE_13__ {int /*<<< orphan*/  libzfs_mnttab_cache; int /*<<< orphan*/  libzfs_mnttab; } ;
typedef  TYPE_3__ libzfs_handle_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MNTTAB ; 
 int /*<<< orphan*/  MNTTYPE_ZFS ; 
 int /*<<< orphan*/  avl_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * avl_find (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/ * freopen (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ getmntent (int /*<<< orphan*/ ,struct mnttab*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* zfs_alloc (TYPE_3__*,int) ; 
 void* zfs_strdup (TYPE_3__*,int /*<<< orphan*/ ) ; 

int
libzfs_mnttab_update(libzfs_handle_t *hdl)
{
	struct mnttab entry;

	/* Reopen MNTTAB to prevent reading stale data from open file */
	if (freopen(MNTTAB, "r", hdl->libzfs_mnttab) == NULL)
		return (ENOENT);

	while (getmntent(hdl->libzfs_mnttab, &entry) == 0) {
		mnttab_node_t *mtn;
		avl_index_t where;

		if (strcmp(entry.mnt_fstype, MNTTYPE_ZFS) != 0)
			continue;

		mtn = zfs_alloc(hdl, sizeof (mnttab_node_t));
		mtn->mtn_mt.mnt_special = zfs_strdup(hdl, entry.mnt_special);
		mtn->mtn_mt.mnt_mountp = zfs_strdup(hdl, entry.mnt_mountp);
		mtn->mtn_mt.mnt_fstype = zfs_strdup(hdl, entry.mnt_fstype);
		mtn->mtn_mt.mnt_mntopts = zfs_strdup(hdl, entry.mnt_mntopts);

		/* Exclude duplicate mounts */
		if (avl_find(&hdl->libzfs_mnttab_cache, mtn, &where) != NULL) {
			free(mtn->mtn_mt.mnt_special);
			free(mtn->mtn_mt.mnt_mountp);
			free(mtn->mtn_mt.mnt_fstype);
			free(mtn->mtn_mt.mnt_mntopts);
			free(mtn);
			continue;
		}

		avl_add(&hdl->libzfs_mnttab_cache, mtn);
	}

	return (0);
}