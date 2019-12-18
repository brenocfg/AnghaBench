#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ext2fs_inode_bitmap ;
typedef  scalar_t__ ext2_ino_t ;
typedef  TYPE_2__* ext2_filsys ;
typedef  scalar_t__ dgrp_t ;
struct TYPE_11__ {scalar_t__ group_desc_count; TYPE_1__* super; } ;
struct TYPE_10__ {scalar_t__ s_inodes_per_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_BG_BLOCK_UNINIT ; 
 int /*<<< orphan*/  EXT2_BG_INODE_UNINIT ; 
 int /*<<< orphan*/  ext2fs_bg_flags_clear (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_bg_flags_test (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_fast_unmark_inode_bitmap2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_group_desc_csum_set (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_has_group_desc_csum (TYPE_2__*) ; 
 int /*<<< orphan*/  ext2fs_mark_ib_dirty (TYPE_2__*) ; 
 int /*<<< orphan*/  ext2fs_mark_super_dirty (TYPE_2__*) ; 

__attribute__((used)) static void check_inode_uninit(ext2_filsys fs, ext2fs_inode_bitmap map,
			  dgrp_t group)
{
	ext2_ino_t	i, ino;

	if (group >= fs->group_desc_count ||
	    !ext2fs_has_group_desc_csum(fs) ||
	    !(ext2fs_bg_flags_test(fs, group, EXT2_BG_INODE_UNINIT)))
		return;

	ino = (group * fs->super->s_inodes_per_group) + 1;
	for (i=0; i < fs->super->s_inodes_per_group; i++, ino++)
		ext2fs_fast_unmark_inode_bitmap2(map, ino);

	ext2fs_bg_flags_clear(fs, group, EXT2_BG_INODE_UNINIT);
	/* Mimics what the kernel does */
	ext2fs_bg_flags_clear(fs, group, EXT2_BG_BLOCK_UNINIT);
	ext2fs_group_desc_csum_set(fs, group);
	ext2fs_mark_ib_dirty(fs);
	ext2fs_mark_super_dirty(fs);
}