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
struct ext4_group_desc {int /*<<< orphan*/  bg_flags; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  dgrp_t ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_4__ {int /*<<< orphan*/  group_desc; } ;

/* Variables and functions */
 struct ext4_group_desc* ext4fs_group_desc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ext2fs_bg_flags_clear(ext2_filsys fs, dgrp_t group, __u16 bg_flags)
{
	struct ext4_group_desc *gdp;

	gdp = ext4fs_group_desc(fs, fs->group_desc, group);
	gdp->bg_flags &= ~bg_flags;
	return;
}