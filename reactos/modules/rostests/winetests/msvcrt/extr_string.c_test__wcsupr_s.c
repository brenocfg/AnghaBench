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
 int p_wcsupr_s (char*,int) ; 
 int /*<<< orphan*/  wcscmp (char*,char const*) ; 
 int /*<<< orphan*/  wcscpy (char*,char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__wcsupr_s(void)
{
    static const WCHAR mixedString[] = {'M', 'i', 'X', 'e', 'D', 'l', 'o', 'w',
                                        'e', 'r', 'U', 'P', 'P', 'E', 'R', 0};
    static const WCHAR expectedString[] = {'M', 'I', 'X', 'E', 'D', 'L', 'O',
                                           'W', 'E', 'R', 'U', 'P', 'P', 'E',
                                           'R', 0};
    WCHAR testBuffer[2*ARRAY_SIZE(mixedString)];
    int ret;

    if (!p_wcsupr_s)
    {
        win_skip("_wcsupr_s not found\n");
        return;
    }

    /* Test NULL input string and invalid size. */
    errno = EBADF;
    ret = p_wcsupr_s(NULL, 0);
    ok(ret == EINVAL, "Expected _wcsupr_s to fail with EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    /* Test NULL input string and valid size. */
    errno = EBADF;
    ret = p_wcsupr_s(NULL, ARRAY_SIZE(testBuffer));
    ok(ret == EINVAL, "Expected _wcsupr_s to fail with EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    /* Test empty string with zero size. */
    errno = EBADF;
    testBuffer[0] = '\0';
    ret = p_wcsupr_s(testBuffer, 0);
    ok(ret == EINVAL, "Expected _wcsupr_s to fail with EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(testBuffer[0] == '\0', "Expected the buffer to be unchanged\n");

    /* Test empty string with size of one. */
    testBuffer[0] = '\0';
    ret = p_wcsupr_s(testBuffer, 1);
    ok(ret == 0, "Expected _wcsupr_s to succeed, got %d\n", ret);
    ok(testBuffer[0] == '\0', "Expected the buffer to be unchanged\n");

    /* Test one-byte buffer with zero size. */
    errno = EBADF;
    testBuffer[0] = 'x';
    ret = p_wcsupr_s(testBuffer, 0);
    ok(ret == EINVAL, "Expected _wcsupr_s to fail with EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(testBuffer[0] == '\0', "Expected the first buffer character to be null\n");

    /* Test one-byte buffer with size of one. */
    errno = EBADF;
    testBuffer[0] = 'x';
    ret = p_wcsupr_s(testBuffer, 1);
    ok(ret == EINVAL, "Expected _wcsupr_s to fail with EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(testBuffer[0] == '\0', "Expected the first buffer character to be null\n");

    /* Test invalid size. */
    wcscpy(testBuffer, mixedString);
    errno = EBADF;
    ret = p_wcsupr_s(testBuffer, 0);
    ok(ret == EINVAL, "Expected _wcsupr_s to fail with EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(testBuffer[0] == '\0', "Expected the first buffer character to be null\n");

    /* Test normal string uppercasing. */
    wcscpy(testBuffer, mixedString);
    ret = p_wcsupr_s(testBuffer, ARRAY_SIZE(mixedString));
    ok(ret == 0, "Expected _wcsupr_s to succeed, got %d\n", ret);
    ok(!wcscmp(testBuffer, expectedString), "Expected the string to be fully upper-case\n");

    /* Test uppercasing with a shorter buffer size count. */
    wcscpy(testBuffer, mixedString);
    errno = EBADF;
    ret = p_wcsupr_s(testBuffer, ARRAY_SIZE(mixedString) - 1);
    ok(ret == EINVAL, "Expected _wcsupr_s to fail with EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(testBuffer[0] == '\0', "Expected the first buffer character to be null\n");

    /* Test uppercasing with a longer buffer size count. */
    wcscpy(testBuffer, mixedString);
    ret = p_wcsupr_s(testBuffer, ARRAY_SIZE(testBuffer));
    ok(ret == 0, "Expected _wcsupr_s to succeed, got %d\n", ret);
    ok(!wcscmp(testBuffer, expectedString), "Expected the string to be fully upper-case\n");
}