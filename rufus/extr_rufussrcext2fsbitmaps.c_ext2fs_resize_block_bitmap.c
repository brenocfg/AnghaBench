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
typedef  int /*<<< orphan*/  errcode_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_MAGIC_BLOCK_BITMAP ; 
 int /*<<< orphan*/  ext2fs_resize_generic_bitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errcode_t ext2fs_resize_block_bitmap(__u32 new_end, __u32 new_real_end,
				     ext2fs_block_bitmap bmap)
{
	return (ext2fs_resize_generic_bitmap(EXT2_ET_MAGIC_BLOCK_BITMAP,
					     new_end, new_real_end, bmap));
}