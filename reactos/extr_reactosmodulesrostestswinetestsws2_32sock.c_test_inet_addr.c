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
typedef  scalar_t__ u_long ;

/* Variables and functions */
 scalar_t__ INADDR_NONE ; 
 scalar_t__ inet_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_inet_addr(void)
{
    u_long addr;

    addr = inet_addr(NULL);
    ok(addr == INADDR_NONE, "inet_addr succeeded unexpectedly\n");
}