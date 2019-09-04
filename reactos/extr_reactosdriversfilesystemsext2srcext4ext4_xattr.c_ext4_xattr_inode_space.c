#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ext4_xattr_ref {TYPE_2__* OnDiskInode; TYPE_1__* fs; } ;
typedef  int __s32 ;
struct TYPE_4__ {int i_extra_isize; } ;
struct TYPE_3__ {int InodeSize; } ;

/* Variables and functions */
 int EXT4_GOOD_OLD_INODE_SIZE ; 

__attribute__((used)) static __s32 ext4_xattr_inode_space(struct ext4_xattr_ref *xattr_ref)
{
	int inode_size = xattr_ref->fs->InodeSize;
	int size_rem = inode_size - EXT4_GOOD_OLD_INODE_SIZE -
			    xattr_ref->OnDiskInode->i_extra_isize;
	return size_rem;
}