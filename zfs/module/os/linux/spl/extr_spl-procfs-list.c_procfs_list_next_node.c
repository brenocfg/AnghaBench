#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pl_list; } ;
typedef  TYPE_1__ procfs_list_t ;
struct TYPE_6__ {int /*<<< orphan*/  cached_pos; void* cached_node; TYPE_1__* procfs_list; } ;
typedef  TYPE_2__ procfs_list_cursor_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_ID (TYPE_1__*,void*) ; 
 void* SEQ_START_TOKEN ; 
 void* list_head (int /*<<< orphan*/ *) ; 
 void* list_next (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void *
procfs_list_next_node(procfs_list_cursor_t *cursor, loff_t *pos)
{
	void *next_node;
	procfs_list_t *procfs_list = cursor->procfs_list;

	if (cursor->cached_node == SEQ_START_TOKEN)
		next_node = list_head(&procfs_list->pl_list);
	else
		next_node = list_next(&procfs_list->pl_list,
		    cursor->cached_node);

	if (next_node != NULL) {
		cursor->cached_node = next_node;
		cursor->cached_pos = NODE_ID(procfs_list, cursor->cached_node);
		*pos = cursor->cached_pos;
	}
	return (next_node);
}