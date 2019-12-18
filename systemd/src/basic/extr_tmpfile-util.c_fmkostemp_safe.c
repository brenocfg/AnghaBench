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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/ * fdopen (int,char const*) ; 
 int mkostemp_safe (char*) ; 
 int /*<<< orphan*/  safe_close (int) ; 

int fmkostemp_safe(char *pattern, const char *mode, FILE **ret_f) {
        int fd;
        FILE *f;

        fd = mkostemp_safe(pattern);
        if (fd < 0)
                return fd;

        f = fdopen(fd, mode);
        if (!f) {
                safe_close(fd);
                return -errno;
        }

        *ret_f = f;
        return 0;
}