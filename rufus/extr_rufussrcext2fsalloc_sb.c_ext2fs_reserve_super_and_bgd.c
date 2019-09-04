#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ext2fs_block_bitmap ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ dgrp_t ;
typedef  scalar_t__ blk_t ;
typedef  scalar_t__ blk64_t ;
struct TYPE_9__ {int s_first_meta_bg; int s_reserved_gdt_blocks; } ;
struct TYPE_8__ {int desc_blocks; int blocksize; scalar_t__ inode_blocks_per_group; TYPE_4__* super; } ;

/* Variables and functions */
 int EXT2FS_CLUSTER_RATIO (TYPE_1__*) ; 
 scalar_t__ ext2fs_blocks_count (TYPE_4__*) ; 
 int ext2fs_group_blocks_count (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ext2fs_has_feature_meta_bg (TYPE_4__*) ; 
 int /*<<< orphan*/  ext2fs_mark_block_bitmap2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_mark_block_bitmap_range2 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ext2fs_super_and_bgd_loc2 (TYPE_1__*,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

int ext2fs_reserve_super_and_bgd(ext2_filsys fs,
				 dgrp_t group,
				 ext2fs_block_bitmap bmap)
{
	blk64_t	super_blk, old_desc_blk, new_desc_blk;
	blk_t	used_blks;
	int	old_desc_blocks, num_blocks;

	ext2fs_super_and_bgd_loc2(fs, group, &super_blk,
				  &old_desc_blk, &new_desc_blk, &used_blks);

	if (ext2fs_has_feature_meta_bg(fs->super))
		old_desc_blocks = fs->super->s_first_meta_bg;
	else
		old_desc_blocks =
			fs->desc_blocks + fs->super->s_reserved_gdt_blocks;

	if (super_blk || (group == 0))
		ext2fs_mark_block_bitmap2(bmap, super_blk);
	if ((group == 0) && (fs->blocksize == 1024) &&
	    EXT2FS_CLUSTER_RATIO(fs) > 1)
		ext2fs_mark_block_bitmap2(bmap, 0);

	if (old_desc_blk) {
		num_blocks = old_desc_blocks;
		if (old_desc_blk + num_blocks >= ext2fs_blocks_count(fs->super))
			num_blocks = ext2fs_blocks_count(fs->super) -
				old_desc_blk;
		ext2fs_mark_block_bitmap_range2(bmap, old_desc_blk, num_blocks);
	}
	if (new_desc_blk)
		ext2fs_mark_block_bitmap2(bmap, new_desc_blk);

	num_blocks = ext2fs_group_blocks_count(fs, group);
	num_blocks -= 2 + fs->inode_blocks_per_group + used_blks;

	return num_blocks  ;
}