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
typedef  int /*<<< orphan*/  uid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTTY ; 
 scalar_t__ IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTY_MODE ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int fchmod_and_chown (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int isatty (int) ; 

__attribute__((used)) static int chown_terminal(int fd, uid_t uid) {
        int r;

        assert(fd >= 0);

        /* Before we chown/chmod the TTY, let's ensure this is actually a tty */
        if (isatty(fd) < 1) {
                if (IN_SET(errno, EINVAL, ENOTTY))
                        return 0; /* not a tty */

                return -errno;
        }

        /* This might fail. What matters are the results. */
        r = fchmod_and_chown(fd, TTY_MODE, uid, -1);
        if (r < 0)
                return r;

        return 1;
}