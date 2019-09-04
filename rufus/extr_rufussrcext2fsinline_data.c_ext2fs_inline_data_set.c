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
struct ext2_inode {scalar_t__ i_block; } ;
struct ext2_inline_data {size_t ea_size; char* ea_data; int /*<<< orphan*/  ino; int /*<<< orphan*/  fs; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  scalar_t__ errcode_t ;

/* Variables and functions */
 scalar_t__ EXT2_ET_INLINE_DATA_NO_SPACE ; 
 size_t EXT4_MIN_INLINE_DATA_SIZE ; 
 scalar_t__ ext2fs_inline_data_ea_set (struct ext2_inline_data*) ; 
 scalar_t__ ext2fs_inline_data_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ ext2fs_read_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ext2_inode*) ; 
 scalar_t__ ext2fs_write_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ext2_inode*) ; 
 scalar_t__ ext2fs_xattr_inode_max_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

errcode_t ext2fs_inline_data_set(ext2_filsys fs, ext2_ino_t ino,
				 struct ext2_inode *inode,
				 void *buf, size_t size)
{
	struct ext2_inode inode_buf;
	struct ext2_inline_data data = {
		.fs = fs,
		.ino = ino,
	};
	errcode_t retval;
	size_t free_ea_size, existing_size, free_inode_size;

	if (!inode) {
		retval = ext2fs_read_inode(fs, ino, &inode_buf);
		if (retval)
			return retval;
		inode = &inode_buf;
	}

	if (size <= EXT4_MIN_INLINE_DATA_SIZE) {
		memcpy((void *)inode->i_block, buf, size);
	} else {
		retval = ext2fs_xattr_inode_max_size(fs, ino, &free_ea_size);
		if (retval)
			return retval;

		retval = ext2fs_inline_data_size(fs, ino, &existing_size);
		if (retval)
			return retval;

		if (existing_size < EXT4_MIN_INLINE_DATA_SIZE) {
			free_inode_size = EXT4_MIN_INLINE_DATA_SIZE -
					  existing_size;
		} else {
			free_inode_size = 0;
		}

		if (size != existing_size &&
		    size > existing_size + free_ea_size + free_inode_size)
			return EXT2_ET_INLINE_DATA_NO_SPACE;

		memcpy((void *)inode->i_block, buf, EXT4_MIN_INLINE_DATA_SIZE);
		if (size > EXT4_MIN_INLINE_DATA_SIZE)
			data.ea_size = size - EXT4_MIN_INLINE_DATA_SIZE;
		data.ea_data = (char *) buf + EXT4_MIN_INLINE_DATA_SIZE;
	}
	retval = ext2fs_write_inode(fs, ino, inode);
	if (retval)
		return retval;
	return ext2fs_inline_data_ea_set(&data);
}