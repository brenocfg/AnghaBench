#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ext2_ext_attr_header {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  int /*<<< orphan*/  blk64_t ;
struct TYPE_5__ {int /*<<< orphan*/  io; int /*<<< orphan*/  blocksize; } ;

/* Variables and functions */
 scalar_t__ ext2fs_ext_attr_block_csum_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ext2_ext_attr_header*) ; 
 int /*<<< orphan*/  ext2fs_free_mem (char**) ; 
 scalar_t__ ext2fs_get_mem (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  ext2fs_mark_changed (TYPE_1__*) ; 
 int /*<<< orphan*/  ext2fs_swap_ext_attr (char*,void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ io_channel_write_blk64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

errcode_t ext2fs_write_ext_attr3(ext2_filsys fs, blk64_t block, void *inbuf,
				 ext2_ino_t inum)
{
	errcode_t	retval;
	char		*write_buf;

#ifdef WORDS_BIGENDIAN
	retval = ext2fs_get_mem(fs->blocksize, &write_buf);
	if (retval)
		return retval;
	ext2fs_swap_ext_attr(write_buf, inbuf, fs->blocksize, 1);
#else
	write_buf = (char *) inbuf;
#endif

	retval = ext2fs_ext_attr_block_csum_set(fs, inum, block,
			(struct ext2_ext_attr_header *)write_buf);
	if (retval)
		return retval;

	retval = io_channel_write_blk64(fs->io, block, 1, write_buf);
#ifdef WORDS_BIGENDIAN
	ext2fs_free_mem(&write_buf);
#endif
	if (!retval)
		ext2fs_mark_changed(fs);
	return retval;
}