#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ext4_group_desc {int bg_used_dirs_count; int bg_used_dirs_count_hi; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  dgrp_t ;
typedef  int __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  super; int /*<<< orphan*/  group_desc; } ;

/* Variables and functions */
 scalar_t__ ext2fs_has_feature_64bit (int /*<<< orphan*/ ) ; 
 struct ext4_group_desc* ext4fs_group_desc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ext2fs_bg_used_dirs_count_set(ext2_filsys fs, dgrp_t group, __u32 n)
{
	struct ext4_group_desc *gdp;

	gdp = ext4fs_group_desc(fs, fs->group_desc, group);
	gdp->bg_used_dirs_count = n;
	if (ext2fs_has_feature_64bit(fs->super))
		gdp->bg_used_dirs_count_hi = (__u32) n >> 16;
}