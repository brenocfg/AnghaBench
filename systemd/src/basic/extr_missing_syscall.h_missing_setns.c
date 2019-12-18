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
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  __NR_setns ; 
 int /*<<< orphan*/  errno ; 
 int syscall (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int missing_setns(int fd, int nstype) {
#  ifdef __NR_setns
        return syscall(__NR_setns, fd, nstype);
#  else
        errno = ENOSYS;
        return -1;
#  endif
}