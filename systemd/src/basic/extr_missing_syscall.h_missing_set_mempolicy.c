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
 int /*<<< orphan*/  __NR_set_mempolicy ; 
 int /*<<< orphan*/  errno ; 
 long syscall (int /*<<< orphan*/ ,int,unsigned long const*,unsigned long) ; 

__attribute__((used)) static inline long missing_set_mempolicy(int mode, const unsigned long *nodemask,
                           unsigned long maxnode) {
        long i;
#  if defined __NR_set_mempolicy && __NR_set_mempolicy > 0
        i = syscall(__NR_set_mempolicy, mode, nodemask, maxnode);
#  else
        errno = ENOSYS;
        i = -1;
#  endif
        return i;
}