#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mmp_struct {unsigned int mmp_seq; unsigned int mmp_check_interval; int /*<<< orphan*/  mmp_bdevname; int /*<<< orphan*/  mmp_nodename; } ;
typedef  TYPE_2__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
struct TYPE_7__ {int flags; struct mmp_struct* mmp_buf; TYPE_1__* super; int /*<<< orphan*/  device_name; int /*<<< orphan*/  blocksize; } ;
struct TYPE_6__ {unsigned int s_mmp_update_interval; int /*<<< orphan*/  s_mmp_block; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_MMP_FAILED ; 
 scalar_t__ EXT2_ET_MMP_FSCK_ON ; 
 scalar_t__ EXT2_ET_MMP_UNKNOWN_SEQ ; 
 scalar_t__ EXT2_ET_OP_NOT_SUPPORTED ; 
 int EXT2_FLAG_RW ; 
 unsigned int EXT4_MMP_MIN_CHECK_INTERVAL ; 
 unsigned int EXT4_MMP_SEQ_CLEAN ; 
 unsigned int EXT4_MMP_SEQ_FSCK ; 
 scalar_t__ ext2fs_get_mem (int /*<<< orphan*/ ,struct mmp_struct**) ; 
 unsigned int ext2fs_mmp_new_seq () ; 
 scalar_t__ ext2fs_mmp_read (TYPE_2__*,int /*<<< orphan*/ ,struct mmp_struct*) ; 
 scalar_t__ ext2fs_mmp_write (TYPE_2__*,int /*<<< orphan*/ ,struct mmp_struct*) ; 
 int /*<<< orphan*/  gethostname (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,unsigned int) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

errcode_t ext2fs_mmp_start(ext2_filsys fs)
{
#ifdef CONFIG_MMP
	struct mmp_struct *mmp_s;
	unsigned seq;
	unsigned int mmp_check_interval;
	errcode_t retval = 0;

	if (fs->mmp_buf == NULL) {
		retval = ext2fs_get_mem(fs->blocksize, &fs->mmp_buf);
		if (retval)
			goto mmp_error;
	}

	retval = ext2fs_mmp_read(fs, fs->super->s_mmp_block, fs->mmp_buf);
	if (retval)
		goto mmp_error;

	mmp_s = fs->mmp_buf;

	mmp_check_interval = fs->super->s_mmp_update_interval;
	if (mmp_check_interval < EXT4_MMP_MIN_CHECK_INTERVAL)
		mmp_check_interval = EXT4_MMP_MIN_CHECK_INTERVAL;

	seq = mmp_s->mmp_seq;
	if (seq == EXT4_MMP_SEQ_CLEAN)
		goto clean_seq;
	if (seq == EXT4_MMP_SEQ_FSCK) {
		retval = EXT2_ET_MMP_FSCK_ON;
		goto mmp_error;
	}

	if (seq > EXT4_MMP_SEQ_FSCK) {
		retval = EXT2_ET_MMP_UNKNOWN_SEQ;
		goto mmp_error;
	}

	/*
	 * If check_interval in MMP block is larger, use that instead of
	 * check_interval from the superblock.
	 */
	if (mmp_s->mmp_check_interval > mmp_check_interval)
		mmp_check_interval = mmp_s->mmp_check_interval;

	sleep(min(mmp_check_interval * 2 + 1, mmp_check_interval + 60));

	retval = ext2fs_mmp_read(fs, fs->super->s_mmp_block, fs->mmp_buf);
	if (retval)
		goto mmp_error;

	if (seq != mmp_s->mmp_seq) {
		retval = EXT2_ET_MMP_FAILED;
		goto mmp_error;
	}

clean_seq:
	if (!(fs->flags & EXT2_FLAG_RW))
		goto mmp_error;

	mmp_s->mmp_seq = seq = ext2fs_mmp_new_seq();
#ifdef HAVE_GETHOSTNAME
	gethostname(mmp_s->mmp_nodename, sizeof(mmp_s->mmp_nodename));
#else
	strcpy(mmp_s->mmp_nodename, "unknown host");
#endif
	strncpy(mmp_s->mmp_bdevname, fs->device_name,
		sizeof(mmp_s->mmp_bdevname));

	retval = ext2fs_mmp_write(fs, fs->super->s_mmp_block, fs->mmp_buf);
	if (retval)
		goto mmp_error;

	sleep(min(2 * mmp_check_interval + 1, mmp_check_interval + 60));

	retval = ext2fs_mmp_read(fs, fs->super->s_mmp_block, fs->mmp_buf);
	if (retval)
		goto mmp_error;

	if (seq != mmp_s->mmp_seq) {
		retval = EXT2_ET_MMP_FAILED;
		goto mmp_error;
	}

	mmp_s->mmp_seq = EXT4_MMP_SEQ_FSCK;
	retval = ext2fs_mmp_write(fs, fs->super->s_mmp_block, fs->mmp_buf);
	if (retval)
		goto mmp_error;

	return 0;

mmp_error:
	return retval;
#else
	return EXT2_ET_OP_NOT_SUPPORTED;
#endif
}