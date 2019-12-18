#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_filsys ;
typedef  TYPE_2__* ext2_file_t ;
typedef  scalar_t__ errcode_t ;
typedef  int /*<<< orphan*/  blk64_t ;
struct TYPE_9__ {int i_flags; } ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  buf; int /*<<< orphan*/  physblock; int /*<<< orphan*/  blockno; int /*<<< orphan*/  ino; TYPE_5__ inode; TYPE_1__* fs; } ;
struct TYPE_7__ {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMAP_ALLOC ; 
 int /*<<< orphan*/  BMAP_BUFFER ; 
 int BMAP_RET_UNINIT ; 
 int /*<<< orphan*/  BMAP_SET ; 
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2_FILE ; 
 int EXT2_FILE_BUF_DIRTY ; 
 int EXT2_FILE_BUF_VALID ; 
 int EXT4_EXTENTS_FL ; 
 scalar_t__ ext2fs_bmap2 (TYPE_1__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ io_channel_write_blk64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

errcode_t ext2fs_file_flush(ext2_file_t file)
{
	errcode_t	retval;
	ext2_filsys fs;
	int		ret_flags;
	blk64_t		dontcare;

	EXT2_CHECK_MAGIC(file, EXT2_ET_MAGIC_EXT2_FILE);
	fs = file->fs;

	if (!(file->flags & EXT2_FILE_BUF_VALID) ||
	    !(file->flags & EXT2_FILE_BUF_DIRTY))
		return 0;

	/* Is this an uninit block? */
	if (file->physblock && file->inode.i_flags & EXT4_EXTENTS_FL) {
		retval = ext2fs_bmap2(fs, file->ino, &file->inode, BMAP_BUFFER,
				      0, file->blockno, &ret_flags, &dontcare);
		if (retval)
			return retval;
		if (ret_flags & BMAP_RET_UNINIT) {
			retval = ext2fs_bmap2(fs, file->ino, &file->inode,
					      BMAP_BUFFER, BMAP_SET,
					      file->blockno, 0,
					      &file->physblock);
			if (retval)
				return retval;
		}
	}

	/*
	 * OK, the physical block hasn't been allocated yet.
	 * Allocate it.
	 */
	if (!file->physblock) {
		retval = ext2fs_bmap2(fs, file->ino, &file->inode,
				     BMAP_BUFFER, file->ino ? BMAP_ALLOC : 0,
				     file->blockno, 0, &file->physblock);
		if (retval)
			return retval;
	}

	retval = io_channel_write_blk64(fs->io, file->physblock, 1, file->buf);
	if (retval)
		return retval;

	file->flags &= ~EXT2_FILE_BUF_DIRTY;

	return retval;
}