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
struct TYPE_3__ {scalar_t__ tp_magic; void (* tp_func ) (void*) ;int tp_name_size; struct TYPE_3__* tp_name; int /*<<< orphan*/  tp_pri; int /*<<< orphan*/  tp_state; void* tp_args; } ;
typedef  TYPE_1__ thread_priv_t ;
typedef  int /*<<< orphan*/  kthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  PRIO_TO_NICE (int /*<<< orphan*/ ) ; 
 scalar_t__ TP_MAGIC ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
thread_generic_wrapper(void *arg)
{
	thread_priv_t *tp = (thread_priv_t *)arg;
	void (*func)(void *);
	void *args;

	ASSERT(tp->tp_magic == TP_MAGIC);
	func = tp->tp_func;
	args = tp->tp_args;
	set_current_state(tp->tp_state);
	set_user_nice((kthread_t *)current, PRIO_TO_NICE(tp->tp_pri));
	kmem_free(tp->tp_name, tp->tp_name_size);
	kmem_free(tp, sizeof (thread_priv_t));

	if (func)
		func(args);

	return (0);
}