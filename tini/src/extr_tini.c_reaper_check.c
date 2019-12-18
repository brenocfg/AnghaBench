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
 int /*<<< orphan*/  PRINT_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PR_GET_CHILD_SUBREAPER ; 
 int /*<<< orphan*/  errno ; 
 int getpid () ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  reaper_warning ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void reaper_check () {
	/* Check that we can properly reap zombies */
#if HAS_SUBREAPER
	int bit = 0;
#endif

	if (getpid() == 1) {
		return;
	}

#if HAS_SUBREAPER
	if (prctl(PR_GET_CHILD_SUBREAPER, &bit)) {
		PRINT_DEBUG("Failed to read child subreaper attribute: %s", strerror(errno));
	} else if (bit == 1) {
		return;
	}
#endif

	PRINT_WARNING(reaper_warning);
}