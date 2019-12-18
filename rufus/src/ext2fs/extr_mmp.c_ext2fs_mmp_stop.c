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
struct mmp_struct {int /*<<< orphan*/  mmp_seq; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
struct TYPE_7__ {int /*<<< orphan*/  s_mmp_block; } ;
struct TYPE_6__ {int flags; int mmp_fd; TYPE_5__* super; struct mmp_struct* mmp_cmp; struct mmp_struct* mmp_buf; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_MMP_CHANGE_ABORT ; 
 scalar_t__ EXT2_ET_OP_NOT_SUPPORTED ; 
 int EXT2_FLAG_RW ; 
 int EXT2_FLAG_SKIP_MMP ; 
 int /*<<< orphan*/  EXT4_MMP_SEQ_CLEAN ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ext2fs_has_feature_mmp (TYPE_5__*) ; 
 scalar_t__ ext2fs_mmp_read (TYPE_1__*,int /*<<< orphan*/ ,struct mmp_struct*) ; 
 scalar_t__ ext2fs_mmp_write (TYPE_1__*,int /*<<< orphan*/ ,struct mmp_struct*) ; 
 scalar_t__ memcmp (struct mmp_struct*,struct mmp_struct*,int) ; 

errcode_t ext2fs_mmp_stop(ext2_filsys fs)
{
#ifdef CONFIG_MMP
	struct mmp_struct *mmp, *mmp_cmp;
	errcode_t retval = 0;

	if (!ext2fs_has_feature_mmp(fs->super) ||
	    !(fs->flags & EXT2_FLAG_RW) || (fs->flags & EXT2_FLAG_SKIP_MMP))
		goto mmp_error;

	retval = ext2fs_mmp_read(fs, fs->super->s_mmp_block, fs->mmp_buf);
	if (retval)
		goto mmp_error;

	/* Check if the MMP block is not changed. */
	mmp = fs->mmp_buf;
	mmp_cmp = fs->mmp_cmp;
	if (memcmp(mmp, mmp_cmp, sizeof(*mmp_cmp))) {
		retval = EXT2_ET_MMP_CHANGE_ABORT;
		goto mmp_error;
	}

	mmp_cmp->mmp_seq = EXT4_MMP_SEQ_CLEAN;
	retval = ext2fs_mmp_write(fs, fs->super->s_mmp_block, fs->mmp_cmp);

mmp_error:
	if (fs->mmp_fd > 0) {
		close(fs->mmp_fd);
		fs->mmp_fd = -1;
	}

	return retval;
#else
	if (!ext2fs_has_feature_mmp(fs->super) ||
	    !(fs->flags & EXT2_FLAG_RW) || (fs->flags & EXT2_FLAG_SKIP_MMP))
		return 0;

	return EXT2_ET_OP_NOT_SUPPORTED;
#endif
}