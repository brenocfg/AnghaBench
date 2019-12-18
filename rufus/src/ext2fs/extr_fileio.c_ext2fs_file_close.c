#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_file_t ;
typedef  int /*<<< orphan*/  errcode_t ;
struct TYPE_6__ {struct TYPE_6__* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2_FILE ; 
 int /*<<< orphan*/  ext2fs_file_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  ext2fs_free_mem (TYPE_1__**) ; 

errcode_t ext2fs_file_close(ext2_file_t file)
{
	errcode_t	retval;

	EXT2_CHECK_MAGIC(file, EXT2_ET_MAGIC_EXT2_FILE);

	retval = ext2fs_file_flush(file);

	if (file->buf)
		ext2fs_free_mem(&file->buf);
	ext2fs_free_mem(&file);

	return retval;
}