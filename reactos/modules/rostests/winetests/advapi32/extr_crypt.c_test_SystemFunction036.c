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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pSystemFunction036 (int*,int) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SystemFunction036(void)
{
    BOOL ret;
    int test;

    if (!pSystemFunction036)
    {
        win_skip("SystemFunction036 is not available\n");
        return;
    }

    ret = pSystemFunction036(NULL, 0);
    ok(ret == TRUE, "Expected SystemFunction036 to return TRUE, got %d\n", ret);

    /* Test crashes on Windows. */
    if (0)
    {
        SetLastError(0xdeadbeef);
        ret = pSystemFunction036(NULL, 5);
        trace("ret = %d, GetLastError() = %d\n", ret, GetLastError());
    }

    ret = pSystemFunction036(&test, 0);
    ok(ret == TRUE, "Expected SystemFunction036 to return TRUE, got %d\n", ret);

    ret = pSystemFunction036(&test, sizeof(int));
    ok(ret == TRUE, "Expected SystemFunction036 to return TRUE, got %d\n", ret);
}