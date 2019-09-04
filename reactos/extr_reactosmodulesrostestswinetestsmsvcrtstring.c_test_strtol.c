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
typedef  int ULONG ;
typedef  int LONG ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  ERANGE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_strtol(void)
{
    static char neg[] = "-0x";

    char* e;
    LONG l;
    ULONG ul;

    /* errno is only set in case of error, so reset errno to EBADF to check for errno modification */
    /* errno is modified on W2K8+ */
    errno = EBADF;
    l = strtol("-1234", &e, 0);
    ok(l==-1234, "wrong value %d\n", l);
    ok(errno == EBADF || broken(errno == 0), "wrong errno %d\n", errno);
    errno = EBADF;
    ul = strtoul("1234", &e, 0);
    ok(ul==1234, "wrong value %u\n", ul);
    ok(errno == EBADF || broken(errno == 0), "wrong errno %d\n", errno);

    errno = EBADF;
    l = strtol("2147483647L", &e, 0);
    ok(l==2147483647, "wrong value %d\n", l);
    ok(errno == EBADF || broken(errno == 0), "wrong errno %d\n", errno);
    errno = EBADF;
    l = strtol("-2147483648L", &e, 0);
    ok(l==-2147483647L - 1, "wrong value %d\n", l);
    ok(errno == EBADF || broken(errno == 0), "wrong errno %d\n", errno);
    errno = EBADF;
    ul = strtoul("4294967295UL", &e, 0);
    ok(ul==4294967295ul, "wrong value %u\n", ul);
    ok(errno == EBADF || broken(errno == 0), "wrong errno %d\n", errno);

    errno = 0;
    l = strtol("9223372036854775807L", &e, 0);
    ok(l==2147483647, "wrong value %d\n", l);
    ok(errno == ERANGE, "wrong errno %d\n", errno);
    errno = 0;
    ul = strtoul("9223372036854775807L", &e, 0);
    ok(ul==4294967295ul, "wrong value %u\n", ul);
    ok(errno == ERANGE, "wrong errno %d\n", errno);

    errno = 0;
    ul = strtoul("-2", NULL, 0);
    ok(ul == -2, "wrong value %u\n", ul);
    ok(errno == 0, "wrong errno %d\n", errno);

    errno = 0;
    ul = strtoul("-4294967294", NULL, 0);
    ok(ul == 2, "wrong value %u\n", ul);
    ok(errno == 0, "wrong errno %d\n", errno);

    errno = 0;
    ul = strtoul("-4294967295", NULL, 0);
    ok(ul==1, "wrong value %u\n", ul);
    ok(errno == 0, "wrong errno %d\n", errno);

    errno = 0;
    ul = strtoul("-4294967296", NULL, 0);
    ok(ul == 1, "wrong value %u\n", ul);
    ok(errno == ERANGE, "wrong errno %d\n", errno);

    errno = 0;
    l = strtol(neg, &e, 0);
    ok(l == 0, "wrong value %d\n", l);
    ok(errno == 0, "wrong errno %d\n", errno);
    ok(e == neg, "e = %p, neg = %p\n", e, neg);
}