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
 scalar_t__ DECIMAL_STR_MAX (int) ; 
 scalar_t__ STRLEN (char*) ; 
 int access (char*,int) ; 
 int errno ; 
 int /*<<< orphan*/  xsprintf (char*,char*,int) ; 

int access_fd(int fd, int mode) {
        char p[STRLEN("/proc/self/fd/") + DECIMAL_STR_MAX(fd) + 1];
        int r;

        /* Like access() but operates on an already open fd */

        xsprintf(p, "/proc/self/fd/%i", fd);
        r = access(p, mode);
        if (r < 0)
                return -errno;

        return r;
}