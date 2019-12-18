#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {TYPE_2__* private; } ;
struct TYPE_3__ {int /*<<< orphan*/  pl_lock; } ;
typedef  TYPE_1__ procfs_list_t ;
struct TYPE_4__ {TYPE_1__* procfs_list; } ;
typedef  TYPE_2__ procfs_list_cursor_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
procfs_list_seq_stop(struct seq_file *f, void *p)
{
	procfs_list_cursor_t *cursor = f->private;
	procfs_list_t *procfs_list = cursor->procfs_list;
	mutex_exit(&procfs_list->pl_lock);
}