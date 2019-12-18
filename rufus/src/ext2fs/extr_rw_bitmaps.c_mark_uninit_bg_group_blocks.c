#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ext2fs_block_bitmap ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  scalar_t__ dgrp_t ;
typedef  scalar_t__ blk64_t ;
struct TYPE_8__ {scalar_t__ group_desc_count; int /*<<< orphan*/  inode_blocks_per_group; int /*<<< orphan*/  block_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_BG_BLOCK_UNINIT ; 
 int /*<<< orphan*/  ext2fs_bg_flags_test (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_block_bitmap_loc (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ext2fs_inode_bitmap_loc (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ext2fs_inode_table_loc (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_mark_block_bitmap2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_mark_block_bitmap_range2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_reserve_super_and_bgd (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static errcode_t mark_uninit_bg_group_blocks(ext2_filsys fs)
{
	dgrp_t			i;
	blk64_t			blk;
	ext2fs_block_bitmap	bmap = fs->block_map;

	for (i = 0; i < fs->group_desc_count; i++) {
		if (!ext2fs_bg_flags_test(fs, i, EXT2_BG_BLOCK_UNINIT))
			continue;

		ext2fs_reserve_super_and_bgd(fs, i, bmap);

		/*
		 * Mark the blocks used for the inode table
		 */
		blk = ext2fs_inode_table_loc(fs, i);
		if (blk)
			ext2fs_mark_block_bitmap_range2(bmap, blk,
						fs->inode_blocks_per_group);

		/*
		 * Mark block used for the block bitmap
		 */
		blk = ext2fs_block_bitmap_loc(fs, i);
		if (blk)
			ext2fs_mark_block_bitmap2(bmap, blk);

		/*
		 * Mark block used for the inode bitmap
		 */
		blk = ext2fs_inode_bitmap_loc(fs, i);
		if (blk)
			ext2fs_mark_block_bitmap2(bmap, blk);
	}
	return 0;
}