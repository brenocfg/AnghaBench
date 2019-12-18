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
struct timer_list {long expires; } ;
struct spl_task_timer {int /*<<< orphan*/  task; struct timer_list timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cv_wakeup ; 
 int /*<<< orphan*/  add_timer (struct timer_list*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  del_timer_sync (struct timer_list*) ; 
 int /*<<< orphan*/  io_schedule () ; 
 long jiffies ; 
 int /*<<< orphan*/  timer_setup (struct timer_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long
spl_io_schedule_timeout(long time_left)
{
	long expire_time = jiffies + time_left;
	struct spl_task_timer task_timer;
	struct timer_list *timer = &task_timer.timer;

	task_timer.task = current;

	timer_setup(timer, __cv_wakeup, 0);

	timer->expires = expire_time;
	add_timer(timer);

	io_schedule();

	del_timer_sync(timer);

	time_left = expire_time - jiffies;

	return (time_left < 0 ? 0 : time_left);
}