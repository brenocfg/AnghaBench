#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ext2fs_generic_bitmap_64 ;
typedef  int /*<<< orphan*/  ext2fs_generic_bitmap ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_8__ {TYPE_1__* bitmap_ops; int /*<<< orphan*/  magic; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_bmap_range ) (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ EXT2FS_IS_32_BITMAP (TYPE_2__*) ; 
 int /*<<< orphan*/  EXT2FS_IS_64_BITMAP (TYPE_2__*) ; 
 int /*<<< orphan*/  EXT2FS_UNMARK_ERROR ; 
 int /*<<< orphan*/  INC_STAT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_get_generic_bitmap_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,void*) ; 
 int /*<<< orphan*/  ext2fs_warn_bitmap2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_range_count ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,void*) ; 

errcode_t ext2fs_get_generic_bmap_range(ext2fs_generic_bitmap gen_bmap,
					__u64 start, unsigned int num,
					void *out)
{
	ext2fs_generic_bitmap_64 bmap = (ext2fs_generic_bitmap_64) gen_bmap;

	if (!bmap)
		return EINVAL;

	if (EXT2FS_IS_32_BITMAP(bmap)) {
		if ((start+num-1) & ~0xffffffffULL) {
			ext2fs_warn_bitmap2(gen_bmap,
					    EXT2FS_UNMARK_ERROR, 0xffffffff);
			return EINVAL;
		}
		return ext2fs_get_generic_bitmap_range(gen_bmap, bmap->magic,
						       start, num, out);
	}

	if (!EXT2FS_IS_64_BITMAP(bmap))
		return EINVAL;

	INC_STAT(bmap, get_range_count);

	return bmap->bitmap_ops->get_bmap_range(bmap, start, num, out);
}