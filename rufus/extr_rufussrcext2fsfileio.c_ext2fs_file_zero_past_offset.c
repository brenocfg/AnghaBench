#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ext2_off64_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  TYPE_2__* ext2_file_t ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ blk64_t ;
struct TYPE_7__ {int /*<<< orphan*/  ino; TYPE_1__* fs; } ;
struct TYPE_6__ {scalar_t__ blocksize; int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int BMAP_RET_UNINIT ; 
 scalar_t__ ext2fs_bmap2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int*,scalar_t__*) ; 
 int /*<<< orphan*/  ext2fs_free_mem (char**) ; 
 scalar_t__ ext2fs_get_mem (scalar_t__,char**) ; 
 scalar_t__ io_channel_read_blk64 (int /*<<< orphan*/ ,scalar_t__,int,char*) ; 
 scalar_t__ io_channel_write_blk64 (int /*<<< orphan*/ ,scalar_t__,int,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sync_buffer_position (TYPE_2__*) ; 

__attribute__((used)) static errcode_t ext2fs_file_zero_past_offset(ext2_file_t file,
					      ext2_off64_t offset)
{
	ext2_filsys fs = file->fs;
	char *b = NULL;
	ext2_off64_t off = offset % fs->blocksize;
	blk64_t blk;
	int ret_flags;
	errcode_t retval;

	if (off == 0)
		return 0;

	retval = sync_buffer_position(file);
	if (retval)
		return retval;

	/* Is there an initialized block at the end? */
	retval = ext2fs_bmap2(fs, file->ino, NULL, NULL, 0,
			      offset / fs->blocksize, &ret_flags, &blk);
	if (retval)
		return retval;
	if ((blk == 0) || (ret_flags & BMAP_RET_UNINIT))
		return 0;

	/* Zero to the end of the block */
	retval = ext2fs_get_mem(fs->blocksize, &b);
	if (retval)
		return retval;

	/* Read/zero/write block */
	retval = io_channel_read_blk64(fs->io, blk, 1, b);
	if (retval)
		goto out;

	memset(b + off, 0, fs->blocksize - off);

	retval = io_channel_write_blk64(fs->io, blk, 1, b);
	if (retval)
		goto out;

out:
	ext2fs_free_mem(&b);
	return retval;
}