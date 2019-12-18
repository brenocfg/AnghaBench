#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_filsys ;
typedef  unsigned int dgrp_t ;
typedef  int blk_t ;
typedef  scalar_t__ blk64_t ;
struct TYPE_5__ {int inode_blocks_per_group; int /*<<< orphan*/  super; } ;

/* Variables and functions */
 unsigned int EXT2_DESC_PER_BLOCK (int /*<<< orphan*/ ) ; 
 int ext2fs_group_blocks_count (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  ext2fs_super_and_bgd_loc2 (TYPE_1__*,unsigned int,scalar_t__*,scalar_t__*,scalar_t__*,int*) ; 

int ext2fs_super_and_bgd_loc(ext2_filsys fs,
			     dgrp_t group,
			     blk_t *ret_super_blk,
			     blk_t *ret_old_desc_blk,
			     blk_t *ret_new_desc_blk,
			     int *ret_meta_bg)
{
	blk64_t ret_super_blk2;
	blk64_t ret_old_desc_blk2;
	blk64_t ret_new_desc_blk2;
	blk_t ret_used_blks;
	blk_t numblocks;
	unsigned int meta_bg_size;

	ext2fs_super_and_bgd_loc2(fs, group, &ret_super_blk2,
					&ret_old_desc_blk2,
					&ret_new_desc_blk2,
					&ret_used_blks);

	numblocks = ext2fs_group_blocks_count(fs, group);

	if (ret_super_blk)
		*ret_super_blk = (blk_t)ret_super_blk2;
	if (ret_old_desc_blk)
		*ret_old_desc_blk = (blk_t)ret_old_desc_blk2;
	if (ret_new_desc_blk)
		*ret_new_desc_blk = (blk_t)ret_new_desc_blk2;
	if (ret_meta_bg) {
		meta_bg_size = EXT2_DESC_PER_BLOCK(fs->super);
		*ret_meta_bg = group / meta_bg_size;
	}

	numblocks -= 2 + fs->inode_blocks_per_group + ret_used_blks;

	return numblocks;
}