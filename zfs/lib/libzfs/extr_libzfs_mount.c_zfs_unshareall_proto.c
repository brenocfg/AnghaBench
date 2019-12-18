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
typedef  int /*<<< orphan*/  zfs_share_proto_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  prop_changelist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_PROP_SHARENFS ; 
 int /*<<< orphan*/  changelist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * changelist_gather (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int changelist_unshare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
zfs_unshareall_proto(zfs_handle_t *zhp, zfs_share_proto_t *proto)
{
	prop_changelist_t *clp;
	int ret;

	clp = changelist_gather(zhp, ZFS_PROP_SHARENFS, 0, 0);
	if (clp == NULL)
		return (-1);

	ret = changelist_unshare(clp, proto);
	changelist_free(clp);

	return (ret);
}