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
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ blk_t ;
typedef  scalar_t__ blk64_t ;

/* Variables and functions */
 scalar_t__ ext2fs_zero_blocks2 (int /*<<< orphan*/ ,scalar_t__,int,scalar_t__*,int*) ; 

errcode_t ext2fs_zero_blocks(ext2_filsys fs, blk_t blk, int num,
			     blk_t *ret_blk, int *ret_count)
{
	blk64_t ret_blk2;
	errcode_t retval;

	retval = ext2fs_zero_blocks2(fs, blk, num, &ret_blk2, ret_count);
	if (retval)
		*ret_blk = (blk_t) ret_blk2;
	return retval;
}