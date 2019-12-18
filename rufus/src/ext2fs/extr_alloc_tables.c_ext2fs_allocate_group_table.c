#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ext2fs_block_bitmap ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  int dgrp_t ;
typedef  int blk64_t ;
struct TYPE_22__ {int s_log_groups_per_flex; } ;
struct TYPE_21__ {int group_desc_count; int stride; int inode_blocks_per_group; TYPE_7__* super; int /*<<< orphan*/  block_map; } ;

/* Variables and functions */
 int EXT2FS_CLUSTER_RATIO (TYPE_1__*) ; 
 int /*<<< orphan*/  EXT2_BG_BLOCK_UNINIT ; 
 scalar_t__ EXT2_ET_BLOCK_ALLOC_FAIL ; 
 int /*<<< orphan*/  ext2fs_bg_flags_clear (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_bg_free_blocks_count (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ext2fs_bg_free_blocks_count_set (TYPE_1__*,int,scalar_t__) ; 
 int ext2fs_block_bitmap_loc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ext2fs_block_bitmap_loc_set (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ext2fs_free_blocks_count_add (TYPE_7__*,int) ; 
 scalar_t__ ext2fs_get_free_blocks2 (TYPE_1__*,int,int,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ext2fs_group_desc_csum_set (TYPE_1__*,int) ; 
 int ext2fs_group_first_block2 (TYPE_1__*,int) ; 
 int ext2fs_group_last_block2 (TYPE_1__*,int) ; 
 int ext2fs_group_of_blk2 (TYPE_1__*,int) ; 
 scalar_t__ ext2fs_has_feature_flex_bg (TYPE_7__*) ; 
 int ext2fs_inode_bitmap_loc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ext2fs_inode_bitmap_loc_set (TYPE_1__*,int,int) ; 
 int ext2fs_inode_table_loc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ext2fs_inode_table_loc_set (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ext2fs_mark_block_bitmap2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext2fs_mark_block_bitmap_range2 (int /*<<< orphan*/ ,int,int) ; 
 int flexbg_offset (TYPE_1__*,int,int,int /*<<< orphan*/ ,int,int) ; 

errcode_t ext2fs_allocate_group_table(ext2_filsys fs, dgrp_t group,
				      ext2fs_block_bitmap bmap)
{
	errcode_t	retval;
	blk64_t		group_blk, start_blk, last_blk, new_blk;
	dgrp_t		last_grp = 0;
	int		rem_grps = 0, flexbg_size = 0, table_offset = 0;

	group_blk = ext2fs_group_first_block2(fs, group);
	last_blk = ext2fs_group_last_block2(fs, group);

	if (!bmap)
		bmap = fs->block_map;

	if (ext2fs_has_feature_flex_bg(fs->super) &&
	    fs->super->s_log_groups_per_flex) {
		flexbg_size = 1 << fs->super->s_log_groups_per_flex;
		last_grp = group | (flexbg_size - 1);
		if (last_grp > fs->group_desc_count-1)
			last_grp = fs->group_desc_count-1;
		rem_grps = last_grp - group + 1;
	}

	/*
	 * Allocate the block and inode bitmaps, if necessary
	 */
	if (fs->stride && !flexbg_size) {
		retval = ext2fs_get_free_blocks2(fs, group_blk, last_blk,
						 1, bmap, &start_blk);
		if (retval)
			return retval;
		start_blk += fs->inode_blocks_per_group;
		start_blk += ((fs->stride * group) %
			      (last_blk - start_blk + 1));
		if (start_blk >= last_blk)
			start_blk = group_blk;
	} else
		start_blk = group_blk;

	if (flexbg_size) {
		blk64_t prev_block = 0;

		table_offset = flexbg_size;
		if (group % flexbg_size)
			prev_block = ext2fs_block_bitmap_loc(fs, group - 1) + 1;
		else if (last_grp == fs->group_desc_count-1) {
			/*
			 * If we are allocating for the last flex_bg
			 * keep the metadata tables contiguous
			 */
			table_offset = last_grp & (flexbg_size - 1);
			if (table_offset == 0)
				table_offset = flexbg_size;
			else
				table_offset++;
		}
		/* FIXME: Take backup group descriptor blocks into account
		 * if the flexbg allocations will grow to overlap them... */
		start_blk = flexbg_offset(fs, group, prev_block, bmap,
					  rem_grps, 1);
		last_blk = ext2fs_group_last_block2(fs, last_grp);
	}

	if (!ext2fs_block_bitmap_loc(fs, group)) {
		retval = ext2fs_get_free_blocks2(fs, start_blk, last_blk,
						 1, bmap, &new_blk);
		if (retval == EXT2_ET_BLOCK_ALLOC_FAIL)
			retval = ext2fs_get_free_blocks2(fs, group_blk,
					last_blk, 1, bmap, &new_blk);
		if (retval)
			return retval;
		ext2fs_mark_block_bitmap2(bmap, new_blk);
		ext2fs_block_bitmap_loc_set(fs, group, new_blk);
		if (flexbg_size) {
			dgrp_t gr = ext2fs_group_of_blk2(fs, new_blk);
			ext2fs_bg_free_blocks_count_set(fs, gr, ext2fs_bg_free_blocks_count(fs, gr) - 1);
			ext2fs_free_blocks_count_add(fs->super, -1);
			ext2fs_bg_flags_clear(fs, gr, EXT2_BG_BLOCK_UNINIT);
			ext2fs_group_desc_csum_set(fs, gr);
		}
	}

	if (flexbg_size) {
		blk64_t prev_block = 0;
		if (group % flexbg_size)
			prev_block = ext2fs_inode_bitmap_loc(fs, group - 1) + 1;
		else
			prev_block = ext2fs_block_bitmap_loc(fs, group) +
				table_offset;
		/* FIXME: Take backup group descriptor blocks into account
		 * if the flexbg allocations will grow to overlap them... */
		start_blk = flexbg_offset(fs, group, prev_block, bmap,
					  rem_grps, 1);
		last_blk = ext2fs_group_last_block2(fs, last_grp);
	}

	if (!ext2fs_inode_bitmap_loc(fs, group)) {
		retval = ext2fs_get_free_blocks2(fs, start_blk, last_blk,
						 1, bmap, &new_blk);
		if (retval == EXT2_ET_BLOCK_ALLOC_FAIL)
			retval = ext2fs_get_free_blocks2(fs, group_blk,
					 last_blk, 1, bmap, &new_blk);
		if (retval)
			return retval;
		ext2fs_mark_block_bitmap2(bmap, new_blk);
		ext2fs_inode_bitmap_loc_set(fs, group, new_blk);
		if (flexbg_size) {
			dgrp_t gr = ext2fs_group_of_blk2(fs, new_blk);
			ext2fs_bg_free_blocks_count_set(fs, gr, ext2fs_bg_free_blocks_count(fs, gr) - 1);
			ext2fs_free_blocks_count_add(fs->super, -1);
			ext2fs_bg_flags_clear(fs, gr, EXT2_BG_BLOCK_UNINIT);
			ext2fs_group_desc_csum_set(fs, gr);
		}
	}

	/*
	 * Allocate the inode table
	 */
	if (flexbg_size) {
		blk64_t prev_block = 0;

		if (group % flexbg_size)
			prev_block = ext2fs_inode_table_loc(fs, group - 1) +
				fs->inode_blocks_per_group;
		else
			prev_block = ext2fs_inode_bitmap_loc(fs, group) +
				table_offset;

		/* FIXME: Take backup group descriptor blocks into account
		 * if the flexbg allocations will grow to overlap them... */
		group_blk = flexbg_offset(fs, group, prev_block, bmap,
					  rem_grps, fs->inode_blocks_per_group);
		last_blk = ext2fs_group_last_block2(fs, last_grp);
	}

	if (!ext2fs_inode_table_loc(fs, group)) {
		retval = ext2fs_get_free_blocks2(fs, group_blk, last_blk,
						fs->inode_blocks_per_group,
						bmap, &new_blk);
		if (retval)
			return retval;

		ext2fs_mark_block_bitmap_range2(bmap,
			new_blk, fs->inode_blocks_per_group);
		if (flexbg_size) {
			blk64_t num, blk;
			num = fs->inode_blocks_per_group;
			blk = new_blk;
			while (num) {
				int gr = ext2fs_group_of_blk2(fs, blk);
				last_blk = ext2fs_group_last_block2(fs, gr);
				blk64_t n = num;

				if (blk + num > last_blk)
					n = last_blk - blk + 1;

				ext2fs_bg_free_blocks_count_set(fs, gr,
					ext2fs_bg_free_blocks_count(fs, gr) -
					n/EXT2FS_CLUSTER_RATIO(fs));
				ext2fs_bg_flags_clear(fs, gr,
					EXT2_BG_BLOCK_UNINIT);
				ext2fs_group_desc_csum_set(fs, gr);
				ext2fs_free_blocks_count_add(fs->super, -n);
				blk += n;
				num -= n;
			}
		}
		ext2fs_inode_table_loc_set(fs, group, new_blk);
	}
	ext2fs_group_desc_csum_set(fs, group);
	return 0;
}