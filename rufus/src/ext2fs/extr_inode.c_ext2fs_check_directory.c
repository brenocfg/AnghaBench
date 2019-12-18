#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ext2_inode {int /*<<< orphan*/  i_mode; } ;
typedef  scalar_t__ ext2_ino_t ;
typedef  TYPE_2__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
struct TYPE_8__ {scalar_t__ (* check_directory ) (TYPE_2__*,scalar_t__) ;TYPE_1__* super; } ;
struct TYPE_7__ {scalar_t__ s_inodes_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EXT2_ET_BAD_INODE_NUM ; 
 scalar_t__ EXT2_ET_CALLBACK_NOTHANDLED ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2FS_FILSYS ; 
 scalar_t__ EXT2_ET_NO_DIRECTORY ; 
 int /*<<< orphan*/  LINUX_S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_read_inode (TYPE_2__*,scalar_t__,struct ext2_inode*) ; 
 scalar_t__ stub1 (TYPE_2__*,scalar_t__) ; 

errcode_t ext2fs_check_directory(ext2_filsys fs, ext2_ino_t ino)
{
	struct	ext2_inode	inode;
	errcode_t		retval;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	if (ino > fs->super->s_inodes_count)
		return EXT2_ET_BAD_INODE_NUM;

	if (fs->check_directory) {
		retval = (fs->check_directory)(fs, ino);
		if (retval != EXT2_ET_CALLBACK_NOTHANDLED)
			return retval;
	}
	retval = ext2fs_read_inode(fs, ino, &inode);
	if (retval)
		return retval;
	if (!LINUX_S_ISDIR(inode.i_mode))
		return EXT2_ET_NO_DIRECTORY;
	return 0;
}