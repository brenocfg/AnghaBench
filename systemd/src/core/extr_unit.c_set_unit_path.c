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
 int errno ; 
 scalar_t__ setenv (char*,char const*,int) ; 

int set_unit_path(const char *p) {
        /* This is mostly for debug purposes */
        if (setenv("SYSTEMD_UNIT_PATH", p, 1) < 0)
                return -errno;

        return 0;
}