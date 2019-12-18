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
struct watchdog_info {int /*<<< orphan*/  firmware_version; int /*<<< orphan*/  identity; } ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  WDIOC_GETSUPPORT ; 
 int errno ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,struct watchdog_info*) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ open (char*,int) ; 
 int update_timeout () ; 
 scalar_t__ watchdog_device ; 
 scalar_t__ watchdog_fd ; 

__attribute__((used)) static int open_watchdog(void) {
        struct watchdog_info ident;

        if (watchdog_fd >= 0)
                return 0;

        watchdog_fd = open(watchdog_device ?: "/dev/watchdog",
                           O_WRONLY|O_CLOEXEC);
        if (watchdog_fd < 0)
                return -errno;

        if (ioctl(watchdog_fd, WDIOC_GETSUPPORT, &ident) >= 0)
                log_info("Hardware watchdog '%s', version %x",
                         ident.identity,
                         ident.firmware_version);

        return update_timeout();
}