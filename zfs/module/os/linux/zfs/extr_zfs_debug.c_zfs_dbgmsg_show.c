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
struct TYPE_2__ {int /*<<< orphan*/  zdm_msg; scalar_t__ zdm_timestamp; } ;
typedef  TYPE_1__ zfs_dbgmsg_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_dbgmsg_show(struct seq_file *f, void *p)
{
	zfs_dbgmsg_t *zdm = (zfs_dbgmsg_t *)p;
	seq_printf(f, "%-12llu %-s\n",
	    (u_longlong_t)zdm->zdm_timestamp, zdm->zdm_msg);
	return (0);
}