#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  TYPE_1__* ext2_file_t ;
typedef  scalar_t__ errcode_t ;
struct TYPE_3__ {size_t pos; int /*<<< orphan*/  buf; int /*<<< orphan*/  inode; int /*<<< orphan*/  ino; int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 scalar_t__ ext2fs_inline_data_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static errcode_t
ext2fs_file_read_inline_data(ext2_file_t file, void *buf,
			     unsigned int wanted, unsigned int *got)
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

	if (file->pos >= size)
		goto out;

	count = size - file->pos;
	if (count > wanted)
		count = wanted;
	memcpy(buf, file->buf + file->pos, count);
	file->pos += count;
	buf = (char *) buf + count;

out:
	if (got)
		*got = count;
	return retval;
}