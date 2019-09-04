#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  int /*<<< orphan*/  blk64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_OP_NOT_SUPPORTED ; 

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