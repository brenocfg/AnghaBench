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
 int /*<<< orphan*/  F_LOCK ; 
 int errno ; 
 scalar_t__ lockf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lockfp(int fd, int *fd_lock) {
        if (lockf(fd, F_LOCK, 0) < 0)
                return -errno;
        *fd_lock = fd;
        return 0;
}