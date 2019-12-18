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
struct ext2_inode {int i_flags; } ;
struct ext2_inline_data {size_t ea_size; int /*<<< orphan*/  ea_data; int /*<<< orphan*/  ino; int /*<<< orphan*/  fs; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  scalar_t__ errcode_t ;

/* Variables and functions */
 scalar_t__ EXT2_ET_NO_INLINE_DATA ; 
 int EXT4_INLINE_DATA_FL ; 
 size_t EXT4_MIN_INLINE_DATA_SIZE ; 
 scalar_t__ ext2fs_free_mem (int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_inline_data_ea_get (struct ext2_inline_data*) ; 
 scalar_t__ ext2fs_read_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ext2_inode*) ; 

errcode_t ext2fs_inline_data_size(ext2_filsys fs, ext2_ino_t ino, size_t *size)
{
	struct ext2_inode inode;
	struct ext2_inline_data data;
	errcode_t retval;

	retval = ext2fs_read_inode(fs, ino, &inode);
	if (retval)
		return retval;

	if (!(inode.i_flags & EXT4_INLINE_DATA_FL))
		return EXT2_ET_NO_INLINE_DATA;

	data.fs = fs;
	data.ino = ino;
	retval = ext2fs_inline_data_ea_get(&data);
	if (retval)
		return retval;

	*size = EXT4_MIN_INLINE_DATA_SIZE + data.ea_size;
	return ext2fs_free_mem(&data.ea_data);
}