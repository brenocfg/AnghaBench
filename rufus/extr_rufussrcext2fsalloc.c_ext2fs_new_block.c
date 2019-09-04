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
typedef  int /*<<< orphan*/  ext2fs_block_bitmap ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  scalar_t__ blk_t ;
typedef  scalar_t__ blk64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_new_block2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 

errcode_t ext2fs_new_block(ext2_filsys fs, blk_t goal,
			   ext2fs_block_bitmap map, blk_t *ret)
{
	errcode_t retval;
	blk64_t val;
	retval = ext2fs_new_block2(fs, goal, map, &val);
	if (!retval)
		*ret = (blk_t) val;
	return retval;
}