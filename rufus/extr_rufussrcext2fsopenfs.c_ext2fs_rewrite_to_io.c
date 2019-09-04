#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ io_channel ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
struct TYPE_3__ {int flags; scalar_t__ image_io; scalar_t__ io; int /*<<< orphan*/  blocksize; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_NOT_IMAGE_FILE ; 
 int EXT2_FLAG_BB_DIRTY ; 
 int EXT2_FLAG_DIRTY ; 
 int EXT2_FLAG_IB_DIRTY ; 
 int EXT2_FLAG_IMAGE_FILE ; 
 int EXT2_FLAG_RW ; 
 int /*<<< orphan*/  io_channel_close (scalar_t__) ; 
 scalar_t__ io_channel_set_blksize (scalar_t__,int /*<<< orphan*/ ) ; 

errcode_t ext2fs_rewrite_to_io(ext2_filsys fs, io_channel new_io)
{
	errcode_t err;

	if ((fs->flags & EXT2_FLAG_IMAGE_FILE) == 0)
		return EXT2_ET_NOT_IMAGE_FILE;
	err = io_channel_set_blksize(new_io, fs->blocksize);
	if (err)
		return err;
	if ((new_io == fs->image_io) || (new_io == fs->io))
		return 0;
	if ((fs->image_io != fs->io) &&
	    fs->image_io)
		io_channel_close(fs->image_io);
	if (fs->io)
		io_channel_close(fs->io);
	fs->io = fs->image_io = new_io;
	fs->flags |= EXT2_FLAG_DIRTY | EXT2_FLAG_RW |
		EXT2_FLAG_BB_DIRTY | EXT2_FLAG_IB_DIRTY;
	fs->flags &= ~EXT2_FLAG_IMAGE_FILE;
	return 0;
}