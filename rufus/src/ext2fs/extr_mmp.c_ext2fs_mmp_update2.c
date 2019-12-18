#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_sec; } ;
struct mmp_struct {scalar_t__ mmp_time; int /*<<< orphan*/  mmp_seq; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
struct TYPE_7__ {int /*<<< orphan*/  s_mmp_block; } ;
struct TYPE_6__ {int flags; scalar_t__ mmp_last_written; TYPE_5__* super; struct mmp_struct* mmp_buf; struct mmp_struct* mmp_cmp; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_MMP_CHANGE_ABORT ; 
 scalar_t__ EXT2_ET_OP_NOT_SUPPORTED ; 
 int EXT2_FLAG_RW ; 
 int EXT2_FLAG_SKIP_MMP ; 
 scalar_t__ EXT2_MIN_MMP_UPDATE_INTERVAL ; 
 int /*<<< orphan*/  EXT4_MMP_SEQ_FSCK ; 
 int /*<<< orphan*/  ext2fs_has_feature_mmp (TYPE_5__*) ; 
 scalar_t__ ext2fs_mmp_read (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_mmp_write (TYPE_1__*,int /*<<< orphan*/ ,struct mmp_struct*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (struct mmp_struct*,struct mmp_struct*,int) ; 

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