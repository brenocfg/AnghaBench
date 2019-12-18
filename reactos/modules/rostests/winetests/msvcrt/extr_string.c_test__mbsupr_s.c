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
typedef  unsigned char* errno_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 unsigned char* EBADF ; 
 unsigned char* EINVAL ; 
 unsigned char* errno ; 
 int /*<<< orphan*/  memcmp (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,unsigned char*) ; 
 unsigned char* p_mbsupr_s (unsigned char*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__mbsupr_s(void)
{
    errno_t ret;
    unsigned char buffer[20];

    if (!p_mbsupr_s)
    {
        win_skip("Skipping _mbsupr_s tests\n");
        return;
    }

    errno = EBADF;
    ret = p_mbsupr_s(NULL, 0);
    ok(ret == 0, "Expected _mbsupr_s to return 0, got %d\n", ret);

    errno = EBADF;
    ret = p_mbsupr_s(NULL, sizeof(buffer));
    ok(ret == EINVAL, "Expected _mbsupr_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    errno = EBADF;
    ret = p_mbsupr_s(buffer, 0);
    ok(ret == EINVAL, "Expected _mbsupr_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    memcpy(buffer, "abcdefgh", sizeof("abcdefgh"));
    errno = EBADF;
    ret = p_mbsupr_s(buffer, sizeof("abcdefgh"));
    ok(ret == 0, "Expected _mbsupr_s to return 0, got %d\n", ret);
    ok(!memcmp(buffer, "ABCDEFGH", sizeof("ABCDEFGH")),
       "Expected the output buffer to be \"ABCDEFGH\", got \"%s\"\n",
       buffer);

    memcpy(buffer, "abcdefgh", sizeof("abcdefgh"));
    errno = EBADF;
    ret = p_mbsupr_s(buffer, sizeof(buffer));
    ok(ret == 0, "Expected _mbsupr_s to return 0, got %d\n", ret);
    ok(!memcmp(buffer, "ABCDEFGH", sizeof("ABCDEFGH")),
       "Expected the output buffer to be \"ABCDEFGH\", got \"%s\"\n",
       buffer);

    memcpy(buffer, "abcdefgh", sizeof("abcdefgh"));
    errno = EBADF;
    ret = p_mbsupr_s(buffer, 4);
    ok(ret == EINVAL, "Expected _mbsupr_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    memcpy(buffer, "abcdefgh\0ijklmnop", sizeof("abcdefgh\0ijklmnop"));
    errno = EBADF;
    ret = p_mbsupr_s(buffer, sizeof(buffer));
    ok(ret == 0, "Expected _mbsupr_s to return 0, got %d\n", ret);
    ok(!memcmp(buffer, "ABCDEFGH\0ijklmnop", sizeof("ABCDEFGH\0ijklmnop")),
       "Expected the output buffer to be \"ABCDEFGH\\0ijklmnop\", got \"%s\"\n",
       buffer);

}