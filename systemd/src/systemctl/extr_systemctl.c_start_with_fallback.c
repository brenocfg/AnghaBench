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
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  action_to_runlevel () ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ start_unit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ talk_initctl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_with_fallback(void) {
        /* First, try systemd via D-Bus. */
        if (start_unit(0, NULL, NULL) == 0)
                return 0;

#if HAVE_SYSV_COMPAT
        /* Nothing else worked, so let's try /dev/initctl */
        if (talk_initctl(action_to_runlevel()) > 0)
                return 0;
#endif

        return log_error_errno(SYNTHETIC_ERRNO(EIO),
                               "Failed to talk to init daemon.");
}