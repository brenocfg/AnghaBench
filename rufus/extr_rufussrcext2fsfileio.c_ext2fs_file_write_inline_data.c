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
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  TYPE_1__* ext2_file_t ;
typedef  scalar_t__ errcode_t ;
struct TYPE_4__ {size_t pos; int /*<<< orphan*/  inode; int /*<<< orphan*/  ino; int /*<<< orphan*/  buf; int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_INLINE_DATA_NO_SPACE ; 
 unsigned int EXT2_I_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_file_set_size2 (TYPE_1__*,unsigned int) ; 
 scalar_t__ ext2fs_inline_data_expand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_inline_data_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ ext2fs_inline_data_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ ext2fs_read_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,unsigned int) ; 

__attribute__((used)) static errcode_t
ext2fs_file_write_inline_data(ext2_file_t file, const void *buf,
			      unsigned int nbytes, unsigned int *written)
{
	ext2_filsys fs;
	errcode_t retval;
	unsigned int count = 0;
	size_t size;

	fs = file->fs;
	retval = ext2fs_inline_data_get(fs, file->ino, &file->inode,
					file->buf, &size);
	if (retval)
		return retval;

	if (file->pos < size) {
		count = nbytes - file->pos;
		memcpy(file->buf + file->pos, buf, count);

		retval = ext2fs_inline_data_set(fs, file->ino, &file->inode,
						file->buf, count);
		if (retval == EXT2_ET_INLINE_DATA_NO_SPACE)
			goto expand;
		if (retval)
			return retval;

		file->pos += count;

		/* Update inode size */
		if (count != 0 && EXT2_I_SIZE(&file->inode) < file->pos) {
			errcode_t	rc;

			rc = ext2fs_file_set_size2(file, file->pos);
			if (retval == 0)
				retval = rc;
		}

		if (written)
			*written = count;
		return 0;
	}

expand:
	retval = ext2fs_inline_data_expand(fs, file->ino);
	if (retval)
		return retval;
	/*
	 * reload inode and return no space error
	 *
	 * XXX: file->inode could be copied from the outside
	 * in ext2fs_file_open2().  We have no way to modify
	 * the outside inode.
	 */
	retval = ext2fs_read_inode(fs, file->ino, &file->inode);
	if (retval)
		return retval;
	return EXT2_ET_INLINE_DATA_NO_SPACE;
}