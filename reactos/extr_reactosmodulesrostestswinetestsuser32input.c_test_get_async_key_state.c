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
 scalar_t__ GetAsyncKeyState (int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_get_async_key_state(void)
{
    /* input value sanity checks */
    ok(0 == GetAsyncKeyState(1000000), "GetAsyncKeyState did not return 0\n");
    ok(0 == GetAsyncKeyState(-1000000), "GetAsyncKeyState did not return 0\n");
}