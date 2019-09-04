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
typedef  int /*<<< orphan*/  uint64_t ;
struct bb_struct_u64_list {int dummy; } ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  int /*<<< orphan*/  blk64_t ;
typedef  TYPE_1__* bb_u64_list ;
struct TYPE_5__ {int size; int num; int /*<<< orphan*/ * list; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_ET_MAGIC_BADBLOCKS_LIST ; 
 int /*<<< orphan*/  BB_ET_NO_MEMORY ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static errcode_t make_u64_list(int size, int num, uint64_t *list, bb_u64_list *ret)
{
	bb_u64_list bb;

	bb = calloc(1, sizeof(struct bb_struct_u64_list));
	if (bb == NULL)
		return BB_ET_NO_MEMORY;
	bb->magic = BB_ET_MAGIC_BADBLOCKS_LIST;
	bb->size = size ? size : 10;
	bb->num = num;
	bb->list = malloc(sizeof(blk64_t) * bb->size);
	if (bb->list == NULL) {
		free(bb);
		bb = NULL;
		return BB_ET_NO_MEMORY;
	}
	if (list)
		memcpy(bb->list, list, bb->size * sizeof(blk64_t));
	else
		memset(bb->list, 0, bb->size * sizeof(blk64_t));
	*ret = bb;
	return 0;
}