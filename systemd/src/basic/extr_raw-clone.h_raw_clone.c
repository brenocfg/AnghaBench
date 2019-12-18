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
typedef  int pid_t ;

/* Variables and functions */
 unsigned long CLONE_CHILD_CLEARTID ; 
 unsigned long CLONE_CHILD_SETTID ; 
 unsigned long CLONE_PARENT_SETTID ; 
 unsigned long CLONE_SETTLS ; 
 unsigned long CLONE_VM ; 
 int /*<<< orphan*/  __NR_clone ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int /*<<< orphan*/  reset_cached_pid () ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static inline pid_t raw_clone(unsigned long flags) {
        pid_t ret;

        assert((flags & (CLONE_VM|CLONE_PARENT_SETTID|CLONE_CHILD_SETTID|
                         CLONE_CHILD_CLEARTID|CLONE_SETTLS)) == 0);
#if defined(__s390x__) || defined(__s390__) || defined(__CRIS__)
        /* On s390/s390x and cris the order of the first and second arguments
         * of the raw clone() system call is reversed. */
        ret = (pid_t) syscall(__NR_clone, NULL, flags);
#elif defined(__sparc__)
        {
                /**
                 * sparc always returns the other process id in %o0, and
                 * a boolean flag whether this is the child or the parent in
                 * %o1. Inline assembly is needed to get the flag returned
                 * in %o1.
                 */
                int in_child, child_pid, error;

                asm volatile("mov %3, %%g1\n\t"
                             "mov %4, %%o0\n\t"
                             "mov 0 , %%o1\n\t"
#if defined(__arch64__)
                             "t 0x6d\n\t"
#else
                             "t 0x10\n\t"
#endif
                             "addx %%g0, 0, %2\n\t"
                             "mov %%o1, %0\n\t"
                             "mov %%o0, %1" :
                             "=r"(in_child), "=r"(child_pid), "=r"(error) :
                             "i"(__NR_clone), "r"(flags) :
                             "%o1", "%o0", "%g1", "cc" );

                if (error) {
                        errno = child_pid;
                        ret = -1;
                } else
                        ret = in_child ? 0 : child_pid;
        }
#else
        ret = (pid_t) syscall(__NR_clone, flags, NULL);
#endif

        if (ret == 0)
                reset_cached_pid();

        return ret;
}