#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ext2fs_generic_bitmap_64 ;
typedef  int /*<<< orphan*/  ext2fs_generic_bitmap ;
struct TYPE_6__ {TYPE_1__* bitmap_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* clear_bmap ) (TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ EXT2FS_IS_32_BITMAP (TYPE_2__*) ; 
 int /*<<< orphan*/  ext2fs_clear_generic_bitmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void ext2fs_clear_generic_bmap(ext2fs_generic_bitmap gen_bitmap)
{
	ext2fs_generic_bitmap_64 bitmap = (ext2fs_generic_bitmap_64) gen_bitmap;

	if (EXT2FS_IS_32_BITMAP(bitmap))
		ext2fs_clear_generic_bitmap(gen_bitmap);
	else
		bitmap->bitmap_ops->clear_bmap(bitmap);
}