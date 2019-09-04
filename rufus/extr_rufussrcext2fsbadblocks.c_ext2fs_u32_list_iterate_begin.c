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
struct ext2_struct_u32_iterate {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_u32_list ;
typedef  TYPE_1__* ext2_u32_iterate ;
typedef  scalar_t__ errcode_t ;
struct TYPE_4__ {scalar_t__ ptr; int /*<<< orphan*/  bb; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_BADBLOCKS_ITERATE ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_BADBLOCKS_LIST ; 
 scalar_t__ ext2fs_get_mem (int,TYPE_1__**) ; 

errcode_t ext2fs_u32_list_iterate_begin(ext2_u32_list bb,
					ext2_u32_iterate *ret)
{
	ext2_u32_iterate iter;
	errcode_t		retval;

	EXT2_CHECK_MAGIC(bb, EXT2_ET_MAGIC_BADBLOCKS_LIST);

	retval = ext2fs_get_mem(sizeof(struct ext2_struct_u32_iterate), &iter);
	if (retval)
		return retval;

	iter->magic = EXT2_ET_MAGIC_BADBLOCKS_ITERATE;
	iter->bb = bb;
	iter->ptr = 0;
	*ret = iter;
	return 0;
}