#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  unsigned int dgrp_t ;
typedef  int blk_t ;
typedef  int blk64_t ;
struct TYPE_8__ {int s_first_meta_bg; int s_reserved_gdt_blocks; } ;
struct TYPE_7__ {int blocksize; int desc_blocks; TYPE_3__* super; } ;

/* Variables and functions */
 unsigned int EXT2_DESC_PER_BLOCK (TYPE_3__*) ; 
 int ext2fs_bg_has_super (TYPE_1__*,unsigned int) ; 
 int ext2fs_group_first_block2 (TYPE_1__*,unsigned int) ; 
 scalar_t__ ext2fs_has_feature_meta_bg (TYPE_3__*) ; 

errcode_t ext2fs_super_and_bgd_loc2(ext2_filsys fs,
					   dgrp_t group,
					   blk64_t *ret_super_blk,
					   blk64_t *ret_old_desc_blk,
					   blk64_t *ret_new_desc_blk,
					   blk_t *ret_used_blks)
{
	blk64_t	group_block, super_blk = 0, old_desc_blk = 0, new_desc_blk = 0;
	unsigned int meta_bg, meta_bg_size;
	blk_t	numblocks = 0;
	blk64_t old_desc_blocks;
	int	has_super;

	group_block = ext2fs_group_first_block2(fs, group);
	if (group_block == 0 && fs->blocksize == 1024)
		group_block = 1; /* Deal with 1024 blocksize && bigalloc */

	if (ext2fs_has_feature_meta_bg(fs->super))
		old_desc_blocks = fs->super->s_first_meta_bg;
	else
		old_desc_blocks =
			fs->desc_blocks + fs->super->s_reserved_gdt_blocks;

	has_super = ext2fs_bg_has_super(fs, group);

	if (has_super) {
		super_blk = group_block;
		numblocks++;
	}
	meta_bg_size = EXT2_DESC_PER_BLOCK(fs->super);
	meta_bg = group / meta_bg_size;

	if (!ext2fs_has_feature_meta_bg(fs->super) ||
	    (meta_bg < fs->super->s_first_meta_bg)) {
		if (has_super) {
			old_desc_blk = group_block + 1;
			numblocks += old_desc_blocks;
		}
	} else {
		if (((group % meta_bg_size) == 0) ||
		    ((group % meta_bg_size) == 1) ||
		    ((group % meta_bg_size) == (meta_bg_size-1))) {
			if (has_super)
				has_super = 1;
			new_desc_blk = group_block + has_super;
			numblocks++;
		}
	}

	if (ret_super_blk)
		*ret_super_blk = super_blk;
	if (ret_old_desc_blk)
		*ret_old_desc_blk = old_desc_blk;
	if (ret_new_desc_blk)
		*ret_new_desc_blk = new_desc_blk;
	if (ret_used_blks)
		*ret_used_blks = numblocks;

	return 0;
}