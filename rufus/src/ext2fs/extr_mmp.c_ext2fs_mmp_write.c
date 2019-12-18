#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct mmp_struct {int /*<<< orphan*/  mmp_time; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  int /*<<< orphan*/  blk64_t ;
struct TYPE_6__ {scalar_t__ s_mmp_block; scalar_t__ s_first_data_block; } ;
struct TYPE_5__ {int /*<<< orphan*/  io; TYPE_4__* super; int /*<<< orphan*/  mmp_last_written; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_MMP_BAD_BLOCK ; 
 scalar_t__ EXT2_ET_OP_NOT_SUPPORTED ; 
 scalar_t__ ext2fs_blocks_count (TYPE_4__*) ; 
 scalar_t__ ext2fs_mmp_csum_set (TYPE_1__*,struct mmp_struct*) ; 
 int /*<<< orphan*/  ext2fs_swap_mmp (struct mmp_struct*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_channel_flush (int /*<<< orphan*/ ) ; 
 scalar_t__ io_channel_write_blk64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 

errcode_t ext2fs_mmp_write(ext2_filsys fs, blk64_t mmp_blk, void *buf)
{
#ifdef CONFIG_MMP
	struct mmp_struct *mmp_s = buf;
	struct timeval tv;
	errcode_t retval = 0;

	gettimeofday(&tv, 0);
	mmp_s->mmp_time = tv.tv_sec;
	fs->mmp_last_written = tv.tv_sec;

	if (fs->super->s_mmp_block < fs->super->s_first_data_block ||
	    fs->super->s_mmp_block > ext2fs_blocks_count(fs->super))
		return EXT2_ET_MMP_BAD_BLOCK;

#ifdef WORDS_BIGENDIAN
	ext2fs_swap_mmp(mmp_s);
#endif

	retval = ext2fs_mmp_csum_set(fs, mmp_s);
	if (retval)
		return retval;

	/* I was tempted to make this use O_DIRECT and the mmp_fd, but
	 * this caused no end of grief, while leaving it as-is works. */
	retval = io_channel_write_blk64(fs->io, mmp_blk, -(int)sizeof(struct mmp_struct), buf);

#ifdef WORDS_BIGENDIAN
	ext2fs_swap_mmp(mmp_s);
#endif

	/* Make sure the block gets to disk quickly */
	io_channel_flush(fs->io);
	return retval;
#else
	return EXT2_ET_OP_NOT_SUPPORTED;
#endif
}