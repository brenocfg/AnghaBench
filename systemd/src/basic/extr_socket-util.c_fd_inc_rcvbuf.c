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
typedef  int /*<<< orphan*/  value ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_RCVBUFFORCE ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int setsockopt_int (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

int fd_inc_rcvbuf(int fd, size_t n) {
        int r, value;
        socklen_t l = sizeof(value);

        r = getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &value, &l);
        if (r >= 0 && l == sizeof(value) && (size_t) value >= n*2)
                return 0;

        /* If we have the privileges we will ignore the kernel limit. */

        if (setsockopt_int(fd, SOL_SOCKET, SO_RCVBUF, n) < 0) {
                r = setsockopt_int(fd, SOL_SOCKET, SO_RCVBUFFORCE, n);
                if (r < 0)
                        return r;
        }

        return 1;
}