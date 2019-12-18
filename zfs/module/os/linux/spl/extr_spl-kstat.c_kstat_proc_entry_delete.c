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
struct TYPE_5__ {scalar_t__ kpe_proc; int /*<<< orphan*/  kpe_list; int /*<<< orphan*/  kpe_name; TYPE_2__* kpe_owner; } ;
typedef  TYPE_1__ kstat_proc_entry_t ;
struct TYPE_6__ {int /*<<< orphan*/  ksm_kstat_list; int /*<<< orphan*/  ksm_proc; } ;
typedef  TYPE_2__ kstat_module_t ;

/* Variables and functions */
 int /*<<< orphan*/  kstat_delete_module (TYPE_2__*) ; 
 int /*<<< orphan*/  kstat_module_lock ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kstat_proc_entry_delete(kstat_proc_entry_t *kpep)
{
	kstat_module_t *module = kpep->kpe_owner;
	if (kpep->kpe_proc)
		remove_proc_entry(kpep->kpe_name, module->ksm_proc);

	mutex_enter(&kstat_module_lock);
	list_del_init(&kpep->kpe_list);

	/*
	 * Remove top level module directory if it wasn't empty before, but now
	 * is.
	 */
	if (kpep->kpe_proc && list_empty(&module->ksm_kstat_list))
		kstat_delete_module(module);
	mutex_exit(&kstat_module_lock);

}