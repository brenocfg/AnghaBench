#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_u32_list ;
typedef  TYPE_2__* ext2_u32_iterate ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_5__ {scalar_t__ magic; scalar_t__ ptr; TYPE_1__* bb; } ;
struct TYPE_4__ {scalar_t__ magic; scalar_t__ num; int /*<<< orphan*/ * list; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_MAGIC_BADBLOCKS_ITERATE ; 
 scalar_t__ EXT2_ET_MAGIC_BADBLOCKS_LIST ; 

int ext2fs_u32_list_iterate(ext2_u32_iterate iter, __u32 *blk)
{
	ext2_u32_list	bb;

	if (iter->magic != EXT2_ET_MAGIC_BADBLOCKS_ITERATE)
		return 0;

	bb = iter->bb;

	if (bb->magic != EXT2_ET_MAGIC_BADBLOCKS_LIST)
		return 0;

	if (iter->ptr < bb->num) {
		*blk = bb->list[iter->ptr++];
		return 1;
	}
	*blk = 0;
	return 0;
}