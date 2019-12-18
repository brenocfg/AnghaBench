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

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_NEQ_BLOCK_BITMAP ; 
 int /*<<< orphan*/  ext2fs_compare_generic_bmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errcode_t ext2fs_compare_block_bitmap(ext2fs_block_bitmap bm1,
				      ext2fs_block_bitmap bm2)
{
	return (ext2fs_compare_generic_bmap(EXT2_ET_NEQ_BLOCK_BITMAP,
					    bm1, bm2));
}