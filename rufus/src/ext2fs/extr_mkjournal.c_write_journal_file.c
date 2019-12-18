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
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  int blk_t ;
struct TYPE_4__ {scalar_t__ blocksize; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_SHORT_WRITE ; 
 int EXT2_MKJOURNAL_LAZYINIT ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ ext2fs_create_journal_superblock (TYPE_1__*,int,int,char**) ; 
 int /*<<< orphan*/  ext2fs_free_mem (char**) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int write (int,char*,scalar_t__) ; 

__attribute__((used)) static errcode_t write_journal_file(ext2_filsys fs, char *filename,
				    blk_t num_blocks, int flags)
{
	errcode_t	retval;
	char		*buf = 0;
	int		fd, ret_size;
	blk_t		i;

	if ((retval = ext2fs_create_journal_superblock(fs, num_blocks, flags,
						       &buf)))
		return retval;

	/* Open the device or journal file */
	if ((fd = open(filename, O_WRONLY)) < 0) {
		retval = errno;
		goto errfree;
	}

	/* Write the superblock out */
	retval = EXT2_ET_SHORT_WRITE;
	ret_size = write(fd, buf, fs->blocksize);
	if (ret_size < 0) {
		retval = errno;
		goto errout;
	}
	if (ret_size != (int) fs->blocksize)
		goto errout;
	memset(buf, 0, fs->blocksize);

	if (flags & EXT2_MKJOURNAL_LAZYINIT)
		goto success;

	for (i = 1; i < num_blocks; i++) {
		ret_size = write(fd, buf, fs->blocksize);
		if (ret_size < 0) {
			retval = errno;
			goto errout;
		}
		if (ret_size != (int) fs->blocksize)
			goto errout;
	}

success:
	retval = 0;
errout:
	close(fd);
errfree:
	ext2fs_free_mem(&buf);
	return retval;
}