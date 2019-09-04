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
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_OP_NOT_SUPPORTED ; 
 int EXT2_FLAG_RW ; 
 int EXT2_FLAG_SKIP_MMP ; 
 int /*<<< orphan*/  ext2fs_has_feature_mmp (int /*<<< orphan*/ ) ; 

errcode_t ext2fs_mmp_update2(ext2_filsys fs, int immediately)
{
#ifdef CONFIG_MMP
	struct mmp_struct *mmp, *mmp_cmp;
	struct timeval tv;
	errcode_t retval = 0;

	if (!ext2fs_has_feature_mmp(fs->super) ||
	    !(fs->flags & EXT2_FLAG_RW) || (fs->flags & EXT2_FLAG_SKIP_MMP))
		return 0;

	gettimeofday(&tv, 0);
	if (!immediately &&
	    tv.tv_sec - fs->mmp_last_written < EXT2_MIN_MMP_UPDATE_INTERVAL)
		return 0;

	retval = ext2fs_mmp_read(fs, fs->super->s_mmp_block, NULL);
	if (retval)
		goto mmp_error;

	mmp = fs->mmp_buf;
	mmp_cmp = fs->mmp_cmp;

	if (memcmp(mmp, mmp_cmp, sizeof(*mmp_cmp)))
		return EXT2_ET_MMP_CHANGE_ABORT;

	mmp->mmp_time = tv.tv_sec;
	mmp->mmp_seq = EXT4_MMP_SEQ_FSCK;
	retval = ext2fs_mmp_write(fs, fs->super->s_mmp_block, fs->mmp_buf);

mmp_error:
	return retval;
#else
	if (!ext2fs_has_feature_mmp(fs->super) ||
	    !(fs->flags & EXT2_FLAG_RW) || (fs->flags & EXT2_FLAG_SKIP_MMP))
		return 0;

	return EXT2_ET_OP_NOT_SUPPORTED;
#endif
}