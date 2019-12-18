#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ext2fs_block_bitmap ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int dgrp_t ;
typedef  int /*<<< orphan*/  blk64_t ;
struct TYPE_8__ {int s_log_groups_per_flex; int s_blocks_per_group; } ;
struct TYPE_7__ {int group_desc_count; TYPE_6__* super; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_blocks_count (TYPE_6__*) ; 
 scalar_t__ ext2fs_get_free_blocks2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext2fs_group_first_block2 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ext2fs_group_last_block2 (TYPE_1__*,int) ; 

__attribute__((used)) static blk64_t flexbg_offset(ext2_filsys fs, dgrp_t group, blk64_t start_blk,
			     ext2fs_block_bitmap bmap, int rem_grp,
			     int elem_size)
{
	int		flexbg, flexbg_size, size;
	blk64_t		last_blk, first_free = 0;
	dgrp_t	       	last_grp;

	flexbg_size = 1 << fs->super->s_log_groups_per_flex;
	flexbg = group / flexbg_size;
	size = rem_grp * elem_size;

	if (size > (int) (fs->super->s_blocks_per_group / 4))
		size = (int) fs->super->s_blocks_per_group / 4;

	/*
	 * Don't do a long search if the previous block search is still valid,
	 * but skip minor obstructions such as group descriptor backups.
	 */
	if (start_blk && start_blk < ext2fs_blocks_count(fs->super) &&
	    ext2fs_get_free_blocks2(fs, start_blk, start_blk + size, elem_size,
				    bmap, &first_free) == 0)
		return first_free;

	start_blk = ext2fs_group_first_block2(fs, flexbg_size * flexbg);
	last_grp = group | (flexbg_size - 1);
	if (last_grp > fs->group_desc_count-1)
		last_grp = fs->group_desc_count-1;
	last_blk = ext2fs_group_last_block2(fs, last_grp);

	/* Find the first available block */
	if (ext2fs_get_free_blocks2(fs, start_blk, last_blk, size,
				    bmap, &first_free) == 0)
		return first_free;

	if (ext2fs_get_free_blocks2(fs, start_blk, last_blk, elem_size,
				   bmap, &first_free) == 0)
		return first_free;

	if (ext2fs_get_free_blocks2(fs, 0, last_blk, elem_size, bmap,
				    &first_free) == 0)
		return first_free;

	return first_free;
}