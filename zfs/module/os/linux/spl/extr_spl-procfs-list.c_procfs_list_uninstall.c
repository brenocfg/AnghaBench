#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pl_kstat_entry; } ;
typedef  TYPE_1__ procfs_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  kstat_proc_entry_delete (int /*<<< orphan*/ *) ; 

void
procfs_list_uninstall(procfs_list_t *procfs_list)
{
	kstat_proc_entry_delete(&procfs_list->pl_kstat_entry);
}