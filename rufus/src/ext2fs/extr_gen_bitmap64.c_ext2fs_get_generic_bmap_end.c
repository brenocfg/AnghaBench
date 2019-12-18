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
typedef  TYPE_1__* ext2fs_generic_bitmap_64 ;
typedef  int /*<<< orphan*/  ext2fs_generic_bitmap ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_4__ {int /*<<< orphan*/  end; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ EXT2FS_IS_32_BITMAP (TYPE_1__*) ; 
 int /*<<< orphan*/  EXT2FS_IS_64_BITMAP (TYPE_1__*) ; 
 int /*<<< orphan*/  ext2fs_get_generic_bitmap_end (int /*<<< orphan*/ ) ; 

__u64 ext2fs_get_generic_bmap_end(ext2fs_generic_bitmap gen_bitmap)
{
	ext2fs_generic_bitmap_64 bitmap = (ext2fs_generic_bitmap_64) gen_bitmap;

	if (!bitmap)
		return EINVAL;

	if (EXT2FS_IS_32_BITMAP(bitmap))
		return ext2fs_get_generic_bitmap_end(gen_bitmap);

	if (!EXT2FS_IS_64_BITMAP(bitmap))
		return EINVAL;

	return bitmap->end;
}