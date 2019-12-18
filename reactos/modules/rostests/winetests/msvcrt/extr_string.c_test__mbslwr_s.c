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
 unsigned char* p_mbslwr_s (unsigned char*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__mbslwr_s(void)
{
    errno_t ret;
    unsigned char buffer[20];

    if (!p_mbslwr_s)
    {
        win_skip("Skipping _mbslwr_s tests\n");
        return;
    }

    errno = EBADF;
    ret = p_mbslwr_s(NULL, 0);
    ok(ret == 0, "Expected _mbslwr_s to return 0, got %d\n", ret);

    errno = EBADF;
    ret = p_mbslwr_s(NULL, sizeof(buffer));
    ok(ret == EINVAL, "Expected _mbslwr_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    errno = EBADF;
    ret = p_mbslwr_s(buffer, 0);
    ok(ret == EINVAL, "Expected _mbslwr_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    memcpy(buffer, "ABCDEFGH", sizeof("ABCDEFGH"));
    errno = EBADF;
    ret = p_mbslwr_s(buffer, sizeof("ABCDEFGH"));
    ok(ret == 0, "Expected _mbslwr_s to return 0, got %d\n", ret);
    ok(!memcmp(buffer, "abcdefgh", sizeof("abcdefgh")),
       "Expected the output buffer to be \"abcdefgh\", got \"%s\"\n",
       buffer);

    memcpy(buffer, "ABCDEFGH", sizeof("ABCDEFGH"));
    errno = EBADF;
    ret = p_mbslwr_s(buffer, sizeof(buffer));
    ok(ret == 0, "Expected _mbslwr_s to return 0, got %d\n", ret);
    ok(!memcmp(buffer, "abcdefgh", sizeof("abcdefgh")),
       "Expected the output buffer to be \"abcdefgh\", got \"%s\"\n",
       buffer);

    memcpy(buffer, "ABCDEFGH", sizeof("ABCDEFGH"));
    errno = EBADF;
    ret = p_mbslwr_s(buffer, 4);
    ok(ret == EINVAL, "Expected _mbslwr_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    memcpy(buffer, "ABCDEFGH\0IJKLMNOP", sizeof("ABCDEFGH\0IJKLMNOP"));
    errno = EBADF;
    ret = p_mbslwr_s(buffer, sizeof(buffer));
    ok(ret == 0, "Expected _mbslwr_s to return 0, got %d\n", ret);
    ok(!memcmp(buffer, "abcdefgh\0IJKLMNOP", sizeof("abcdefgh\0IJKLMNOP")),
       "Expected the output buffer to be \"abcdefgh\\0IJKLMNOP\", got \"%s\"\n",
       buffer);
}