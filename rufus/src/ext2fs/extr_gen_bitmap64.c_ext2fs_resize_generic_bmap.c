#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ext2fs_generic_bitmap_64 ;
typedef  TYPE_3__* ext2fs_generic_bitmap ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_12__ {int /*<<< orphan*/  magic; } ;
struct TYPE_11__ {TYPE_1__* bitmap_ops; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* resize_bmap ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ EXT2FS_IS_32_BITMAP (TYPE_2__*) ; 
 int /*<<< orphan*/  EXT2FS_IS_64_BITMAP (TYPE_2__*) ; 
 int /*<<< orphan*/  INC_STAT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_resize_generic_bitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  resize_count ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errcode_t ext2fs_resize_generic_bmap(ext2fs_generic_bitmap gen_bmap,
				     __u64 new_end,
				     __u64 new_real_end)
{
	ext2fs_generic_bitmap_64 bmap = (ext2fs_generic_bitmap_64) gen_bmap;

	if (!bmap)
		return EINVAL;

	if (EXT2FS_IS_32_BITMAP(bmap))
		return ext2fs_resize_generic_bitmap(gen_bmap->magic, new_end,
						    new_real_end, gen_bmap);

	if (!EXT2FS_IS_64_BITMAP(bmap))
		return EINVAL;

	INC_STAT(bmap, resize_count);

	return bmap->bitmap_ops->resize_bmap(bmap, new_end, new_real_end);
}