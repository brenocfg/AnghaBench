#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ext2_super_block {scalar_t__ s_mmp_update_interval; int /*<<< orphan*/  s_mmp_block; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  int /*<<< orphan*/  blk64_t ;
struct TYPE_5__ {int /*<<< orphan*/ * mmp_buf; int /*<<< orphan*/  blocksize; struct ext2_super_block* super; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_INVALID_ARGUMENT ; 
 scalar_t__ EXT2_ET_OP_NOT_SUPPORTED ; 
 scalar_t__ EXT4_MMP_MAX_UPDATE_INTERVAL ; 
 scalar_t__ EXT4_MMP_UPDATE_INTERVAL ; 
 scalar_t__ ext2fs_alloc_block2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_get_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ ext2fs_mmp_reset (TYPE_1__*) ; 

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