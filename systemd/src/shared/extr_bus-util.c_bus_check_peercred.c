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
struct ucred {scalar_t__ uid; } ;
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ geteuid () ; 
 int getpeercred (int,struct ucred*) ; 
 int sd_bus_get_fd (int /*<<< orphan*/ *) ; 

int bus_check_peercred(sd_bus *c) {
        struct ucred ucred;
        int fd, r;

        assert(c);

        fd = sd_bus_get_fd(c);
        if (fd < 0)
                return fd;

        r = getpeercred(fd, &ucred);
        if (r < 0)
                return r;

        if (ucred.uid != 0 && ucred.uid != geteuid())
                return -EPERM;

        return 1;
}