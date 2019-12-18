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

/* Variables and functions */
 int /*<<< orphan*/  nfs_only ; 
 int /*<<< orphan*/  share_all_proto ; 
 int /*<<< orphan*/  smb_only ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int zfs_unshare_proto (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

int
zfs_unshareall_bytype(zfs_handle_t *zhp, const char *mountpoint,
    const char *proto)
{
	if (proto == NULL)
		return (zfs_unshare_proto(zhp, mountpoint, share_all_proto));
	if (strcmp(proto, "nfs") == 0)
		return (zfs_unshare_proto(zhp, mountpoint, nfs_only));
	else if (strcmp(proto, "smb") == 0)
		return (zfs_unshare_proto(zhp, mountpoint, smb_only));
	else
		return (1);
}