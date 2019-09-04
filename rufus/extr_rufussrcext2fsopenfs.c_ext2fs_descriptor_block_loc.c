#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  int /*<<< orphan*/  dgrp_t ;
typedef  int /*<<< orphan*/  blk_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_descriptor_block_loc2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

blk_t ext2fs_descriptor_block_loc(ext2_filsys fs, blk_t group_block, dgrp_t i)
{
	return ext2fs_descriptor_block_loc2(fs, group_block, i);
}