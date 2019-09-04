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
typedef  int /*<<< orphan*/  blk64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_FUDGE_BLOCK_BITMAP_END ; 
 int /*<<< orphan*/  ext2fs_fudge_generic_bmap_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

errcode_t ext2fs_fudge_block_bitmap_end2(ext2fs_block_bitmap bitmap,
					 blk64_t end, blk64_t *oend)
{
	return (ext2fs_fudge_generic_bmap_end(bitmap,
					      EXT2_ET_FUDGE_BLOCK_BITMAP_END,
					      end, oend));
}