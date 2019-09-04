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
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  XCloseMainDisplay () ; 
 int /*<<< orphan*/ * XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/ * displayName ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ hasDisplayNameChanged ; 
 int /*<<< orphan*/ * mainDisplay ; 
 int registered ; 
 int /*<<< orphan*/  stderr ; 

Display *XGetMainDisplay(void)
{
	/* Close the display if displayName has changed */
	if (hasDisplayNameChanged) {
		XCloseMainDisplay();
		hasDisplayNameChanged = 0;
	}

	if (mainDisplay == NULL) {
		/* First try the user set displayName */
		mainDisplay = XOpenDisplay(displayName);

		/* Then try using environment variable DISPLAY */
		if (mainDisplay == NULL) {
			mainDisplay = XOpenDisplay(NULL);
		}

		if (mainDisplay == NULL) {
			fputs("Could not open main display\n", stderr);
		} else if (!registered) {
			atexit(&XCloseMainDisplay);
			registered = 1;
		}
	}

	return mainDisplay;
}