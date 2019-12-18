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
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __NR_futex ; 
 int syscall (int /*<<< orphan*/ ,void*,int,unsigned int,struct timespec const*,void*,int) ; 

__attribute__((used)) static int sys_futex(void *addr, int op, unsigned val,
                     const struct timespec *to, void *addr2, int val3)
{
    return syscall(__NR_futex, addr, op, val, to, addr2, val3);
}