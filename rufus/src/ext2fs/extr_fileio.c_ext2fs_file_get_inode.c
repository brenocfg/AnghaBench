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
struct ext2_inode {int dummy; } ;
typedef  TYPE_1__* ext2_file_t ;
struct TYPE_3__ {scalar_t__ magic; struct ext2_inode inode; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_MAGIC_EXT2_FILE ; 

struct ext2_inode *ext2fs_file_get_inode(ext2_file_t file)
{
	if (file->magic != EXT2_ET_MAGIC_EXT2_FILE)
		return NULL;
	return &file->inode;
}