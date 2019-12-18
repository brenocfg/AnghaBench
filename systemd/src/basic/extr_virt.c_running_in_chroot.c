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
 int files_same (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ getenv_bool (char*) ; 

int running_in_chroot(void) {
        int r;

        if (getenv_bool("SYSTEMD_IGNORE_CHROOT") > 0)
                return 0;

        r = files_same("/proc/1/root", "/", 0);
        if (r < 0)
                return r;

        return r == 0;
}