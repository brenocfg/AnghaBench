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
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  parent ;
typedef  int /*<<< orphan*/  child ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int ZFS_MAXPROPLEN ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int /*<<< orphan*/  libzfs_path_contains (char*,char*) ; 
 int /*<<< orphan*/  verify (int) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
non_descendant_idx(zfs_handle_t **handles, size_t num_handles, int idx)
{
	char parent[ZFS_MAXPROPLEN];
	char child[ZFS_MAXPROPLEN];
	int i;

	verify(zfs_prop_get(handles[idx], ZFS_PROP_MOUNTPOINT, parent,
	    sizeof (parent), NULL, NULL, 0, B_FALSE) == 0);

	for (i = idx + 1; i < num_handles; i++) {
		verify(zfs_prop_get(handles[i], ZFS_PROP_MOUNTPOINT, child,
		    sizeof (child), NULL, NULL, 0, B_FALSE) == 0);
		if (!libzfs_path_contains(parent, child))
			break;
	}
	return (i);
}