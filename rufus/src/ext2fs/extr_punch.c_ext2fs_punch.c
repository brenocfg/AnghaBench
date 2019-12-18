#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ext2_inode {int i_flags; int i_size; int i_blocks; } ;
typedef  int ext2_ino_t ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ blk64_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int EXT4_EXTENTS_FL ; 
 int EXT4_INLINE_DATA_FL ; 
 scalar_t__ ext2fs_punch_extent (int /*<<< orphan*/ ,int,struct ext2_inode*,scalar_t__,scalar_t__) ; 
 scalar_t__ ext2fs_punch_ind (int /*<<< orphan*/ ,struct ext2_inode*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ ext2fs_punch_inline_data (int /*<<< orphan*/ ,int,struct ext2_inode*,scalar_t__,scalar_t__) ; 
 scalar_t__ ext2fs_read_inode (int /*<<< orphan*/ ,int,struct ext2_inode*) ; 
 scalar_t__ ext2fs_write_inode (int /*<<< orphan*/ ,int,struct ext2_inode*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

errcode_t ext2fs_punch(ext2_filsys fs, ext2_ino_t ino,
		       struct ext2_inode *inode,
		       char *block_buf, blk64_t start,
		       blk64_t end)
{
	errcode_t		retval;
	struct ext2_inode	inode_buf;

	if (start > end)
		return EINVAL;

	/* Read inode structure if necessary */
	if (!inode) {
		retval = ext2fs_read_inode(fs, ino, &inode_buf);
		if (retval)
			return retval;
		inode = &inode_buf;
	}
	if (inode->i_flags & EXT4_INLINE_DATA_FL)
		return ext2fs_punch_inline_data(fs, ino, inode, start, end);
	else if (inode->i_flags & EXT4_EXTENTS_FL)
		retval = ext2fs_punch_extent(fs, ino, inode, start, end);
	else
		retval = ext2fs_punch_ind(fs, inode, block_buf, start, end);
	if (retval)
		return retval;

#ifdef PUNCH_DEBUG
	printf("%u: write inode size now %u blocks %u\n",
		ino, inode->i_size, inode->i_blocks);
#endif
	return ext2fs_write_inode(fs, ino, inode);
}