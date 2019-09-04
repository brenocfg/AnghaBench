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
struct ext4_xattr_ref {int /*<<< orphan*/  dirty; scalar_t__ block_loaded; TYPE_1__* fs; } ;
struct TYPE_2__ {int InodeSize; } ;

/* Variables and functions */
 int EXT4_GOOD_OLD_INODE_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int ext4_xattr_block_fetch (struct ext4_xattr_ref*) ; 
 int ext4_xattr_inode_fetch (struct ext4_xattr_ref*) ; 

__attribute__((used)) static int ext4_xattr_fetch(struct ext4_xattr_ref *xattr_ref)
{
	int ret = 0;
	int inode_size = xattr_ref->fs->InodeSize;
	if (inode_size > EXT4_GOOD_OLD_INODE_SIZE) {
		ret = ext4_xattr_inode_fetch(xattr_ref);
		if (ret != 0)
			return ret;
	}

	if (xattr_ref->block_loaded)
		ret = ext4_xattr_block_fetch(xattr_ref);

	xattr_ref->dirty = FALSE;
	return ret;
}