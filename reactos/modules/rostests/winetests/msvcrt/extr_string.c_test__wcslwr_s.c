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
typedef  char WCHAR ;

/* Variables and functions */
 int ARRAY_SIZE (char const*) ; 
 int EBADF ; 
 int EINVAL ; 
 int errno ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int p_wcslwr_s (char*,int) ; 
 int /*<<< orphan*/  wcscmp (char*,char const*) ; 
 int /*<<< orphan*/  wcscpy (char*,char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__wcslwr_s(void)
{
    static const WCHAR mixedString[] = {'M', 'i', 'X', 'e', 'D', 'l', 'o', 'w',
                                        'e', 'r', 'U', 'P', 'P', 'E', 'R', 0};
    static const WCHAR expectedString[] = {'m', 'i', 'x', 'e', 'd', 'l', 'o',
                                           'w', 'e', 'r', 'u', 'p', 'p', 'e',
                                           'r', 0};
    WCHAR buffer[2*ARRAY_SIZE(mixedString)];
    int ret;

    if (!p_wcslwr_s)
    {
        win_skip("_wcslwr_s not found\n");
        return;
    }

    /* Test NULL input string and invalid size. */
    errno = EBADF;
    ret = p_wcslwr_s(NULL, 0);
    ok(ret == EINVAL, "expected EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "expected errno EINVAL, got %d\n", errno);

    /* Test NULL input string and valid size. */
    errno = EBADF;
    ret = p_wcslwr_s(NULL, ARRAY_SIZE(buffer));
    ok(ret == EINVAL, "expected EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "expected errno EINVAL, got %d\n", errno);

    /* Test empty string with zero size. */
    errno = EBADF;
    buffer[0] = 'a';
    ret = p_wcslwr_s(buffer, 0);
    ok(ret == EINVAL, "expected EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "expected errno EINVAL, got %d\n", errno);
    ok(buffer[0] == 0, "expected empty string\n");

    /* Test empty string with size of one. */
    buffer[0] = 0;
    ret = p_wcslwr_s(buffer, 1);
    ok(ret == 0, "got %d\n", ret);
    ok(buffer[0] == 0, "expected buffer to be unchanged\n");

    /* Test one-byte buffer with zero size. */
    errno = EBADF;
    buffer[0] = 'x';
    ret = p_wcslwr_s(buffer, 0);
    ok(ret == EINVAL, "expected EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "expected errno to be EINVAL, got %d\n", errno);
    ok(buffer[0] == '\0', "expected empty string\n");

    /* Test one-byte buffer with size of one. */
    errno = EBADF;
    buffer[0] = 'x';
    ret = p_wcslwr_s(buffer, 1);
    ok(ret == EINVAL, "expected EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "expected errno to be EINVAL, got %d\n", errno);
    ok(buffer[0] == '\0', "expected empty string\n");

    /* Test invalid size. */
    wcscpy(buffer, mixedString);
    errno = EBADF;
    ret = p_wcslwr_s(buffer, 0);
    ok(ret == EINVAL, "Expected EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "expected errno to be EINVAL, got %d\n", errno);
    ok(buffer[0] == '\0', "expected empty string\n");

    /* Test normal string uppercasing. */
    wcscpy(buffer, mixedString);
    ret = p_wcslwr_s(buffer, ARRAY_SIZE(mixedString));
    ok(ret == 0, "expected 0, got %d\n", ret);
    ok(!wcscmp(buffer, expectedString), "expected lowercase\n");

    /* Test uppercasing with a shorter buffer size count. */
    wcscpy(buffer, mixedString);
    errno = EBADF;
    ret = p_wcslwr_s(buffer, ARRAY_SIZE(mixedString) - 1);
    ok(ret == EINVAL, "expected EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "expected errno to be EINVAL, got %d\n", errno);
    ok(buffer[0] == '\0', "expected empty string\n");

    /* Test uppercasing with a longer buffer size count. */
    wcscpy(buffer, mixedString);
    ret = p_wcslwr_s(buffer, ARRAY_SIZE(buffer));
    ok(ret == 0, "expected 0, got %d\n", ret);
    ok(!wcscmp(buffer, expectedString), "expected lowercase\n");
}