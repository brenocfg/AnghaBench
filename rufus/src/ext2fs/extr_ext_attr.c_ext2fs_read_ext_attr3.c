#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  int /*<<< orphan*/  blk64_t ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  io; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_EXT_ATTR_CSUM_INVALID ; 
 int EXT2_FLAG_IGNORE_CSUM_ERRORS ; 
 scalar_t__ check_ext_attr_header (void*) ; 
 int /*<<< orphan*/  ext2fs_ext_attr_block_csum_verify (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ext2fs_swap_ext_attr (void*,void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ io_channel_read_blk64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 

errcode_t ext2fs_read_ext_attr3(ext2_filsys fs, blk64_t block, void *buf,
				ext2_ino_t inum)
{
	int		csum_failed = 0;
	errcode_t	retval;

	retval = io_channel_read_blk64(fs->io, block, 1, buf);
	if (retval)
		return retval;

	if (!(fs->flags & EXT2_FLAG_IGNORE_CSUM_ERRORS) &&
	    !ext2fs_ext_attr_block_csum_verify(fs, inum, block, buf))
		csum_failed = 1;

#ifdef WORDS_BIGENDIAN
	ext2fs_swap_ext_attr(buf, buf, fs->blocksize, 1);
#endif

	retval = check_ext_attr_header(buf);
	if (retval == 0 && csum_failed)
		retval = EXT2_ET_EXT_ATTR_CSUM_INVALID;

	return retval;
}