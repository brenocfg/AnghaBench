#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ext2_inode {int i_size; int i_size_high; int /*<<< orphan*/  i_mode; } ;
typedef  int ext2_off64_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
struct TYPE_8__ {scalar_t__ s_rev_level; } ;
struct TYPE_7__ {TYPE_3__* super; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_FILE_TOO_BIG ; 
 scalar_t__ EXT2_GOOD_OLD_REV ; 
 scalar_t__ LINUX_S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_has_feature_large_file (TYPE_3__*) ; 
 int /*<<< orphan*/  ext2fs_mark_super_dirty (TYPE_1__*) ; 
 scalar_t__ ext2fs_needs_large_file_feature (int) ; 
 int /*<<< orphan*/  ext2fs_set_feature_large_file (TYPE_3__*) ; 
 int /*<<< orphan*/  ext2fs_update_dynamic_rev (TYPE_1__*) ; 

errcode_t ext2fs_inode_size_set(ext2_filsys fs, struct ext2_inode *inode,
				ext2_off64_t size)
{
	/* Only regular files get to be larger than 4GB */
	if (!LINUX_S_ISREG(inode->i_mode) && (size >> 32))
		return EXT2_ET_FILE_TOO_BIG;

	/* If we're writing a large file, set the large_file flag */
	if (LINUX_S_ISREG(inode->i_mode) &&
	    ext2fs_needs_large_file_feature(size) &&
	    (!ext2fs_has_feature_large_file(fs->super) ||
	     fs->super->s_rev_level == EXT2_GOOD_OLD_REV)) {
		ext2fs_set_feature_large_file(fs->super);
		ext2fs_update_dynamic_rev(fs);
		ext2fs_mark_super_dirty(fs);
	}

	inode->i_size = size & 0xffffffff;
	inode->i_size_high = (size >> 32);

	return 0;
}