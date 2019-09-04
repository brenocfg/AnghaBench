#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct ext2_super_block {scalar_t__ s_blocks_per_group; scalar_t__ s_inodes_per_group; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  scalar_t__ dgrp_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_14__ {scalar_t__ group_desc_count; int /*<<< orphan*/  inode_map; struct ext2_super_block* super; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_BG_BLOCK_UNINIT ; 
 int /*<<< orphan*/  EXT2_BG_INODE_UNINIT ; 
 int /*<<< orphan*/  EXT2_ET_NO_INODE_BITMAP ; 
 scalar_t__ ext2fs_bg_checksum (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ext2fs_bg_flags (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_bg_flags_clear (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_bg_flags_set (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_bg_free_blocks_count (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ext2fs_bg_free_inodes_count (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ext2fs_bg_itable_unused (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_bg_itable_unused_set (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  ext2fs_group_desc_csum_set (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_has_group_desc_csum (TYPE_1__*) ; 
 int /*<<< orphan*/  ext2fs_mark_super_dirty (TYPE_1__*) ; 
 int find_last_inode_ingrp (int /*<<< orphan*/ ,int,scalar_t__) ; 

errcode_t ext2fs_set_gdt_csum(ext2_filsys fs)
{
	struct ext2_super_block *sb = fs->super;
	int dirty = 0;
	dgrp_t i;

	if (!fs->inode_map)
		return EXT2_ET_NO_INODE_BITMAP;

	if (!ext2fs_has_group_desc_csum(fs))
		return 0;

	for (i = 0; i < fs->group_desc_count; i++) {
		__u32 old_csum = ext2fs_bg_checksum(fs, i);
		__u32 old_unused = ext2fs_bg_itable_unused(fs, i);
		__u32 old_flags = ext2fs_bg_flags(fs, i);
		__u32 old_free_inodes_count = ext2fs_bg_free_inodes_count(fs, i);
		__u32 old_free_blocks_count = ext2fs_bg_free_blocks_count(fs, i);

		if (old_free_blocks_count == sb->s_blocks_per_group &&
		    i != fs->group_desc_count - 1)
			ext2fs_bg_flags_set(fs, i, EXT2_BG_BLOCK_UNINIT);

		if (old_free_inodes_count == sb->s_inodes_per_group) {
			ext2fs_bg_flags_set(fs, i, EXT2_BG_INODE_UNINIT);
			ext2fs_bg_itable_unused_set(fs, i, sb->s_inodes_per_group);
		} else {
			int unused =
				sb->s_inodes_per_group -
				find_last_inode_ingrp(fs->inode_map,
						      sb->s_inodes_per_group, i);

			ext2fs_bg_flags_clear(fs, i, EXT2_BG_INODE_UNINIT);
			ext2fs_bg_itable_unused_set(fs, i, unused);
		}

		ext2fs_group_desc_csum_set(fs, i);
		if (old_flags != ext2fs_bg_flags(fs, i))
			dirty = 1;
		if (old_unused != ext2fs_bg_itable_unused(fs, i))
			dirty = 1;
		if (old_csum != ext2fs_bg_checksum(fs, i))
			dirty = 1;
	}
	if (dirty)
		ext2fs_mark_super_dirty(fs);
	return 0;
}