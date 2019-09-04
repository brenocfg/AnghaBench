#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ dgrp_t ;
struct TYPE_9__ {scalar_t__ group_desc_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_BG_BLOCK_UNINIT ; 
 int /*<<< orphan*/  ext2fs_bg_flags_clear (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_bg_flags_test (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_group_desc_csum_set (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_has_group_desc_csum (TYPE_1__*) ; 
 int /*<<< orphan*/  ext2fs_mark_bb_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  ext2fs_mark_super_dirty (TYPE_1__*) ; 

void ext2fs_clear_block_uninit(ext2_filsys fs, dgrp_t group)
{
	if (group >= fs->group_desc_count ||
	    !ext2fs_has_group_desc_csum(fs) ||
	    !(ext2fs_bg_flags_test(fs, group, EXT2_BG_BLOCK_UNINIT)))
		return;

	/* uninit block bitmaps are now initialized in read_bitmaps() */

	ext2fs_bg_flags_clear(fs, group, EXT2_BG_BLOCK_UNINIT);
	ext2fs_group_desc_csum_set(fs, group);
	ext2fs_mark_super_dirty(fs);
	ext2fs_mark_bb_dirty(fs);
}