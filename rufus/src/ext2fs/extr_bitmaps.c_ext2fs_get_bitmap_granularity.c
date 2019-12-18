#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2fs_generic_bitmap_64 ;
typedef  int /*<<< orphan*/  ext2fs_block_bitmap ;
struct TYPE_3__ {int cluster_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2FS_IS_64_BITMAP (TYPE_1__*) ; 

int ext2fs_get_bitmap_granularity(ext2fs_block_bitmap bitmap)
{
	ext2fs_generic_bitmap_64 bmap = (ext2fs_generic_bitmap_64) bitmap;

	if (!EXT2FS_IS_64_BITMAP(bmap))
		return 0;

	return bmap->cluster_bits;
}