#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_filsys ;
typedef  TYPE_2__* ext2_file_t ;
typedef  scalar_t__ errcode_t ;
typedef  unsigned int __u64 ;
struct TYPE_11__ {int i_flags; } ;
struct TYPE_10__ {unsigned int pos; scalar_t__ buf; TYPE_7__ inode; TYPE_1__* fs; } ;
struct TYPE_9__ {unsigned int blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2_FILE ; 
 unsigned int EXT2_I_SIZE (TYPE_7__*) ; 
 int EXT4_INLINE_DATA_FL ; 
 scalar_t__ ext2fs_file_read_inline_data (TYPE_2__*,void*,unsigned int,unsigned int*) ; 
 scalar_t__ load_buffer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,unsigned int) ; 
 scalar_t__ sync_buffer_position (TYPE_2__*) ; 

errcode_t ext2fs_file_read(ext2_file_t file, void *buf,
			   unsigned int wanted, unsigned int *got)
{
	ext2_filsys	fs;
	errcode_t	retval = 0;
	unsigned int	start, c, count = 0;
	__u64		left;
	char		*ptr = (char *) buf;

	EXT2_CHECK_MAGIC(file, EXT2_ET_MAGIC_EXT2_FILE);
	fs = file->fs;

	/* If an inode has inline data, things get complicated. */
	if (file->inode.i_flags & EXT4_INLINE_DATA_FL)
		return ext2fs_file_read_inline_data(file, buf, wanted, got);

	while ((file->pos < EXT2_I_SIZE(&file->inode)) && (wanted > 0)) {
		retval = sync_buffer_position(file);
		if (retval)
			goto fail;
		retval = load_buffer(file, 0);
		if (retval)
			goto fail;

		start = file->pos % fs->blocksize;
		c = fs->blocksize - start;
		if (c > wanted)
			c = wanted;
		left = EXT2_I_SIZE(&file->inode) - file->pos ;
		if (c > left)
			c = left;

		memcpy(ptr, file->buf+start, c);
		file->pos += c;
		ptr += c;
		count += c;
		wanted -= c;
	}

fail:
	if (got)
		*got = count;
	return retval;
}