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
struct holdarg {char* snapname; scalar_t__ recursive; int /*<<< orphan*/  tag; int /*<<< orphan*/  nvl; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int EINVAL ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lzc_exists (char*) ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 int zfs_iter_filesystems (TYPE_1__*,int (*) (TYPE_1__*,void*),struct holdarg*) ; 

__attribute__((used)) static int
zfs_hold_one(zfs_handle_t *zhp, void *arg)
{
	struct holdarg *ha = arg;
	char name[ZFS_MAX_DATASET_NAME_LEN];
	int rv = 0;

	if (snprintf(name, sizeof (name), "%s@%s", zhp->zfs_name,
	    ha->snapname) >= sizeof (name))
		return (EINVAL);

	if (lzc_exists(name))
		fnvlist_add_string(ha->nvl, name, ha->tag);

	if (ha->recursive)
		rv = zfs_iter_filesystems(zhp, zfs_hold_one, ha);
	zfs_close(zhp);
	return (rv);
}