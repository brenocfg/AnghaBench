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
 int EUNATCH ; 
 void* proc_create_data (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* proc_mkdir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_slab_operations ; 
 int /*<<< orphan*/ * proc_spl ; 
 int /*<<< orphan*/ * proc_spl_kmem ; 
 int /*<<< orphan*/ * proc_spl_kmem_slab ; 
 int /*<<< orphan*/ * proc_spl_kstat ; 
 int /*<<< orphan*/ * proc_spl_taskq ; 
 int /*<<< orphan*/ * proc_spl_taskq_all ; 
 int /*<<< orphan*/  proc_taskq_all_operations ; 
 int /*<<< orphan*/  proc_taskq_operations ; 
 int /*<<< orphan*/ * register_sysctl_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spl_header ; 
 int /*<<< orphan*/  spl_root ; 
 int /*<<< orphan*/  unregister_sysctl_table (int /*<<< orphan*/ *) ; 

int
spl_proc_init(void)
{
	int rc = 0;

	spl_header = register_sysctl_table(spl_root);
	if (spl_header == NULL)
		return (-EUNATCH);

	proc_spl = proc_mkdir("spl", NULL);
	if (proc_spl == NULL) {
		rc = -EUNATCH;
		goto out;
	}

	proc_spl_taskq_all = proc_create_data("taskq-all", 0444, proc_spl,
	    &proc_taskq_all_operations, NULL);
	if (proc_spl_taskq_all == NULL) {
		rc = -EUNATCH;
		goto out;
	}

	proc_spl_taskq = proc_create_data("taskq", 0444, proc_spl,
	    &proc_taskq_operations, NULL);
	if (proc_spl_taskq == NULL) {
		rc = -EUNATCH;
		goto out;
	}

	proc_spl_kmem = proc_mkdir("kmem", proc_spl);
	if (proc_spl_kmem == NULL) {
		rc = -EUNATCH;
		goto out;
	}

	proc_spl_kmem_slab = proc_create_data("slab", 0444, proc_spl_kmem,
	    &proc_slab_operations, NULL);
	if (proc_spl_kmem_slab == NULL) {
		rc = -EUNATCH;
		goto out;
	}

	proc_spl_kstat = proc_mkdir("kstat", proc_spl);
	if (proc_spl_kstat == NULL) {
		rc = -EUNATCH;
		goto out;
	}
out:
	if (rc) {
		remove_proc_entry("kstat", proc_spl);
		remove_proc_entry("slab", proc_spl_kmem);
		remove_proc_entry("kmem", proc_spl);
		remove_proc_entry("taskq-all", proc_spl);
		remove_proc_entry("taskq", proc_spl);
		remove_proc_entry("spl", NULL);
		unregister_sysctl_table(spl_header);
	}

	return (rc);
}