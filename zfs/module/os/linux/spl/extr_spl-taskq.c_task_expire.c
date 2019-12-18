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
typedef  int /*<<< orphan*/  taskq_ent_t ;
struct timer_list {int dummy; } ;
typedef  scalar_t__ spl_timer_list_t ;

/* Variables and functions */
 int /*<<< orphan*/ * from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * t ; 
 int /*<<< orphan*/  task_expire_impl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tqent_timer ; 

__attribute__((used)) static void
task_expire(spl_timer_list_t tl)
{
	struct timer_list *tmr = (struct timer_list *)tl;
	taskq_ent_t *t = from_timer(t, tmr, tqent_timer);
	task_expire_impl(t);
}