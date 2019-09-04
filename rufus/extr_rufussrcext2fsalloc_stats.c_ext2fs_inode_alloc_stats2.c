#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ext2_ino_t ;
typedef  TYPE_2__* ext2_filsys ;
struct TYPE_17__ {TYPE_1__* super; int /*<<< orphan*/  inode_map; } ;
struct TYPE_16__ {scalar_t__ s_inodes_count; int s_inodes_per_group; int s_free_inodes_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_BG_INODE_UNINIT ; 
 int /*<<< orphan*/  com_err (char*,int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  ext2fs_bg_flags_clear (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_bg_free_inodes_count (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ext2fs_bg_free_inodes_count_set (TYPE_2__*,int,scalar_t__) ; 
 scalar_t__ ext2fs_bg_itable_unused (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ext2fs_bg_itable_unused_set (TYPE_2__*,int,scalar_t__) ; 
 scalar_t__ ext2fs_bg_used_dirs_count (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ext2fs_bg_used_dirs_count_set (TYPE_2__*,int,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_group_desc_csum_set (TYPE_2__*,int) ; 
 int ext2fs_group_of_ino (TYPE_2__*,scalar_t__) ; 
 scalar_t__ ext2fs_has_group_desc_csum (TYPE_2__*) ; 
 int /*<<< orphan*/  ext2fs_mark_ib_dirty (TYPE_2__*) ; 
 int /*<<< orphan*/  ext2fs_mark_inode_bitmap2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_mark_super_dirty (TYPE_2__*) ; 
 int /*<<< orphan*/  ext2fs_unmark_inode_bitmap2 (int /*<<< orphan*/ ,scalar_t__) ; 

void ext2fs_inode_alloc_stats2(ext2_filsys fs, ext2_ino_t ino,
			       int inuse, int isdir)
{
	int	group = ext2fs_group_of_ino(fs, ino);

	if (ino > fs->super->s_inodes_count) {
#ifndef OMIT_COM_ERR
		com_err("ext2fs_inode_alloc_stats2", 0,
			"Illegal inode number: %lu", (unsigned long) ino);
#endif
		return;
	}
	if (inuse > 0)
		ext2fs_mark_inode_bitmap2(fs->inode_map, ino);
	else
		ext2fs_unmark_inode_bitmap2(fs->inode_map, ino);
	ext2fs_bg_free_inodes_count_set(fs, group, ext2fs_bg_free_inodes_count(fs, group) - inuse);
	if (isdir)
		ext2fs_bg_used_dirs_count_set(fs, group, ext2fs_bg_used_dirs_count(fs, group) + inuse);

	/* We don't strictly need to be clearing the uninit flag if inuse < 0
	 * (i.e. freeing inodes) but it also means something is bad. */
	ext2fs_bg_flags_clear(fs, group, EXT2_BG_INODE_UNINIT);
	if (ext2fs_has_group_desc_csum(fs)) {
		ext2_ino_t first_unused_inode =	fs->super->s_inodes_per_group -
			ext2fs_bg_itable_unused(fs, group) +
			group * fs->super->s_inodes_per_group + 1;

		if (ino >= first_unused_inode)
			ext2fs_bg_itable_unused_set(fs, group, group * fs->super->s_inodes_per_group + fs->super->s_inodes_per_group - ino);
		ext2fs_group_desc_csum_set(fs, group);
	}

	fs->super->s_free_inodes_count -= inuse;
	ext2fs_mark_super_dirty(fs);
	ext2fs_mark_ib_dirty(fs);
}