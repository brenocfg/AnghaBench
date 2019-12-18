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
 scalar_t__ ENOTTY ; 
 scalar_t__ ENXIO ; 
 int /*<<< orphan*/  PRINT_DEBUG (char*) ; 
 int /*<<< orphan*/  PRINT_FATAL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  getpgrp () ; 
 scalar_t__ setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ tcsetpgrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int isolate_child() {
	// Put the child into a new process group.
	if (setpgid(0, 0) < 0) {
		PRINT_FATAL("setpgid failed: %s", strerror(errno));
		return 1;
	}

	// If there is a tty, allocate it to this new process group. We
	// can do this in the child process because we're blocking
	// SIGTTIN / SIGTTOU.

	// Doing it in the child process avoids a race condition scenario
	// if Tini is calling Tini (in which case the grandparent may make the
	// parent the foreground process group, and the actual child ends up...
	// in the background!)
	if (tcsetpgrp(STDIN_FILENO, getpgrp())) {
		if (errno == ENOTTY) {
			PRINT_DEBUG("tcsetpgrp failed: no tty (ok to proceed)");
		} else if (errno == ENXIO) {
			// can occur on lx-branded zones
			PRINT_DEBUG("tcsetpgrp failed: no such device (ok to proceed)");
		} else {
			PRINT_FATAL("tcsetpgrp failed: %s", strerror(errno));
			return 1;
		}
	}

	return 0;
}