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
typedef  int /*<<< orphan*/  blk64_t ;
typedef  TYPE_1__* bb_u64_list ;
typedef  TYPE_2__* bb_u64_iterate ;
struct TYPE_5__ {scalar_t__ magic; scalar_t__ ptr; TYPE_1__* bb; } ;
struct TYPE_4__ {scalar_t__ magic; scalar_t__ num; int /*<<< orphan*/ * list; } ;

/* Variables and functions */
 scalar_t__ BB_ET_MAGIC_BADBLOCKS_ITERATE ; 
 scalar_t__ BB_ET_MAGIC_BADBLOCKS_LIST ; 

__attribute__((used)) static int bb_u64_list_iterate(bb_u64_iterate iter, blk64_t *blk)
{
	bb_u64_list bb;

	if (iter->magic != BB_ET_MAGIC_BADBLOCKS_ITERATE)
		return 0;

	bb = iter->bb;

	if (bb->magic != BB_ET_MAGIC_BADBLOCKS_LIST)
		return 0;

	if (iter->ptr < bb->num) {
		*blk = bb->list[iter->ptr++];
		return 1;
	}
	*blk = 0;
	return 0;
}