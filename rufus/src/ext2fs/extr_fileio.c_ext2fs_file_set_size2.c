#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int ext2_off64_t ;
typedef  TYPE_1__* ext2_file_t ;
typedef  scalar_t__ errcode_t ;
typedef  int blk64_t ;
struct TYPE_10__ {int blocksize; int /*<<< orphan*/  super; } ;
struct TYPE_9__ {int /*<<< orphan*/  inode; scalar_t__ ino; TYPE_2__* fs; } ;

/* Variables and functions */
 int EXT2_BLOCK_SIZE_BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EXT2_ET_FILE_TOO_BIG ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2_FILE ; 
 int EXT2_I_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_file_block_offset_too_big (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ext2fs_file_zero_past_offset (TYPE_1__*,int) ; 
 scalar_t__ ext2fs_inode_size_set (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ext2fs_punch (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned long long) ; 
 scalar_t__ ext2fs_write_inode (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 

errcode_t ext2fs_file_set_size2(ext2_file_t file, ext2_off64_t size)
{
	ext2_off64_t	old_size;
	errcode_t	retval;
	blk64_t		old_truncate, truncate_block;

	EXT2_CHECK_MAGIC(file, EXT2_ET_MAGIC_EXT2_FILE);

	if (size && ext2fs_file_block_offset_too_big(file->fs, &file->inode,
					(size - 1) / file->fs->blocksize))
		return EXT2_ET_FILE_TOO_BIG;
	truncate_block = ((size + file->fs->blocksize - 1) >>
			  EXT2_BLOCK_SIZE_BITS(file->fs->super));
	old_size = EXT2_I_SIZE(&file->inode);
	old_truncate = ((old_size + file->fs->blocksize - 1) >>
		      EXT2_BLOCK_SIZE_BITS(file->fs->super));

	retval = ext2fs_inode_size_set(file->fs, &file->inode, size);
	if (retval)
		return retval;

	if (file->ino) {
		retval = ext2fs_write_inode(file->fs, file->ino, &file->inode);
		if (retval)
			return retval;
	}

	retval = ext2fs_file_zero_past_offset(file, size);
	if (retval)
		return retval;

	if (truncate_block >= old_truncate)
		return 0;

	return ext2fs_punch(file->fs, file->ino, &file->inode, 0,
			    truncate_block, ~0ULL);
}