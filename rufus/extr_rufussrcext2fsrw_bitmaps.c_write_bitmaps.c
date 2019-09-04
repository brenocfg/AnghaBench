#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ dgrp_t ;
typedef  int blk64_t ;
typedef  int __u64 ;
struct TYPE_18__ {scalar_t__ s_first_data_block; } ;
struct TYPE_17__ {int flags; int blocksize; scalar_t__ group_desc_count; int /*<<< orphan*/  io; int /*<<< orphan*/  inode_map; TYPE_7__* super; int /*<<< orphan*/  block_map; } ;

/* Variables and functions */
 int EXT2FS_B2C (TYPE_1__*,scalar_t__) ; 
 unsigned int EXT2FS_NUM_B2C (TYPE_1__*,int) ; 
 int /*<<< orphan*/  EXT2_BG_BLOCK_UNINIT ; 
 int /*<<< orphan*/  EXT2_BG_INODE_UNINIT ; 
 scalar_t__ EXT2_BLOCKS_PER_GROUP (TYPE_7__*) ; 
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int EXT2_CLUSTERS_PER_GROUP (TYPE_7__*) ; 
 scalar_t__ EXT2_ET_BLOCK_BITMAP_WRITE ; 
 scalar_t__ EXT2_ET_INODE_BITMAP_WRITE ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2FS_FILSYS ; 
 scalar_t__ EXT2_ET_RO_FILSYS ; 
 int EXT2_FLAG_BB_DIRTY ; 
 int EXT2_FLAG_DIRTY ; 
 int EXT2_FLAG_IB_DIRTY ; 
 int EXT2_FLAG_RW ; 
 int EXT2_INODES_PER_GROUP (TYPE_7__*) ; 
 scalar_t__ ext2fs_bg_flags_test (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_block_bitmap_csum_set (TYPE_1__*,scalar_t__,char*,int) ; 
 int ext2fs_block_bitmap_loc (TYPE_1__*,scalar_t__) ; 
 int ext2fs_blocks_count (TYPE_7__*) ; 
 int /*<<< orphan*/  ext2fs_free_mem (char**) ; 
 scalar_t__ ext2fs_get_block_bitmap_range2 (int /*<<< orphan*/ ,int,int,char*) ; 
 scalar_t__ ext2fs_get_inode_bitmap_range2 (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  ext2fs_group_desc_csum_set (TYPE_1__*,scalar_t__) ; 
 int ext2fs_has_group_desc_csum (TYPE_1__*) ; 
 scalar_t__ ext2fs_inode_bitmap_csum_set (TYPE_1__*,scalar_t__,char*,int) ; 
 int ext2fs_inode_bitmap_loc (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_set_bit (unsigned int,char*) ; 
 scalar_t__ io_channel_alloc_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ io_channel_write_blk64 (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 

__attribute__((used)) static errcode_t write_bitmaps(ext2_filsys fs, int do_inode, int do_block)
{
	dgrp_t 		i;
	unsigned int	j;
	int		block_nbytes, inode_nbytes;
	unsigned int	nbits;
	errcode_t	retval;
	char		*block_buf = NULL, *inode_buf = NULL;
	int		csum_flag;
	blk64_t		blk;
	blk64_t		blk_itr = EXT2FS_B2C(fs, fs->super->s_first_data_block);
	ext2_ino_t	ino_itr = 1;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	if (!(fs->flags & EXT2_FLAG_RW))
		return EXT2_ET_RO_FILSYS;

	csum_flag = ext2fs_has_group_desc_csum(fs);

	inode_nbytes = block_nbytes = 0;
	if (do_block) {
		block_nbytes = EXT2_CLUSTERS_PER_GROUP(fs->super) / 8;
		retval = io_channel_alloc_buf(fs->io, 0, &block_buf);
		if (retval)
			goto errout;
		memset(block_buf, 0xff, fs->blocksize);
	}
	if (do_inode) {
		inode_nbytes = (size_t)
			((EXT2_INODES_PER_GROUP(fs->super)+7) / 8);
		retval = io_channel_alloc_buf(fs->io, 0, &inode_buf);
		if (retval)
			goto errout;
		memset(inode_buf, 0xff, fs->blocksize);
	}

	for (i = 0; i < fs->group_desc_count; i++) {
		if (!do_block)
			goto skip_block_bitmap;

		if (csum_flag && ext2fs_bg_flags_test(fs, i, EXT2_BG_BLOCK_UNINIT)
		    )
			goto skip_this_block_bitmap;

		retval = ext2fs_get_block_bitmap_range2(fs->block_map,
				blk_itr, block_nbytes << 3, block_buf);
		if (retval)
			goto errout;

		if (i == fs->group_desc_count - 1) {
			/* Force bitmap padding for the last group */
			nbits = EXT2FS_NUM_B2C(fs,
				((ext2fs_blocks_count(fs->super)
				  - (__u64) fs->super->s_first_data_block)
				 % (__u64) EXT2_BLOCKS_PER_GROUP(fs->super)));
			if (nbits)
				for (j = nbits; j < fs->blocksize * 8; j++)
					ext2fs_set_bit(j, block_buf);
		}

		retval = ext2fs_block_bitmap_csum_set(fs, i, block_buf,
						      block_nbytes);
		if (retval)
			return retval;
		ext2fs_group_desc_csum_set(fs, i);
		fs->flags |= EXT2_FLAG_DIRTY;

		blk = ext2fs_block_bitmap_loc(fs, i);
		if (blk) {
			retval = io_channel_write_blk64(fs->io, blk, 1,
							block_buf);
			if (retval) {
				retval = EXT2_ET_BLOCK_BITMAP_WRITE;
				goto errout;
			}
		}
	skip_this_block_bitmap:
		blk_itr += block_nbytes << 3;
	skip_block_bitmap:

		if (!do_inode)
			continue;

		if (csum_flag && ext2fs_bg_flags_test(fs, i, EXT2_BG_INODE_UNINIT)
		    )
			goto skip_this_inode_bitmap;

		retval = ext2fs_get_inode_bitmap_range2(fs->inode_map,
				ino_itr, inode_nbytes << 3, inode_buf);
		if (retval)
			goto errout;

		retval = ext2fs_inode_bitmap_csum_set(fs, i, inode_buf,
						      inode_nbytes);
		if (retval)
			goto errout;
		ext2fs_group_desc_csum_set(fs, i);
		fs->flags |= EXT2_FLAG_DIRTY;

		blk = ext2fs_inode_bitmap_loc(fs, i);
		if (blk) {
			retval = io_channel_write_blk64(fs->io, blk, 1,
						      inode_buf);
			if (retval) {
				retval = EXT2_ET_INODE_BITMAP_WRITE;
				goto errout;
			}
		}
	skip_this_inode_bitmap:
		ino_itr += inode_nbytes << 3;

	}
	if (do_block) {
		fs->flags &= ~EXT2_FLAG_BB_DIRTY;
		ext2fs_free_mem(&block_buf);
	}
	if (do_inode) {
		fs->flags &= ~EXT2_FLAG_IB_DIRTY;
		ext2fs_free_mem(&inode_buf);
	}
	return 0;
errout:
	if (inode_buf)
		ext2fs_free_mem(&inode_buf);
	if (block_buf)
		ext2fs_free_mem(&block_buf);
	return retval;
}