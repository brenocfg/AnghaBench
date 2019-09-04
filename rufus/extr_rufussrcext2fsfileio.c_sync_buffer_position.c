#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ext2_file_t ;
typedef  scalar_t__ errcode_t ;
typedef  int blk64_t ;
struct TYPE_6__ {int pos; int blockno; int /*<<< orphan*/  flags; TYPE_1__* fs; } ;
struct TYPE_5__ {int blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_FILE_BUF_VALID ; 
 scalar_t__ ext2fs_file_flush (TYPE_2__*) ; 

__attribute__((used)) static errcode_t sync_buffer_position(ext2_file_t file)
{
	blk64_t	b;
	errcode_t	retval;

	b = file->pos / file->fs->blocksize;
	if (b != file->blockno) {
		retval = ext2fs_file_flush(file);
		if (retval)
			return retval;
		file->flags &= ~EXT2_FILE_BUF_VALID;
	}
	file->blockno = b;
	return 0;
}