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
typedef  int /*<<< orphan*/  errcode_t ;
typedef  scalar_t__ blk64_t ;
struct TYPE_4__ {scalar_t__ magic; scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ EXT2FS_IS_32_BITMAP (TYPE_1__*) ; 
 int /*<<< orphan*/  EXT2FS_IS_64_BITMAP (TYPE_1__*) ; 
 int /*<<< orphan*/  ext2fs_compare_generic_bitmap (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_test_generic_bmap (int /*<<< orphan*/ ,scalar_t__) ; 

errcode_t ext2fs_compare_generic_bmap(errcode_t neq,
				      ext2fs_generic_bitmap gen_bm1,
				      ext2fs_generic_bitmap gen_bm2)
{
	ext2fs_generic_bitmap_64 bm1 = (ext2fs_generic_bitmap_64) gen_bm1;
	ext2fs_generic_bitmap_64 bm2 = (ext2fs_generic_bitmap_64) gen_bm2;
	blk64_t	i;

	if (!bm1 || !bm2)
		return EINVAL;
	if (bm1->magic != bm2->magic)
		return EINVAL;

	/* Now we know both bitmaps have the same magic */
	if (EXT2FS_IS_32_BITMAP(bm1))
		return ext2fs_compare_generic_bitmap(bm1->magic, neq,
						     gen_bm1, gen_bm2);

	if (!EXT2FS_IS_64_BITMAP(bm1))
		return EINVAL;

	if ((bm1->start != bm2->start) ||
	    (bm1->end != bm2->end))
		return neq;

	for (i = bm1->end - ((bm1->end - bm1->start) % 8); i <= bm1->end; i++)
		if (ext2fs_test_generic_bmap(gen_bm1, i) !=
		    ext2fs_test_generic_bmap(gen_bm2, i))
			return neq;

	return 0;
}