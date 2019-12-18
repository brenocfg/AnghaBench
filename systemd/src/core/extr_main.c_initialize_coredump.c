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
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int /*<<< orphan*/  RLIMIT_MAKE_CONST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int /*<<< orphan*/  disable_coredumps () ; 
 int /*<<< orphan*/  errno ; 
 int getpid_cached () ; 
 int /*<<< orphan*/  log_warning_errno (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void initialize_coredump(bool skip_setup) {
#if ENABLE_COREDUMP
        if (getpid_cached() != 1)
                return;

        /* Don't limit the core dump size, so that coredump handlers such as systemd-coredump (which honour the limit)
         * will process core dumps for system services by default. */
        if (setrlimit(RLIMIT_CORE, &RLIMIT_MAKE_CONST(RLIM_INFINITY)) < 0)
                log_warning_errno(errno, "Failed to set RLIMIT_CORE: %m");

        /* But at the same time, turn off the core_pattern logic by default, so that no
         * coredumps are stored until the systemd-coredump tool is enabled via
         * sysctl. However it can be changed via the kernel command line later so core
         * dumps can still be generated during early startup and in initramfs. */
        if (!skip_setup)
                disable_coredumps();
#endif
}