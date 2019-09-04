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

errcode_t ext2fs_mmp_read(ext2_filsys fs, blk64_t mmp_blk, void *buf)
{
#ifdef CONFIG_MMP
	struct mmp_struct *mmp_cmp;
	errcode_t retval = 0;

	if ((mmp_blk <= fs->super->s_first_data_block) ||
	    (mmp_blk >= ext2fs_blocks_count(fs->super)))
		return EXT2_ET_MMP_BAD_BLOCK;

	/* ext2fs_open() reserves fd0,1,2 to avoid stdio collision, so checking
	 * mmp_fd <= 0 is OK to validate that the fd is valid.  This opens its
	 * own fd to read the MMP block to ensure that it is using O_DIRECT,
	 * regardless of how the io_manager is doing reads, to avoid caching of
	 * the MMP block by the io_manager or the VM.  It needs to be fresh. */
	if (fs->mmp_fd <= 0) {
		fs->mmp_fd = open(fs->device_name, O_RDWR | O_DIRECT);
		if (fs->mmp_fd < 0) {
			retval = EXT2_ET_MMP_OPEN_DIRECT;
			goto out;
		}
	}

	if (fs->mmp_cmp == NULL) {
		int align = ext2fs_get_dio_alignment(fs->mmp_fd);

		retval = ext2fs_get_memalign(fs->blocksize, align,
					     &fs->mmp_cmp);
		if (retval)
			return retval;
	}

	if ((blk64_t) ext2fs_llseek(fs->mmp_fd, mmp_blk * fs->blocksize,
				    SEEK_SET) !=
	    mmp_blk * fs->blocksize) {
		retval = EXT2_ET_LLSEEK_FAILED;
		goto out;
	}

	if (read(fs->mmp_fd, fs->mmp_cmp, fs->blocksize) != fs->blocksize) {
		retval = EXT2_ET_SHORT_READ;
		goto out;
	}

	mmp_cmp = fs->mmp_cmp;

	if (!(fs->flags & EXT2_FLAG_IGNORE_CSUM_ERRORS) &&
	    !ext2fs_mmp_csum_verify(fs, mmp_cmp))
		retval = EXT2_ET_MMP_CSUM_INVALID;

#ifdef WORDS_BIGENDIAN
	ext2fs_swap_mmp(mmp_cmp);
#endif

	if (buf != NULL && buf != fs->mmp_cmp)
		memcpy(buf, fs->mmp_cmp, fs->blocksize);

	if (mmp_cmp->mmp_magic != EXT4_MMP_MAGIC) {
		retval = EXT2_ET_MMP_MAGIC_INVALID;
		goto out;
	}

out:
	return retval;
#else
	return EXT2_ET_OP_NOT_SUPPORTED;
#endif
}