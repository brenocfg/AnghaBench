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
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  EVIOCREVOKE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_warning_errno (scalar_t__,char*) ; 

__attribute__((used)) static void sd_eviocrevoke(int fd) {
        static bool warned = false;

        assert(fd >= 0);

        if (ioctl(fd, EVIOCREVOKE, NULL) < 0) {

                if (errno == EINVAL && !warned) {
                        log_warning_errno(errno, "Kernel does not support evdev-revocation: %m");
                        warned = true;
                }
        }
}