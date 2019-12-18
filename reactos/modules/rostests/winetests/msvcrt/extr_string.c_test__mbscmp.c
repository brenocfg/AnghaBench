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
 int INT_MAX ; 
 int _mbscmp (unsigned char const*,unsigned char const*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  p_mbrlen ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__mbscmp(void)
{
    static const unsigned char a[] = {'a',0}, b[] = {'b',0};
    int ret;

    if (!p_mbrlen)
    {
        win_skip("_mbscmp tests\n");
        return;
    }

    ret = _mbscmp(NULL, NULL);
    ok(ret == INT_MAX, "got %d\n", ret);

    ret = _mbscmp(a, NULL);
    ok(ret == INT_MAX, "got %d\n", ret);

    ret = _mbscmp(NULL, a);
    ok(ret == INT_MAX, "got %d\n", ret);

    ret = _mbscmp(a, a);
    ok(!ret, "got %d\n", ret);

    ret = _mbscmp(a, b);
    ok(ret == -1, "got %d\n", ret);

    ret = _mbscmp(b, a);
    ok(ret == 1, "got %d\n", ret);
}