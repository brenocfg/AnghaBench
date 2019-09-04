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
struct ext2_inode {scalar_t__ i_blocks; int i_size; scalar_t__* i_block; int i_flags; int /*<<< orphan*/  i_mode; } ;
typedef  int /*<<< orphan*/  ext2_filsys ;

/* Variables and functions */
 int EXT2_N_BLOCKS ; 
 int EXT4_INLINE_DATA_FL ; 
 int /*<<< orphan*/  LINUX_S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ LINUX_S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINUX_S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_file_acl_block (int /*<<< orphan*/ ,struct ext2_inode*) ; 

int ext2fs_inode_has_valid_blocks2(ext2_filsys fs, struct ext2_inode *inode)
{
	/*
	 * Only directories, regular files, and some symbolic links
	 * have valid block entries.
	 */
	if (!LINUX_S_ISDIR(inode->i_mode) && !LINUX_S_ISREG(inode->i_mode) &&
	    !LINUX_S_ISLNK(inode->i_mode))
		return 0;

	/*
	 * If the symbolic link is a "fast symlink", then the symlink
	 * target is stored in the block entries.
	 */
	if (LINUX_S_ISLNK (inode->i_mode)) {
		if (ext2fs_file_acl_block(fs, inode) == 0) {
			/* With no EA block, we can rely on i_blocks */
			if (inode->i_blocks == 0)
				return 0;
		} else {
			/* With an EA block, life gets more tricky */
			if (inode->i_size >= EXT2_N_BLOCKS*4)
				return 1; /* definitely using i_block[] */
			if (inode->i_size > 4 && inode->i_block[1] == 0)
				return 1; /* definitely using i_block[] */
			return 0; /* Probably a fast symlink */
		}
	}

	/*
	 * If this inode has inline data, it shouldn't have valid block
	 * entries.
	 */
	if (inode->i_flags & EXT4_INLINE_DATA_FL)
		return 0;
	return 1;
}