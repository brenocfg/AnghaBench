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
struct link_struct {char const* name; int flags; scalar_t__ err; scalar_t__ done; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  sb; int /*<<< orphan*/  inode; int /*<<< orphan*/  namelen; TYPE_1__* fs; } ;
struct ext2_inode {int i_flags; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRENT_FLAG_INCLUDE_EMPTY ; 
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EXT2_ET_DIR_NO_SPACE ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2FS_FILSYS ; 
 scalar_t__ EXT2_ET_RO_FILSYS ; 
 int EXT2_FLAG_RW ; 
 int EXT2_INDEX_FL ; 
 scalar_t__ ext2fs_dir_iterate (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct link_struct*) ; 
 scalar_t__ ext2fs_read_inode (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode*) ; 
 scalar_t__ ext2fs_write_inode (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode*) ; 
 int /*<<< orphan*/  link_proc ; 
 int /*<<< orphan*/  strlen (char const*) ; 

errcode_t ext2fs_link(ext2_filsys fs, ext2_ino_t dir, const char *name,
		      ext2_ino_t ino, int flags)
{
	errcode_t		retval;
	struct link_struct	ls;
	struct ext2_inode	inode;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	if (!(fs->flags & EXT2_FLAG_RW))
		return EXT2_ET_RO_FILSYS;

	ls.fs = fs;
	ls.name = name;
	ls.namelen = name ? strlen(name) : 0;
	ls.inode = ino;
	ls.flags = flags;
	ls.done = 0;
	ls.sb = fs->super;
	ls.blocksize = fs->blocksize;
	ls.err = 0;

	retval = ext2fs_dir_iterate(fs, dir, DIRENT_FLAG_INCLUDE_EMPTY,
				    0, link_proc, &ls);
	if (retval)
		return retval;
	if (ls.err)
		return ls.err;

	if (!ls.done)
		return EXT2_ET_DIR_NO_SPACE;

	if ((retval = ext2fs_read_inode(fs, dir, &inode)) != 0)
		return retval;

	/*
	 * If this function changes to preserve the htree, remove the
	 * two hunks in link_proc that shove checksum tails into the
	 * former dx_root/dx_node blocks.
	 */
	if (inode.i_flags & EXT2_INDEX_FL) {
		inode.i_flags &= ~EXT2_INDEX_FL;
		if ((retval = ext2fs_write_inode(fs, dir, &inode)) != 0)
			return retval;
	}

	return 0;
}