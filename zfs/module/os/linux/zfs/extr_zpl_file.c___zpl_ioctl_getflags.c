#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct inode {int dummy; } ;
struct TYPE_2__ {int z_pflags; } ;

/* Variables and functions */
 int FS_APPEND_FL ; 
 int FS_IMMUTABLE_FL ; 
 int FS_NODUMP_FL ; 
 TYPE_1__* ITOZ (struct inode*) ; 
 int ZFS_APPENDONLY ; 
 int ZFS_FL_USER_VISIBLE ; 
 int ZFS_IMMUTABLE ; 
 int ZFS_NODUMP ; 
 int ZFS_PROJINHERIT ; 
 int ZFS_PROJINHERIT_FL ; 

__attribute__((used)) static uint32_t
__zpl_ioctl_getflags(struct inode *ip)
{
	uint64_t zfs_flags = ITOZ(ip)->z_pflags;
	uint32_t ioctl_flags = 0;

	if (zfs_flags & ZFS_IMMUTABLE)
		ioctl_flags |= FS_IMMUTABLE_FL;

	if (zfs_flags & ZFS_APPENDONLY)
		ioctl_flags |= FS_APPEND_FL;

	if (zfs_flags & ZFS_NODUMP)
		ioctl_flags |= FS_NODUMP_FL;

	if (zfs_flags & ZFS_PROJINHERIT)
		ioctl_flags |= ZFS_PROJINHERIT_FL;

	return (ioctl_flags & ZFS_FL_USER_VISIBLE);
}