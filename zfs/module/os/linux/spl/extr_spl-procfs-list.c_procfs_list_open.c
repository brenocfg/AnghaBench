#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_file {TYPE_1__* private; } ;
struct inode {int dummy; } ;
struct file {struct seq_file* private_data; } ;
struct TYPE_2__ {scalar_t__ cached_pos; int /*<<< orphan*/ * cached_node; int /*<<< orphan*/  procfs_list; } ;
typedef  TYPE_1__ procfs_list_cursor_t ;

/* Variables and functions */
 int /*<<< orphan*/  PDE_DATA (struct inode*) ; 
 int /*<<< orphan*/  procfs_list_seq_ops ; 
 int seq_open_private (struct file*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
procfs_list_open(struct inode *inode, struct file *filp)
{
	int rc = seq_open_private(filp, &procfs_list_seq_ops,
	    sizeof (procfs_list_cursor_t));
	if (rc != 0)
		return (rc);

	struct seq_file *f = filp->private_data;
	procfs_list_cursor_t *cursor = f->private;
	cursor->procfs_list = PDE_DATA(inode);
	cursor->cached_node = NULL;
	cursor->cached_pos = 0;

	return (0);
}