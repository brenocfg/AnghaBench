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
struct TYPE_5__ {TYPE_1__* z_vfs; int /*<<< orphan*/ * z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  fstrans_cookie_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {char* vfs_mntpoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int dmu_snapshot_list_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_config_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  spl_fstrans_mark () ; 
 int /*<<< orphan*/  spl_fstrans_unmark (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfsctl_snapshot_path_objset(zfsvfs_t *zfsvfs, uint64_t objsetid,
    int path_len, char *full_path)
{
	objset_t *os = zfsvfs->z_os;
	fstrans_cookie_t cookie;
	char *snapname;
	boolean_t case_conflict;
	uint64_t id, pos = 0;
	int error = 0;

	if (zfsvfs->z_vfs->vfs_mntpoint == NULL)
		return (SET_ERROR(ENOENT));

	cookie = spl_fstrans_mark();
	snapname = kmem_alloc(ZFS_MAX_DATASET_NAME_LEN, KM_SLEEP);

	while (error == 0) {
		dsl_pool_config_enter(dmu_objset_pool(os), FTAG);
		error = dmu_snapshot_list_next(zfsvfs->z_os,
		    ZFS_MAX_DATASET_NAME_LEN, snapname, &id, &pos,
		    &case_conflict);
		dsl_pool_config_exit(dmu_objset_pool(os), FTAG);
		if (error)
			goto out;

		if (id == objsetid)
			break;
	}

	snprintf(full_path, path_len, "%s/.zfs/snapshot/%s",
	    zfsvfs->z_vfs->vfs_mntpoint, snapname);
out:
	kmem_free(snapname, ZFS_MAX_DATASET_NAME_LEN);
	spl_fstrans_unmark(cookie);

	return (error);
}