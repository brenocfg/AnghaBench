#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct set_badblock_record {int max_ind_blocks; int bad_block_count; struct set_badblock_record* block_buf; struct set_badblock_record* ind_blocks; scalar_t__ err; int /*<<< orphan*/  bb_iter; } ;
struct ext2_inode {void* i_ctime; void* i_mtime; void* i_atime; } ;
typedef  int /*<<< orphan*/  rec ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ ext2_badblocks_list ;
typedef  scalar_t__ errcode_t ;
typedef  int /*<<< orphan*/  blk_t ;
struct TYPE_9__ {int blocksize; void* now; int /*<<< orphan*/  block_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_APPEND ; 
 int /*<<< orphan*/  BLOCK_FLAG_DEPTH_TRAVERSE ; 
 int /*<<< orphan*/  EXT2_BAD_INO ; 
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2FS_FILSYS ; 
 scalar_t__ EXT2_ET_NO_BLOCK_BITMAP ; 
 int /*<<< orphan*/  clear_bad_block_proc ; 
 scalar_t__ ext2fs_badblocks_list_iterate_begin (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext2fs_badblocks_list_iterate_end (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_block_iterate2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct set_badblock_record*) ; 
 int /*<<< orphan*/  ext2fs_free_mem (struct set_badblock_record**) ; 
 scalar_t__ ext2fs_get_array (int,int,struct set_badblock_record**) ; 
 scalar_t__ ext2fs_get_mem (int,struct set_badblock_record**) ; 
 int /*<<< orphan*/  ext2fs_iblk_set (TYPE_1__*,struct ext2_inode*,int) ; 
 scalar_t__ ext2fs_inode_size_set (TYPE_1__*,struct ext2_inode*,int) ; 
 scalar_t__ ext2fs_read_inode (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode*) ; 
 scalar_t__ ext2fs_write_inode (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode*) ; 
 int /*<<< orphan*/  memset (struct set_badblock_record*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bad_block_proc ; 
 void* time (int /*<<< orphan*/ ) ; 

errcode_t ext2fs_update_bb_inode(ext2_filsys fs, ext2_badblocks_list bb_list)
{
	errcode_t			retval;
	struct set_badblock_record 	rec;
	struct ext2_inode		inode;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	if (!fs->block_map)
		return EXT2_ET_NO_BLOCK_BITMAP;

	memset(&rec, 0, sizeof(rec));
	rec.max_ind_blocks = 10;
	retval = ext2fs_get_array(rec.max_ind_blocks, sizeof(blk_t),
				&rec.ind_blocks);
	if (retval)
		return retval;
	memset(rec.ind_blocks, 0, rec.max_ind_blocks * sizeof(blk_t));
	retval = ext2fs_get_mem(fs->blocksize, &rec.block_buf);
	if (retval)
		goto cleanup;
	memset(rec.block_buf, 0, fs->blocksize);
	rec.err = 0;

	/*
	 * First clear the old bad blocks (while saving the indirect blocks)
	 */
	retval = ext2fs_block_iterate2(fs, EXT2_BAD_INO,
				       BLOCK_FLAG_DEPTH_TRAVERSE, 0,
				       clear_bad_block_proc, &rec);
	if (retval)
		goto cleanup;
	if (rec.err) {
		retval = rec.err;
		goto cleanup;
	}

	/*
	 * Now set the bad blocks!
	 *
	 * First, mark the bad blocks as used.  This prevents a bad
	 * block from being used as an indirect block for the bad
	 * block inode (!).
	 */
	if (bb_list) {
		retval = ext2fs_badblocks_list_iterate_begin(bb_list,
							     &rec.bb_iter);
		if (retval)
			goto cleanup;
		retval = ext2fs_block_iterate2(fs, EXT2_BAD_INO,
					       BLOCK_FLAG_APPEND, 0,
					       set_bad_block_proc, &rec);
		ext2fs_badblocks_list_iterate_end(rec.bb_iter);
		if (retval)
			goto cleanup;
		if (rec.err) {
			retval = rec.err;
			goto cleanup;
		}
	}

	/*
	 * Update the bad block inode's mod time and block count
	 * field.
	 */
	retval = ext2fs_read_inode(fs, EXT2_BAD_INO, &inode);
	if (retval)
		goto cleanup;

	inode.i_atime = inode.i_mtime = fs->now ? fs->now : time(0);
	if (!inode.i_ctime)
		inode.i_ctime = fs->now ? fs->now : time(0);
	ext2fs_iblk_set(fs, &inode, rec.bad_block_count);
	retval = ext2fs_inode_size_set(fs, &inode,
				       rec.bad_block_count * fs->blocksize);
	if (retval)
		goto cleanup;

	retval = ext2fs_write_inode(fs, EXT2_BAD_INO, &inode);
	if (retval)
		goto cleanup;

cleanup:
	ext2fs_free_mem(&rec.ind_blocks);
	ext2fs_free_mem(&rec.block_buf);
	return retval;
}