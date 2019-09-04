#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_u32_list ;
typedef  int /*<<< orphan*/  blk_t ;
struct TYPE_5__ {int num; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_BADBLOCKS_LIST ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ext2fs_u32_list_equal(ext2_u32_list bb1, ext2_u32_list bb2)
{
	EXT2_CHECK_MAGIC(bb1, EXT2_ET_MAGIC_BADBLOCKS_LIST);
	EXT2_CHECK_MAGIC(bb2, EXT2_ET_MAGIC_BADBLOCKS_LIST);

	if (bb1->num != bb2->num)
		return 0;

	if (memcmp(bb1->list, bb2->list, bb1->num * sizeof(blk_t)) != 0)
		return 0;
	return 1;
}