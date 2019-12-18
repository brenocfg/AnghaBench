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
typedef  void mmp_struct ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  int blk64_t ;
struct TYPE_6__ {int s_first_data_block; } ;
struct TYPE_5__ {scalar_t__ mmp_fd; void* mmp_cmp; int blocksize; int flags; int /*<<< orphan*/  device_name; TYPE_4__* super; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_LLSEEK_FAILED ; 
 scalar_t__ EXT2_ET_MMP_BAD_BLOCK ; 
 scalar_t__ EXT2_ET_MMP_CSUM_INVALID ; 
 scalar_t__ EXT2_ET_MMP_MAGIC_INVALID ; 
 scalar_t__ EXT2_ET_MMP_OPEN_DIRECT ; 
 scalar_t__ EXT2_ET_OP_NOT_SUPPORTED ; 
 scalar_t__ EXT2_ET_SHORT_READ ; 
 int EXT2_FLAG_IGNORE_CSUM_ERRORS ; 
 scalar_t__ EXT4_MMP_MAGIC ; 
 int O_DIRECT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int ext2fs_blocks_count (TYPE_4__*) ; 
 int ext2fs_get_dio_alignment (scalar_t__) ; 
 scalar_t__ ext2fs_get_memalign (int,int,void**) ; 
 scalar_t__ ext2fs_llseek (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_mmp_csum_verify (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  ext2fs_swap_mmp (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int) ; 
 int read (scalar_t__,void*,int) ; 

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