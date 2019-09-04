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
typedef  TYPE_1__* ext2_file_t ;
typedef  scalar_t__ errcode_t ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_3__ {scalar_t__ magic; int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_MAGIC_EXT2_FILE ; 
 int /*<<< orphan*/  EXT2_I_SIZE (int /*<<< orphan*/ *) ; 

errcode_t ext2fs_file_get_lsize(ext2_file_t file, __u64 *ret_size)
{
	if (file->magic != EXT2_ET_MAGIC_EXT2_FILE)
		return EXT2_ET_MAGIC_EXT2_FILE;
	*ret_size = EXT2_I_SIZE(&file->inode);
	return 0;
}