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
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TIOCGPTN ; 
 scalar_t__ asprintf (char**,char*,int) ; 
 int errno ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ptsname_namespace(int pty, char **ret) {
        int no = -1, r;

        /* Like ptsname(), but doesn't assume that the path is
         * accessible in the local namespace. */

        r = ioctl(pty, TIOCGPTN, &no);
        if (r < 0)
                return -errno;

        if (no < 0)
                return -EIO;

        if (asprintf(ret, "/dev/pts/%i", no) < 0)
                return -ENOMEM;

        return 0;
}