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
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIGSEGV ; 
 void** __pxcptinfoptrs () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sighandler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_value ; 

__attribute__((used)) static void test___pxcptinfoptrs(void)
{
    void **ret = __pxcptinfoptrs();
    int res;

    ok(ret != NULL, "ret == NULL\n");
    ok(*ret == NULL, "*ret != NULL\n");

    test_value = 0;

    *ret = (void*)0xdeadbeef;
    signal(SIGSEGV, sighandler);
    res = raise(SIGSEGV);
    ok(res == 0, "failed to raise SIGSEGV\n");
    ok(*ret == (void*)0xdeadbeef, "*ret = %p\n", *ret);

    signal(SIGABRT, sighandler);
    res = raise(SIGABRT);
    ok(res == 0, "failed to raise SIGBREAK\n");
    ok(*ret == (void*)0xdeadbeef, "*ret = %p\n", *ret);

    ok(test_value == 2, "test_value = %d\n", test_value);
}