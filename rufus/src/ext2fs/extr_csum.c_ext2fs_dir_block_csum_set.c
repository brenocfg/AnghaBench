#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ext2_dir_entry {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_DIR_NO_SPACE_FOR_CSUM ; 
 int EXT2_FLAG_IGNORE_CSUM_ERRORS ; 
 scalar_t__ __get_dirent_tail (TYPE_1__*,struct ext2_dir_entry*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ __get_dx_countlimit (TYPE_1__*,struct ext2_dir_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ext2fs_dirent_csum_set (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_dir_entry*) ; 
 int /*<<< orphan*/  ext2fs_dx_csum_set (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_dir_entry*) ; 
 int /*<<< orphan*/  ext2fs_has_feature_metadata_csum (int /*<<< orphan*/ ) ; 

errcode_t ext2fs_dir_block_csum_set(ext2_filsys fs, ext2_ino_t inum,
				    struct ext2_dir_entry *dirent)
{
	if (!ext2fs_has_feature_metadata_csum(fs->super))
		return 0;

	if (__get_dirent_tail(fs, dirent, NULL, 1) == 0)
		return ext2fs_dirent_csum_set(fs, inum, dirent);
	if (__get_dx_countlimit(fs, dirent, NULL, NULL, 1) == 0)
		return ext2fs_dx_csum_set(fs, inum, dirent);

	if (fs->flags & EXT2_FLAG_IGNORE_CSUM_ERRORS)
		return 0;
	return EXT2_ET_DIR_NO_SPACE_FOR_CSUM;
}