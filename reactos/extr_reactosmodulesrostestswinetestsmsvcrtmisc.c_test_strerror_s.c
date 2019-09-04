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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int errno ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pstrerror_s (char*,int,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_strerror_s(void)
{
    int ret;
    char buf[256];

    if (!pstrerror_s)
    {
        win_skip("strerror_s is not available\n");
        return;
    }

    errno = EBADF;
    ret = pstrerror_s(NULL, 0, 0);
    ok(ret == EINVAL, "Expected strerror_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    errno = EBADF;
    ret = pstrerror_s(NULL, sizeof(buf), 0);
    ok(ret == EINVAL, "Expected strerror_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    memset(buf, 'X', sizeof(buf));
    errno = EBADF;
    ret = pstrerror_s(buf, 0, 0);
    ok(ret == EINVAL, "Expected strerror_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(buf[0] == 'X', "Expected output buffer to be untouched\n");

    memset(buf, 'X', sizeof(buf));
    ret = pstrerror_s(buf, 1, 0);
    ok(ret == 0, "Expected strerror_s to return 0, got %d\n", ret);
    ok(strlen(buf) == 0, "Expected output buffer to be null terminated\n");

    memset(buf, 'X', sizeof(buf));
    ret = pstrerror_s(buf, 2, 0);
    ok(ret == 0, "Expected strerror_s to return 0, got %d\n", ret);
    ok(strlen(buf) == 1, "Expected output buffer to be truncated\n");

    memset(buf, 'X', sizeof(buf));
    ret = pstrerror_s(buf, sizeof(buf), 0);
    ok(ret == 0, "Expected strerror_s to return 0, got %d\n", ret);

    memset(buf, 'X', sizeof(buf));
    ret = pstrerror_s(buf, sizeof(buf), -1);
    ok(ret == 0, "Expected strerror_s to return 0, got %d\n", ret);
}