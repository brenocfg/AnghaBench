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
 int EINVAL ; 
 int _NLSCMPERROR ; 
 int errno ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int p__memicmp_l (char const*,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__memicmp_l(void)
{
    static const char *s1 = "abc";
    static const char *s2 = "aBd";
    int ret;

    if (!p__memicmp_l)
    {
        win_skip("_memicmp_l not found.\n");
        return;
    }

    errno = 0xdeadbeef;
    ret = p__memicmp_l(NULL, NULL, 0, NULL);
    ok(!ret, "got %d\n", ret);
    ok(errno == 0xdeadbeef, "errno is %d, expected 0xdeadbeef\n", errno);

    errno = 0xdeadbeef;
    ret = p__memicmp_l(NULL, NULL, 1, NULL);
    ok(ret == _NLSCMPERROR, "got %d\n", ret);
    ok(errno == EINVAL, "errno is %d, expected EINVAL\n", errno);

    errno = 0xdeadbeef;
    ret = p__memicmp_l(s1, NULL, 1, NULL);
    ok(ret == _NLSCMPERROR, "got %d\n", ret);
    ok(errno == EINVAL, "errno is %d, expected EINVAL\n", errno);

    errno = 0xdeadbeef;
    ret = p__memicmp_l(NULL, s2, 1, NULL);
    ok(ret == _NLSCMPERROR, "got %d\n", ret);
    ok(errno == EINVAL, "errno is %d, expected EINVAL\n", errno);

    errno = 0xdeadbeef;
    ret = p__memicmp_l(s1, s2, 2, NULL);
    ok(!ret, "got %d\n", ret);
    ok(errno == 0xdeadbeef, "errno is %d, expected 0xdeadbeef\n", errno);

    errno = 0xdeadbeef;
    ret = p__memicmp_l(s1, s2, 3, NULL);
    ok(ret == -1, "got %d\n", ret);
    ok(errno == 0xdeadbeef, "errno is %d, expected 0xdeadbeef\n", errno);
}