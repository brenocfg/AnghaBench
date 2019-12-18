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
 int /*<<< orphan*/  test_allocateLuid () ; 
 int /*<<< orphan*/  test_lookupPrivilegeName () ; 
 int /*<<< orphan*/  test_lookupPrivilegeValue () ; 

__attribute__((used)) static void test_luid(void)
{
    test_allocateLuid();
    test_lookupPrivilegeName();
    test_lookupPrivilegeValue();
}