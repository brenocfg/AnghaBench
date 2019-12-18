#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ksm_module_list; int /*<<< orphan*/  ksm_name; int /*<<< orphan*/  ksm_kstat_list; } ;
typedef  TYPE_1__ kstat_module_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_spl_kstat ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kstat_delete_module(kstat_module_t *module)
{
	ASSERT(list_empty(&module->ksm_kstat_list));
	remove_proc_entry(module->ksm_name, proc_spl_kstat);
	list_del(&module->ksm_module_list);
	kmem_free(module, sizeof (kstat_module_t));
}