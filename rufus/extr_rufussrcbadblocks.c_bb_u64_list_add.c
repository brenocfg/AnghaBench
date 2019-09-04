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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  TYPE_1__* bb_u64_list ;
struct TYPE_4__ {scalar_t__* list; int num; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BB_ET_MAGIC_BADBLOCKS_LIST ; 
 int /*<<< orphan*/  BB_ET_NO_MEMORY ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* realloc (scalar_t__*,int) ; 

__attribute__((used)) static errcode_t bb_u64_list_add(bb_u64_list bb, uint64_t blk)
{
	int		i, j;
	uint64_t* old_bb_list = bb->list;

	BB_CHECK_MAGIC(bb, BB_ET_MAGIC_BADBLOCKS_LIST);

	if (bb->num >= bb->size) {
		bb->size += 100;
		bb->list = realloc(bb->list, bb->size * sizeof(uint64_t));
		if (bb->list == NULL) {
			bb->list = old_bb_list;
			bb->size -= 100;
			return BB_ET_NO_MEMORY;
		}
		// coverity[suspicious_sizeof]
		memset(&bb->list[bb->size-100], 0, 100 * sizeof(uint64_t));
	}

	/*
	 * Add special case code for appending to the end of the list
	 */
	i = bb->num-1;
	if ((bb->num != 0) && (bb->list[i] == blk))
		return 0;
	if ((bb->num == 0) || (bb->list[i] < blk)) {
		bb->list[bb->num++] = blk;
		return 0;
	}

	j = bb->num;
	for (i=0; i < bb->num; i++) {
		if (bb->list[i] == blk)
			return 0;
		if (bb->list[i] > blk) {
			j = i;
			break;
		}
	}
	for (i=bb->num; i > j; i--)
		bb->list[i] = bb->list[i-1];
	bb->list[j] = blk;
	bb->num++;
	return 0;
}