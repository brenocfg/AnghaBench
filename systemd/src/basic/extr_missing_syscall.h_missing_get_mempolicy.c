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
 int /*<<< orphan*/  __NR_get_mempolicy ; 
 int /*<<< orphan*/  errno ; 
 long syscall (int /*<<< orphan*/ ,int*,unsigned long*,unsigned long,void*,unsigned long) ; 

__attribute__((used)) static inline long missing_get_mempolicy(int *mode, unsigned long *nodemask,
                           unsigned long maxnode, void *addr,
                           unsigned long flags) {
        long i;
#  ifdef __NR_get_mempolicy
        i = syscall(__NR_get_mempolicy, mode, nodemask, maxnode, addr, flags);
#  else
        errno = ENOSYS;
        i = -1;
#  endif
        return i;
}