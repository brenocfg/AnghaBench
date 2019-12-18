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
typedef  scalar_t__ errno_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ p_ultoa_s (int,char*,int,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__ultoa_s(void)
{
    errno_t ret;
    char buffer[33];

    if (!p_ultoa_s)
    {
        win_skip("Skipping _ultoa_s tests\n");
        return;
    }

    errno = EBADF;
    ret = p_ultoa_s(0, NULL, 0, 0);
    ok(ret == EINVAL, "Expected _ultoa_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    memset(buffer, 'X', sizeof(buffer));
    errno = EBADF;
    ret = p_ultoa_s(0, buffer, 0, 0);
    ok(ret == EINVAL, "Expected _ultoa_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(buffer[0] == 'X', "Expected the output buffer to be untouched\n");

    memset(buffer, 'X', sizeof(buffer));
    errno = EBADF;
    ret = p_ultoa_s(0, buffer, sizeof(buffer), 0);
    ok(ret == EINVAL, "Expected _ultoa_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(buffer[0] == '\0', "Expected the output buffer to be null terminated\n");

    memset(buffer, 'X', sizeof(buffer));
    errno = EBADF;
    ret = p_ultoa_s(0, buffer, sizeof(buffer), 64);
    ok(ret == EINVAL, "Expected _ultoa_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(buffer[0] == '\0', "Expected the output buffer to be null terminated\n");

    memset(buffer, 'X', sizeof(buffer));
    errno = EBADF;
    ret = p_ultoa_s(12345678, buffer, 4, 10);
    ok(ret == ERANGE, "Expected _ultoa_s to return ERANGE, got %d\n", ret);
    ok(errno == ERANGE, "Expected errno to be ERANGE, got %d\n", errno);
    ok(!memcmp(buffer, "\000765", 4),
       "Expected the output buffer to be null terminated with truncated output\n");

    memset(buffer, 'X', sizeof(buffer));
    errno = EBADF;
    ret = p_ultoa_s(12345678, buffer, 8, 10);
    ok(ret == ERANGE, "Expected _ultoa_s to return ERANGE, got %d\n", ret);
    ok(errno == ERANGE, "Expected errno to be ERANGE, got %d\n", errno);
    ok(!memcmp(buffer, "\0007654321", 8),
       "Expected the output buffer to be null terminated with truncated output\n");

    ret = p_ultoa_s(12345678, buffer, 9, 10);
    ok(ret == 0, "Expected _ultoa_s to return 0, got %d\n", ret);
    ok(!strcmp(buffer, "12345678"),
       "Expected output buffer string to be \"12345678\", got \"%s\"\n",
       buffer);

    ret = p_ultoa_s(43690, buffer, sizeof(buffer), 2);
    ok(ret == 0, "Expected _ultoa_s to return 0, got %d\n", ret);
    ok(!strcmp(buffer, "1010101010101010"),
       "Expected output buffer string to be \"1010101010101010\", got \"%s\"\n",
       buffer);

    ret = p_ultoa_s(1092009, buffer, sizeof(buffer), 36);
    ok(ret == 0, "Expected _ultoa_s to return 0, got %d\n", ret);
    ok(!strcmp(buffer, "nell"),
       "Expected output buffer string to be \"nell\", got \"%s\"\n",
       buffer);

    ret = p_ultoa_s(5704, buffer, sizeof(buffer), 18);
    ok(ret == 0, "Expected _ultoa_s to return 0, got %d\n", ret);
    ok(!strcmp(buffer, "hag"),
       "Expected output buffer string to be \"hag\", got \"%s\"\n",
       buffer);
}