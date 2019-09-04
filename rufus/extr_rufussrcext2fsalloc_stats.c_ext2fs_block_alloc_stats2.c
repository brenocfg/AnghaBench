#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ blk64_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* block_alloc_stats ) (TYPE_1__*,scalar_t__,int) ;int /*<<< orphan*/  super; int /*<<< orphan*/  block_map; } ;

/* Variables and functions */
 scalar_t__ EXT2FS_CLUSTER_RATIO (TYPE_1__*) ; 
 int /*<<< orphan*/  EXT2_BG_BLOCK_UNINIT ; 
 int /*<<< orphan*/  com_err (char*,int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  ext2fs_bg_flags_clear (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_bg_free_blocks_count (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ext2fs_bg_free_blocks_count_set (TYPE_1__*,int,scalar_t__) ; 
 scalar_t__ ext2fs_blocks_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_free_blocks_count_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext2fs_group_desc_csum_set (TYPE_1__*,int) ; 
 int ext2fs_group_of_blk2 (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_mark_bb_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  ext2fs_mark_block_bitmap2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_mark_super_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  ext2fs_unmark_block_bitmap2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__,int) ; 

void ext2fs_block_alloc_stats2(ext2_filsys fs, blk64_t blk, int inuse)
{
	int	group = ext2fs_group_of_blk2(fs, blk);

	if (blk >= ext2fs_blocks_count(fs->super)) {
#ifndef OMIT_COM_ERR
		com_err("ext2fs_block_alloc_stats", 0,
			"Illegal block number: %lu", (unsigned long) blk);
#endif
		return;
	}
	if (inuse > 0)
		ext2fs_mark_block_bitmap2(fs->block_map, blk);
	else
		ext2fs_unmark_block_bitmap2(fs->block_map, blk);
	ext2fs_bg_free_blocks_count_set(fs, group, ext2fs_bg_free_blocks_count(fs, group) - inuse);
	ext2fs_bg_flags_clear(fs, group, EXT2_BG_BLOCK_UNINIT);
	ext2fs_group_desc_csum_set(fs, group);

	ext2fs_free_blocks_count_add(fs->super,
			     -inuse * (blk64_t) EXT2FS_CLUSTER_RATIO(fs));
	ext2fs_mark_super_dirty(fs);
	ext2fs_mark_bb_dirty(fs);
	if (fs->block_alloc_stats)
		(fs->block_alloc_stats)(fs, (blk64_t) blk, inuse);
}