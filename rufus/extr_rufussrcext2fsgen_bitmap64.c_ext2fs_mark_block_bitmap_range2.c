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
typedef  int /*<<< orphan*/  ext2fs_block_bitmap ;
typedef  unsigned int blk64_t ;
typedef  int __u64 ;
struct TYPE_8__ {unsigned int cluster_bits; unsigned int start; unsigned int end; TYPE_1__* bitmap_ops; int /*<<< orphan*/  description; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* mark_bmap_extent ) (TYPE_2__*,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 scalar_t__ EXT2FS_IS_32_BITMAP (TYPE_2__*) ; 
 int /*<<< orphan*/  EXT2FS_IS_64_BITMAP (TYPE_2__*) ; 
 int /*<<< orphan*/  EXT2FS_UNMARK_ERROR ; 
 int /*<<< orphan*/  EXT2_ET_BAD_BLOCK_MARK ; 
 int /*<<< orphan*/  INC_STAT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_mark_block_bitmap_range (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ext2fs_warn_bitmap (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_warn_bitmap2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mark_ext_count ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned int,unsigned int) ; 

void ext2fs_mark_block_bitmap_range2(ext2fs_block_bitmap gen_bmap,
				     blk64_t block, unsigned int num)
{
	ext2fs_generic_bitmap_64 bmap = (ext2fs_generic_bitmap_64) gen_bmap;
	__u64	end = block + num;

	if (!bmap)
		return;

	if (EXT2FS_IS_32_BITMAP(bmap)) {
		if ((block & ~0xffffffffULL) ||
		    ((block+num-1) & ~0xffffffffULL)) {
			ext2fs_warn_bitmap2((ext2fs_generic_bitmap) bmap,
					    EXT2FS_UNMARK_ERROR, 0xffffffff);
			return;
		}
		ext2fs_mark_block_bitmap_range((ext2fs_generic_bitmap) bmap,
					       block, num);
	}

	if (!EXT2FS_IS_64_BITMAP(bmap))
		return;

	INC_STAT(bmap, mark_ext_count);

	/* convert to clusters if necessary */
	block >>= bmap->cluster_bits;
	end += (1 << bmap->cluster_bits) - 1;
	end >>= bmap->cluster_bits;
	num = end - block;

	if ((block < bmap->start) || (block > bmap->end) ||
	    (block+num-1 > bmap->end)) {
		ext2fs_warn_bitmap(EXT2_ET_BAD_BLOCK_MARK, block,
				   bmap->description);
		return;
	}

	bmap->bitmap_ops->mark_bmap_extent(bmap, block, num);
}