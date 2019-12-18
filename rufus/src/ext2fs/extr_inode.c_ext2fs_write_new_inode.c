#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ext2_inode_large {void* i_crtime; scalar_t__ i_extra_isize; } ;
struct ext2_inode {void* i_atime; void* i_mtime; void* i_ctime; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  void* __u32 ;
struct TYPE_4__ {void* now; int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ EXT2_GOOD_OLD_INODE_SIZE ; 
 int EXT2_INODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_write_inode_full (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode*,int) ; 
 int /*<<< orphan*/  free (struct ext2_inode*) ; 
 struct ext2_inode* malloc (int) ; 
 int /*<<< orphan*/  memset (struct ext2_inode*,int /*<<< orphan*/ ,int) ; 
 void* time (int /*<<< orphan*/ *) ; 

errcode_t ext2fs_write_new_inode(ext2_filsys fs, ext2_ino_t ino,
				 struct ext2_inode *inode)
{
	struct ext2_inode	*buf;
	int 			size = EXT2_INODE_SIZE(fs->super);
	struct ext2_inode_large	*large_inode;
	errcode_t		retval;
	__u32 			t = fs->now ? fs->now : time(NULL);

	if (!inode->i_ctime)
		inode->i_ctime = t;
	if (!inode->i_mtime)
		inode->i_mtime = t;
	if (!inode->i_atime)
		inode->i_atime = t;

	if (size == sizeof(struct ext2_inode))
		return ext2fs_write_inode_full(fs, ino, inode,
					       sizeof(struct ext2_inode));

	buf = malloc(size);
	if (!buf)
		return ENOMEM;

	memset(buf, 0, size);
	*buf = *inode;

	large_inode = (struct ext2_inode_large *) buf;
	large_inode->i_extra_isize = sizeof(struct ext2_inode_large) -
		EXT2_GOOD_OLD_INODE_SIZE;
	if (!large_inode->i_crtime)
		large_inode->i_crtime = t;

	retval = ext2fs_write_inode_full(fs, ino, buf, size);
	free(buf);
	return retval;
}