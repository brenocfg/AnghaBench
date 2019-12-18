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
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int ZVOL_HT_SIZE ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_taskq ; 
 int /*<<< orphan*/  taskq_wait_outstanding (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_htable ; 
 int /*<<< orphan*/  zvol_remove_minors_impl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zvol_state_list ; 
 int /*<<< orphan*/  zvol_state_lock ; 

void
zvol_fini_impl(void)
{
	zvol_remove_minors_impl(NULL);

	/*
	 * The call to "zvol_remove_minors_impl" may dispatch entries to
	 * the system_taskq, but it doesn't wait for those entires to
	 * complete before it returns. Thus, we must wait for all of the
	 * removals to finish, before we can continue.
	 */
	taskq_wait_outstanding(system_taskq, 0);

	kmem_free(zvol_htable, ZVOL_HT_SIZE * sizeof (struct hlist_head));
	list_destroy(&zvol_state_list);
	rw_destroy(&zvol_state_lock);
}