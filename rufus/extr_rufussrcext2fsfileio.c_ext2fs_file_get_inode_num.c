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
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_file_t ;
struct TYPE_3__ {scalar_t__ magic; int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_MAGIC_EXT2_FILE ; 

ext2_ino_t ext2fs_file_get_inode_num(ext2_file_t file)
{
	if (file->magic != EXT2_ET_MAGIC_EXT2_FILE)
		return 0;
	return file->ino;
}