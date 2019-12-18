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
struct seq_file {TYPE_2__* private; } ;
struct TYPE_5__ {TYPE_1__* procfs_list; } ;
typedef  TYPE_2__ procfs_list_cursor_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  pl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 void* procfs_list_next_node (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
procfs_list_seq_next(struct seq_file *f, void *p, loff_t *pos)
{
	procfs_list_cursor_t *cursor = f->private;
	ASSERT(MUTEX_HELD(&cursor->procfs_list->pl_lock));
	return (procfs_list_next_node(cursor, pos));
}