#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ext2_ino_t ;
typedef  TYPE_2__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  scalar_t__ dgrp_t ;
struct TYPE_7__ {scalar_t__ group_desc_count; TYPE_1__* super; } ;
struct TYPE_6__ {int s_inodes_per_group; int s_inodes_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2FS_FILSYS ; 
 int ext2fs_bg_used_dirs_count (TYPE_2__*,scalar_t__) ; 

errcode_t ext2fs_get_num_dirs(ext2_filsys fs, ext2_ino_t *ret_num_dirs)
{
	dgrp_t	i;
	ext2_ino_t	num_dirs, max_dirs;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	num_dirs = 0;
	max_dirs = fs->super->s_inodes_per_group;
	for (i = 0; i < fs->group_desc_count; i++) {
		if (ext2fs_bg_used_dirs_count(fs, i) > max_dirs)
			num_dirs += max_dirs / 8;
		else
			num_dirs += ext2fs_bg_used_dirs_count(fs, i);
	}
	if (num_dirs > fs->super->s_inodes_count)
		num_dirs = fs->super->s_inodes_count;

	*ret_num_dirs = num_dirs;

	return 0;
}