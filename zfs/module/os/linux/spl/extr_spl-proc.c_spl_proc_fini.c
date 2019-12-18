#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * proc_spl ; 
 int /*<<< orphan*/ * proc_spl_kmem ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spl_header ; 
 int /*<<< orphan*/  unregister_sysctl_table (int /*<<< orphan*/ *) ; 

void
spl_proc_fini(void)
{
	remove_proc_entry("kstat", proc_spl);
	remove_proc_entry("slab", proc_spl_kmem);
	remove_proc_entry("kmem", proc_spl);
	remove_proc_entry("taskq-all", proc_spl);
	remove_proc_entry("taskq", proc_spl);
	remove_proc_entry("spl", NULL);

	ASSERT(spl_header != NULL);
	unregister_sysctl_table(spl_header);
}