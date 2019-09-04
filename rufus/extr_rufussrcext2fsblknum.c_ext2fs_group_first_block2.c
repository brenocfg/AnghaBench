#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  dgrp_t ;
typedef  scalar_t__ blk64_t ;
struct TYPE_5__ {scalar_t__ s_first_data_block; } ;
struct TYPE_4__ {TYPE_3__* super; } ;

/* Variables and functions */
 scalar_t__ EXT2_GROUPS_TO_BLOCKS (TYPE_3__*,int /*<<< orphan*/ ) ; 

blk64_t ext2fs_group_first_block2(ext2_filsys fs, dgrp_t group)
{
	return fs->super->s_first_data_block +
		EXT2_GROUPS_TO_BLOCKS(fs->super, group);
}