#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* zfs_name; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct holdarg {char* snapname; scalar_t__ recursive; int /*<<< orphan*/  nvl; int /*<<< orphan*/  tag; void* error; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 void* EINVAL ; 
 void* ENOENT ; 
 void* ESRCH ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ lzc_get_holds (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 int zfs_iter_filesystems (TYPE_1__*,int (*) (TYPE_1__*,void*),struct holdarg*) ; 

__attribute__((used)) static int
zfs_release_one(zfs_handle_t *zhp, void *arg)
{
	struct holdarg *ha = arg;
	char name[ZFS_MAX_DATASET_NAME_LEN];
	int rv = 0;
	nvlist_t *existing_holds;

	if (snprintf(name, sizeof (name), "%s@%s", zhp->zfs_name,
	    ha->snapname) >= sizeof (name)) {
		ha->error = EINVAL;
		rv = EINVAL;
	}

	if (lzc_get_holds(name, &existing_holds) != 0) {
		ha->error = ENOENT;
	} else if (!nvlist_exists(existing_holds, ha->tag)) {
		ha->error = ESRCH;
	} else {
		nvlist_t *torelease = fnvlist_alloc();
		fnvlist_add_boolean(torelease, ha->tag);
		fnvlist_add_nvlist(ha->nvl, name, torelease);
		fnvlist_free(torelease);
	}

	if (ha->recursive)
		rv = zfs_iter_filesystems(zhp, zfs_release_one, ha);
	zfs_close(zhp);
	return (rv);
}