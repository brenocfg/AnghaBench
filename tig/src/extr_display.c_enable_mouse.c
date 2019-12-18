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
typedef  int /*<<< orphan*/  mmask_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_MOUSE_EVENTS ; 
 int /*<<< orphan*/  mouseinterval (int /*<<< orphan*/ ) ; 
 scalar_t__ mousemask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
enable_mouse(bool enable)
{
#ifdef NCURSES_MOUSE_VERSION
	static bool enabled = false;

	if (enable != enabled) {
		mmask_t mask = enable ? ALL_MOUSE_EVENTS : 0;

		if (mousemask(mask, NULL))
			mouseinterval(0);
		enabled = enable;
	}
#endif
}