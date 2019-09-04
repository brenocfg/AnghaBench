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

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_OP_NOT_SUPPORTED ; 

errcode_t ext2fs_mmp_init(ext2_filsys fs)
{
#ifdef CONFIG_MMP
	struct ext2_super_block *sb = fs->super;
	blk64_t mmp_block;
	errcode_t retval;

	if (sb->s_mmp_update_interval == 0)
		sb->s_mmp_update_interval = EXT4_MMP_UPDATE_INTERVAL;
	/* This is probably excessively large, but who knows? */
	else if (sb->s_mmp_update_interval > EXT4_MMP_MAX_UPDATE_INTERVAL)
		return EXT2_ET_INVALID_ARGUMENT;

	if (fs->mmp_buf == NULL) {
		retval = ext2fs_get_mem(fs->blocksize, &fs->mmp_buf);
		if (retval)
			goto out;
	}

	retval = ext2fs_alloc_block2(fs, 0, fs->mmp_buf, &mmp_block);
	if (retval)
		goto out;

	sb->s_mmp_block = mmp_block;

	retval = ext2fs_mmp_reset(fs);
	if (retval)
		goto out;

out:
	return retval;
#else
	return EXT2_ET_OP_NOT_SUPPORTED;
#endif
}