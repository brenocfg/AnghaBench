#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ext2fs_generic_bitmap_64 ;
typedef  int /*<<< orphan*/  ext2fs_generic_bitmap ;
typedef  int __u64 ;
struct TYPE_9__ {int cluster_bits; int start; int end; TYPE_1__* bitmap_ops; } ;
struct TYPE_8__ {int (* unmark_bmap ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 scalar_t__ EXT2FS_IS_32_BITMAP (TYPE_2__*) ; 
 int /*<<< orphan*/  EXT2FS_IS_64_BITMAP (TYPE_2__*) ; 
 int /*<<< orphan*/  EXT2FS_UNMARK_ERROR ; 
 int /*<<< orphan*/  INC_STAT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ext2fs_unmark_generic_bitmap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext2fs_warn_bitmap2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  unmark_count ; 
 int /*<<< orphan*/  warn_bitmap (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int ext2fs_unmark_generic_bmap(ext2fs_generic_bitmap gen_bitmap,
			       __u64 arg)
{
	ext2fs_generic_bitmap_64 bitmap = (ext2fs_generic_bitmap_64) gen_bitmap;

	if (!bitmap)
		return 0;

	if (EXT2FS_IS_32_BITMAP(bitmap)) {
		if (arg & ~0xffffffffULL) {
			ext2fs_warn_bitmap2(gen_bitmap, EXT2FS_UNMARK_ERROR,
					    0xffffffff);
			return 0;
		}
		return ext2fs_unmark_generic_bitmap(gen_bitmap, arg);
	}

	if (!EXT2FS_IS_64_BITMAP(bitmap))
		return 0;

	arg >>= bitmap->cluster_bits;

	INC_STAT(bitmap, unmark_count);

	if ((arg < bitmap->start) || (arg > bitmap->end)) {
		warn_bitmap(bitmap, EXT2FS_UNMARK_ERROR, arg);
		return 0;
	}

	return bitmap->bitmap_ops->unmark_bmap(bitmap, arg);
}