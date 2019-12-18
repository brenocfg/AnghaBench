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
 int /*<<< orphan*/  glutTimerFunc (int,void (*) (int),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reload () ; 
 scalar_t__ reloadrequested ; 
 int /*<<< orphan*/  ui_invalidate () ; 

__attribute__((used)) static void on_timer(int timer_id)
{
	if (reloadrequested)
	{
		reload();
		ui_invalidate();
		reloadrequested = 0;
	}
	glutTimerFunc(500, on_timer, 0);
}