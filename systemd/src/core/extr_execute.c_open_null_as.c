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
 int O_NOCTTY ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int move_fd (int,int,int) ; 
 int open (char*,int) ; 

__attribute__((used)) static int open_null_as(int flags, int nfd) {
        int fd;

        assert(nfd >= 0);

        fd = open("/dev/null", flags|O_NOCTTY);
        if (fd < 0)
                return -errno;

        return move_fd(fd, nfd, false);
}