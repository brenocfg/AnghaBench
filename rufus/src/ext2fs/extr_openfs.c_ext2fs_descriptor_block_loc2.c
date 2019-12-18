#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_filsys ;
typedef  int dgrp_t ;
typedef  scalar_t__ blk64_t ;
struct TYPE_10__ {int s_first_meta_bg; scalar_t__ s_first_data_block; scalar_t__ s_blocks_per_group; } ;
struct TYPE_9__ {int blocksize; TYPE_2__* super; } ;

/* Variables and functions */
 int EXT2FS_CLUSTER_RATIO (TYPE_1__*) ; 
 int EXT2_DESC_PER_BLOCK (TYPE_2__*) ; 
 scalar_t__ ext2fs_bg_has_super (TYPE_1__*,int) ; 
 scalar_t__ ext2fs_blocks_count (TYPE_2__*) ; 
 scalar_t__ ext2fs_group_first_block2 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ext2fs_has_feature_meta_bg (TYPE_2__*) ; 

blk64_t ext2fs_descriptor_block_loc2(ext2_filsys fs, blk64_t group_block,
				     dgrp_t i)
{
	int	bg;
	int	has_super = 0, group_zero_adjust = 0;
	blk64_t	ret_blk;

	/*
	 * On a bigalloc FS with 1K blocks, block 0 is reserved for non-ext4
	 * stuff, so adjust for that if we're being asked for group 0.
	 */
	if (i == 0 && fs->blocksize == 1024 && EXT2FS_CLUSTER_RATIO(fs) > 1)
		group_zero_adjust = 1;

	if (!ext2fs_has_feature_meta_bg(fs->super) ||
	    (i < fs->super->s_first_meta_bg))
		return group_block + i + 1 + group_zero_adjust;

	bg = EXT2_DESC_PER_BLOCK(fs->super) * i;
	if (ext2fs_bg_has_super(fs, bg))
		has_super = 1;
	ret_blk = ext2fs_group_first_block2(fs, bg);
	/*
	 * If group_block is not the normal value, we're trying to use
	 * the backup group descriptors and superblock --- so use the
	 * alternate location of the second block group in the
	 * metablock group.  Ideally we should be testing each bg
	 * descriptor block individually for correctness, but we don't
	 * have the infrastructure in place to do that.
	 */
	if (group_block != fs->super->s_first_data_block &&
	    ((ret_blk + has_super + fs->super->s_blocks_per_group) <
	     ext2fs_blocks_count(fs->super))) {
		ret_blk += fs->super->s_blocks_per_group;

		/*
		 * If we're going to jump forward a block group, make sure
		 * that we adjust has_super to account for the next group's
		 * backup superblock (or lack thereof).
		 */
		if (ext2fs_bg_has_super(fs, bg + 1))
			has_super = 1;
		else
			has_super = 0;
	}
	return ret_blk + has_super + group_zero_adjust;
}