#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ext2_inode {int dummy; } ;
struct ext2_file {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  TYPE_2__* ext2_file_t ;
typedef  scalar_t__ errcode_t ;
struct TYPE_11__ {int flags; struct TYPE_11__* buf; int /*<<< orphan*/  inode; int /*<<< orphan*/  ino; TYPE_1__* fs; int /*<<< orphan*/  magic; } ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2_FILE ; 
 scalar_t__ EXT2_ET_RO_FILSYS ; 
 int EXT2_FILE_CREATE ; 
 int EXT2_FILE_MASK ; 
 int EXT2_FILE_WRITE ; 
 int EXT2_FLAG_RW ; 
 int /*<<< orphan*/  ext2fs_free_mem (TYPE_2__**) ; 
 scalar_t__ ext2fs_get_array (int,int /*<<< orphan*/ ,TYPE_2__**) ; 
 scalar_t__ ext2fs_get_mem (int,TYPE_2__**) ; 
 scalar_t__ ext2fs_read_inode (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ext2_inode*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

errcode_t ext2fs_file_open2(ext2_filsys fs, ext2_ino_t ino,
			    struct ext2_inode *inode,
			    int flags, ext2_file_t *ret)
{
	ext2_file_t 	file;
	errcode_t	retval;

	/*
	 * Don't let caller create or open a file for writing if the
	 * filesystem is read-only.
	 */
	if ((flags & (EXT2_FILE_WRITE | EXT2_FILE_CREATE)) &&
	    !(fs->flags & EXT2_FLAG_RW))
		return EXT2_ET_RO_FILSYS;

	retval = ext2fs_get_mem(sizeof(struct ext2_file), &file);
	if (retval)
		return retval;

	memset(file, 0, sizeof(struct ext2_file));
	file->magic = EXT2_ET_MAGIC_EXT2_FILE;
	file->fs = fs;
	file->ino = ino;
	file->flags = flags & EXT2_FILE_MASK;

	if (inode) {
		memcpy(&file->inode, inode, sizeof(struct ext2_inode));
	} else {
		retval = ext2fs_read_inode(fs, ino, &file->inode);
		if (retval)
			goto fail;
	}

	retval = ext2fs_get_array(3, fs->blocksize, &file->buf);
	if (retval)
		goto fail;

	*ret = file;
	return 0;

fail:
	if (file->buf)
		ext2fs_free_mem(&file->buf);
	ext2fs_free_mem(&file);
	return retval;
}