#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_filsys ;
typedef  int dgrp_t ;
typedef  int /*<<< orphan*/  blk64_t ;
struct TYPE_8__ {int s_first_data_block; int s_log_groups_per_flex; } ;
struct TYPE_7__ {int group_desc_count; TYPE_5__* super; } ;

/* Variables and functions */
 scalar_t__ ext2fs_bg_free_blocks_count (TYPE_1__*,int) ; 
 int ext2fs_blocks_count (TYPE_5__*) ; 
 int /*<<< orphan*/  ext2fs_group_first_block2 (TYPE_1__*,int) ; 
 int ext2fs_group_of_blk2 (TYPE_1__*,int) ; 

__attribute__((used)) static blk64_t get_midpoint_journal_block(ext2_filsys fs)
{
	dgrp_t	group, start, end, i, log_flex;

	group = ext2fs_group_of_blk2(fs, (ext2fs_blocks_count(fs->super) -
					 fs->super->s_first_data_block) / 2);
	log_flex = 1 << fs->super->s_log_groups_per_flex;
	if (fs->super->s_log_groups_per_flex && (group > log_flex)) {
		group = group & ~(log_flex - 1);
		while ((group < fs->group_desc_count) &&
		       ext2fs_bg_free_blocks_count(fs, group) == 0)
			group++;
		if (group == fs->group_desc_count)
			group = 0;
		start = group;
	} else
		start = (group > 0) ? group-1 : group;
	end = ((group+1) < fs->group_desc_count) ? group+1 : group;
	group = start;
	for (i = start + 1; i <= end; i++)
		if (ext2fs_bg_free_blocks_count(fs, i) >
		    ext2fs_bg_free_blocks_count(fs, group))
			group = i;
	return ext2fs_group_first_block2(fs, group);
}