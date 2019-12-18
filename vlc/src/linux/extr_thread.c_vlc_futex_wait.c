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
 int /*<<< orphan*/  FUTEX_WAIT_PRIVATE ; 
 int sys_futex (void*,int /*<<< orphan*/ ,unsigned int,struct timespec const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlc_futex_wait(void *addr, unsigned val, const struct timespec *to)
{
    return sys_futex(addr, FUTEX_WAIT_PRIVATE, val, to, NULL, 0);
}