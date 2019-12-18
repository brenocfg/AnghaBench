#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct ext2_inode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_flags; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  int /*<<< orphan*/  blk64_t ;
struct TYPE_11__ {int /*<<< orphan*/  blocksize; int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMAP_SET ; 
 int /*<<< orphan*/  EXT4_EXTENTS_FL ; 
 int EXT4_INLINE_DATA_DOTDOT_SIZE ; 
 int /*<<< orphan*/  EXT4_INLINE_DATA_FL ; 
 int /*<<< orphan*/  ext2fs_block_alloc_stats (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ext2fs_bmap2 (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_dirent_swab_in2 (TYPE_1__*,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_free_mem (char**) ; 
 scalar_t__ ext2fs_get_memzero (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ ext2fs_has_feature_extents (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_iblk_add_blocks (TYPE_1__*,struct ext2_inode*,int) ; 
 scalar_t__ ext2fs_inline_data_convert_dir (TYPE_1__*,int /*<<< orphan*/ ,char*,char*,size_t) ; 
 scalar_t__ ext2fs_new_block2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_write_dir_block4 (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_write_inode (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode*) ; 

__attribute__((used)) static errcode_t
ext2fs_inline_data_dir_expand(ext2_filsys fs, ext2_ino_t ino,
			      struct ext2_inode *inode, char *buf, size_t size)
{
	errcode_t retval;
	blk64_t blk;
	char *blk_buf;

	retval = ext2fs_get_memzero(fs->blocksize, &blk_buf);
	if (retval)
		return retval;

#ifdef WORDS_BIGENDIAN
	retval = ext2fs_dirent_swab_in2(fs, buf + EXT4_INLINE_DATA_DOTDOT_SIZE,
					size, 0);
	if (retval)
		goto errout;
#endif

	/* Adjust the rec_len */
	retval = ext2fs_inline_data_convert_dir(fs, ino, blk_buf, buf, size);
	if (retval)
		goto errout;
	/* Allocate a new block */
	retval = ext2fs_new_block2(fs, 0, 0, &blk);
	if (retval)
		goto errout;
	retval = ext2fs_write_dir_block4(fs, blk, blk_buf, 0, ino);
	if (retval)
		goto errout;

	/* Update inode */
	if (ext2fs_has_feature_extents(fs->super))
		inode->i_flags |= EXT4_EXTENTS_FL;
	inode->i_flags &= ~EXT4_INLINE_DATA_FL;
	retval = ext2fs_iblk_add_blocks(fs, inode, 1);
	if (retval)
		goto errout;
	inode->i_size = fs->blocksize;
	retval = ext2fs_bmap2(fs, ino, inode, 0, BMAP_SET, 0, 0, &blk);
	if (retval)
		goto errout;
	retval = ext2fs_write_inode(fs, ino, inode);
	if (retval)
		goto errout;
	ext2fs_block_alloc_stats(fs, blk, +1);

errout:
	ext2fs_free_mem(&blk_buf);
	return retval;
}