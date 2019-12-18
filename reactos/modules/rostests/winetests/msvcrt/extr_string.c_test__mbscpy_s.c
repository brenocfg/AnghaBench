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
typedef  int /*<<< orphan*/  src ;
typedef  int /*<<< orphan*/  dest ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  memcmp (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int p__mbscpy_s (unsigned char*,int,unsigned char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__mbscpy_s(void)
{
    const unsigned char src[] = "source string";
    unsigned char dest[16];
    int ret;

    if(!p__mbscpy_s)
    {
        win_skip("_mbscpy_s not found\n");
        return;
    }

    ret = p__mbscpy_s(NULL, 0, src);
    ok(ret == EINVAL, "got %d\n", ret);
    ret = p__mbscpy_s(NULL, sizeof(dest), src);
    ok(ret == EINVAL, "got %d\n", ret);
    ret = p__mbscpy_s(dest, 0, src);
    ok(ret == EINVAL, "got %d\n", ret);
    dest[0] = 'x';
    ret = p__mbscpy_s(dest, sizeof(dest), NULL);
    ok(ret == EINVAL, "got %d\n", ret);
    ok(!dest[0], "dest buffer was not modified on invalid argument\n");

    memset(dest, 'X', sizeof(dest));
    ret = p__mbscpy_s(dest, sizeof(dest), src);
    ok(!ret, "got %d\n", ret);
    ok(!memcmp(dest, src, sizeof(src)), "dest = %s\n", dest);
    ok(dest[sizeof(src)] == 'X', "unused part of buffer was modified\n");

    memset(dest, 'X', sizeof(dest));
    ret = p__mbscpy_s(dest, 4, src);
    ok(ret == ERANGE, "got %d\n", ret);
    ok(!dest[0], "incorrect dest buffer (%d)\n", dest[0]);
    ok(dest[1] == src[1], "incorrect dest buffer (%d)\n", dest[1]);
}