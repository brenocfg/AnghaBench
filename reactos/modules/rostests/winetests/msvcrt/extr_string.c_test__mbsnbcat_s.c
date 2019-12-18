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
typedef  int /*<<< orphan*/  second ;
typedef  int /*<<< orphan*/  first ;
typedef  int /*<<< orphan*/  dest ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int ERANGE ; 
 int errno ; 
 int /*<<< orphan*/  memcmp (unsigned char*,...) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int p_mbsnbcat_s (unsigned char*,int,unsigned char const*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__mbsnbcat_s(void)
{
    unsigned char dest[16];
    const unsigned char first[] = "dinosaur";
    const unsigned char second[] = "duck";
    int ret;

    if (!p_mbsnbcat_s)
    {
        win_skip("Skipping _mbsnbcat_s tests\n");
        return;
    }

    /* Test invalid arguments. */
    ret = p_mbsnbcat_s(NULL, 0, NULL, 0);
    ok(ret == 0, "Expected _mbsnbcat_s to return 0, got %d\n", ret);

    errno = EBADF;
    ret = p_mbsnbcat_s(NULL, 10, NULL, 0);
    ok(ret == EINVAL, "Expected _mbsnbcat_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    errno = EBADF;
    ret = p_mbsnbcat_s(NULL, 0, NULL, 10);
    ok(ret == EINVAL, "Expected _mbsnbcat_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    memset(dest, 'X', sizeof(dest));
    errno = EBADF;
    ret = p_mbsnbcat_s(dest, 0, NULL, 0);
    ok(ret == EINVAL, "Expected _mbsnbcat_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(dest[0] == 'X', "Expected the output buffer to be untouched\n");

    memset(dest, 'X', sizeof(dest));
    errno = EBADF;
    ret = p_mbsnbcat_s(dest, 0, second, 0);
    ok(ret == EINVAL, "Expected _mbsnbcat_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(dest[0] == 'X', "Expected the output buffer to be untouched\n");

    memset(dest, 'X', sizeof(dest));
    errno = EBADF;
    ret = p_mbsnbcat_s(dest, sizeof(dest), NULL, 0);
    ok(ret == EINVAL, "Expected _mbsnbcat_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(dest[0] == '\0', "Expected the output buffer to be null terminated\n");

    memset(dest, 'X', sizeof(dest));
    errno = EBADF;
    ret = p_mbsnbcat_s(dest, sizeof(dest), NULL, 10);
    ok(ret == EINVAL, "Expected _mbsnbcat_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(dest[0] == '\0', "Expected the output buffer to be null terminated\n");

    memset(dest, 'X', sizeof(dest));
    dest[0] = '\0';
    ret = p_mbsnbcat_s(dest, sizeof(dest), second, sizeof(second));
    ok(ret == 0, "Expected _mbsnbcat_s to return 0, got %d\n", ret);
    ok(!memcmp(dest, second, sizeof(second)),
       "Expected the output buffer string to be \"duck\"\n");

    /* Test source truncation behavior. */
    memset(dest, 'X', sizeof(dest));
    memcpy(dest, first, sizeof(first));
    ret = p_mbsnbcat_s(dest, sizeof(dest), second, 0);
    ok(ret == 0, "Expected _mbsnbcat_s to return 0, got %d\n", ret);
    ok(!memcmp(dest, first, sizeof(first)),
       "Expected the output buffer string to be \"dinosaur\"\n");

    memset(dest, 'X', sizeof(dest));
    memcpy(dest, first, sizeof(first));
    ret = p_mbsnbcat_s(dest, sizeof(dest), second, sizeof(second));
    ok(ret == 0, "Expected _mbsnbcat_s to return 0, got %d\n", ret);
    ok(!memcmp(dest, "dinosaurduck", sizeof("dinosaurduck")),
       "Expected the output buffer string to be \"dinosaurduck\"\n");

    memset(dest, 'X', sizeof(dest));
    memcpy(dest, first, sizeof(first));
    ret = p_mbsnbcat_s(dest, sizeof(dest), second, sizeof(second) + 1);
    ok(ret == 0, "Expected _mbsnbcat_s to return 0, got %d\n", ret);
    ok(!memcmp(dest, "dinosaurduck", sizeof("dinosaurduck")),
       "Expected the output buffer string to be \"dinosaurduck\"\n");

    memset(dest, 'X', sizeof(dest));
    memcpy(dest, first, sizeof(first));
    ret = p_mbsnbcat_s(dest, sizeof(dest), second, sizeof(second) - 1);
    ok(ret == 0, "Expected _mbsnbcat_s to return 0, got %d\n", ret);
    ok(!memcmp(dest, "dinosaurduck", sizeof("dinosaurduck")),
       "Expected the output buffer string to be \"dinosaurduck\"\n");

    memset(dest, 'X', sizeof(dest));
    memcpy(dest, first, sizeof(first));
    ret = p_mbsnbcat_s(dest, sizeof(dest), second, sizeof(second) - 2);
    ok(ret == 0, "Expected _mbsnbcat_s to return 0, got %d\n", ret);
    ok(!memcmp(dest, "dinosaurduc", sizeof("dinosaurduc")),
       "Expected the output buffer string to be \"dinosaurduc\"\n");

    /* Test destination truncation behavior. */
    memset(dest, 'X', sizeof(dest));
    memcpy(dest, first, sizeof(first));
    errno = EBADF;
    ret = p_mbsnbcat_s(dest, sizeof(first) - 1, second, sizeof(second));
    ok(ret == EINVAL, "Expected _mbsnbcat_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);
    ok(!memcmp(dest, "\0inosaur", sizeof("\0inosaur") - 1),
       "Expected the output buffer string to be \"\\0inosaur\" without ending null terminator\n");

    memset(dest, 'X', sizeof(dest));
    memcpy(dest, first, sizeof(first));
    errno = EBADF;
    ret = p_mbsnbcat_s(dest, sizeof(first), second, sizeof(second));
    ok(ret == ERANGE, "Expected _mbsnbcat_s to return ERANGE, got %d\n", ret);
    ok(errno == ERANGE, "Expected errno to be ERANGE, got %d\n", errno);
    ok(!memcmp(dest, "\0inosaurd", sizeof("\0inosaurd") - 1),
       "Expected the output buffer string to be \"\\0inosaurd\" without ending null terminator\n");

    memset(dest, 'X', sizeof(dest));
    memcpy(dest, first, sizeof(first));
    errno = EBADF;
    ret = p_mbsnbcat_s(dest, sizeof(first) + 1, second, sizeof(second));
    ok(ret == ERANGE, "Expected _mbsnbcat_s to return ERANGE, got %d\n", ret);
    ok(errno == ERANGE, "Expected errno to be ERANGE, got %d\n", errno);
    ok(!memcmp(dest, "\0inosaurdu", sizeof("\0inosaurdu") - 1),
       "Expected the output buffer string to be \"\\0inosaurdu\" without ending null terminator\n");
}