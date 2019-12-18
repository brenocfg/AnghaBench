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
typedef  int /*<<< orphan*/  FDSet ;

/* Variables and functions */
 int /*<<< orphan*/  F_DUPFD_CLOEXEC ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int fdset_put (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  safe_close (int) ; 

int fdset_put_dup(FDSet *s, int fd) {
        int copy, r;

        assert(s);
        assert(fd >= 0);

        copy = fcntl(fd, F_DUPFD_CLOEXEC, 3);
        if (copy < 0)
                return -errno;

        r = fdset_put(s, copy);
        if (r < 0) {
                safe_close(copy);
                return r;
        }

        return copy;
}