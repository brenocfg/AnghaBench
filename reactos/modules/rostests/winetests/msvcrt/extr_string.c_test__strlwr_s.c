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
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ p_strlwr_s (char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__strlwr_s(void)
{
    errno_t ret;
    char buffer[20];

    if (!p_strlwr_s)
    {
        win_skip("Skipping _strlwr_s tests\n");
        return;
    }

    errno = EBADF;
    ret = p_strlwr_s(NULL, 0);
    ok(ret == EINVAL, "Expected _strlwr_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    errno = EBADF;
    ret = p_strlwr_s(NULL, sizeof(buffer));
    ok(ret == EINVAL, "Expected _strlwr_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    errno = EBADF;
    ret = p_strlwr_s(buffer, 0);
    ok(ret == EINVAL, "Expected _strlwr_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    strcpy(buffer, "GoRrIsTeR");
    errno = EBADF;
    ret = p_strlwr_s(buffer, 5);
    ok(ret == EINVAL, "Expected _strlwr_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(!memcmp(buffer, "\0oRrIsTeR", sizeof("\0oRrIsTeR")),
       "Expected the output buffer to be \"\\0oRrIsTeR\"\n");

    strcpy(buffer, "GoRrIsTeR");
    errno = EBADF;
    ret = p_strlwr_s(buffer, sizeof("GoRrIsTeR") - 1);
    ok(ret == EINVAL, "Expected _strlwr_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(!memcmp(buffer, "\0oRrIsTeR", sizeof("\0oRrIsTeR")),
       "Expected the output buffer to be \"\\0oRrIsTeR\"\n");

    strcpy(buffer, "GoRrIsTeR");
    ret = p_strlwr_s(buffer, sizeof("GoRrIsTeR"));
    ok(ret == 0, "Expected _strlwr_s to return 0, got %d\n", ret);
    ok(!strcmp(buffer, "gorrister"),
       "Expected the output buffer to be \"gorrister\", got \"%s\"\n",
       buffer);

    memcpy(buffer, "GoRrIsTeR\0ELLEN", sizeof("GoRrIsTeR\0ELLEN"));
    ret = p_strlwr_s(buffer, sizeof(buffer));
    ok(ret == 0, "Expected _strlwr_s to return 0, got %d\n", ret);
    ok(!memcmp(buffer, "gorrister\0ELLEN", sizeof("gorrister\0ELLEN")),
       "Expected the output buffer to be \"gorrister\\0ELLEN\", got \"%s\"\n",
       buffer);
}