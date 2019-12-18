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
typedef  TYPE_1__* ext2_u32_list ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {int num; int /*<<< orphan*/ * list; } ;

/* Variables and functions */
 int ext2fs_u32_list_find (TYPE_1__*,int /*<<< orphan*/ ) ; 

int ext2fs_u32_list_del(ext2_u32_list bb, __u32 blk)
{
	int	remloc, i;

	if (bb->num == 0)
		return -1;

	remloc = ext2fs_u32_list_find(bb, blk);
	if (remloc < 0)
		return -1;

	for (i = remloc ; i < bb->num-1; i++)
		bb->list[i] = bb->list[i+1];
	bb->num--;
	return 0;
}