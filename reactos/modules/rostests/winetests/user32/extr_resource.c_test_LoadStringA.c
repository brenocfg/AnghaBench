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
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 void* LoadStringA (int /*<<< orphan*/ ,int,char*,unsigned int const) ; 
 int MAKELONG (int,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memcmp (char*,char const*,int const) ; 
 int /*<<< orphan*/  ok (int,char*,unsigned int const,...) ; 

__attribute__((used)) static void test_LoadStringA (void)
{
    HINSTANCE hInst = GetModuleHandleA(NULL);
    static const char str[] = "String resource"; /* same in resource.rc */
    char buf[128];
    struct string_test {
        unsigned int bufsiz;
        unsigned int expected;
    };
    struct string_test tests[] = {{sizeof buf, sizeof str - 1},
                                  {sizeof str, sizeof str - 1},
                                  {sizeof str - 1, sizeof str - 2}};
    unsigned int i;
    int ret, ret2;

    assert (sizeof str < sizeof buf);
    for (i = 0; i < sizeof tests / sizeof tests[0]; i++) {
        const unsigned int bufsiz = tests[i].bufsiz;
        const unsigned int expected = tests[i].expected;
        const int len = LoadStringA (hInst, 0, buf, bufsiz);

        ok (len == expected, "bufsiz=%d: got %d, expected %d\n",
            bufsiz, len, expected);
        if (len != expected) continue;
        ok (!memcmp (buf, str, len),
            "bufsiz=%d: got '%s', expected '%.*s'\n",
            bufsiz, buf, len, str);
        ok (buf[len] == 0, "bufsiz=%d: NUL termination missing\n",
            bufsiz);
    }

    ret = LoadStringA(hInst, 1, buf, sizeof(buf) );
    ok( ret > 0, "LoadString failed: ret %d err %d\n", ret, GetLastError());
    ret2 = LoadStringA( hInst, MAKELONG( 1, 0x8000 ), buf, sizeof(buf));
    ok( ret2 == ret, "LoadString failed: ret %d err %d\n", ret, GetLastError());
    ret2 = LoadStringA( hInst, MAKELONG( 1, 0xffff ), buf, sizeof(buf));
    ok( ret2 == ret, "LoadString failed: ret %d err %d\n", ret, GetLastError());

    ret = LoadStringA(hInst, 65534, buf, sizeof(buf) );
    ok( ret > 0, "LoadString failed: ret %d err %d\n", ret, GetLastError());
    ret2 = LoadStringA( hInst, MAKELONG( 65534, 0x8000 ), buf, sizeof(buf));
    ok( ret2 == ret, "LoadString failed: ret %d err %d\n", ret, GetLastError());
    ret2 = LoadStringA( hInst, MAKELONG( 65534, 0xffff ), buf, sizeof(buf));
    ok( ret2 == ret, "LoadString failed: ret %d err %d\n", ret, GetLastError());

    ret = LoadStringA(hInst, 0, buf, 0);
    ok( ret == -1 || broken(ret == 0),
        "LoadStringA did not return -1 when called with buflen = 0, got %d, err %d\n",
        ret, GetLastError());

    SetLastError(0xdeadbeef);
    buf[0] = 'a';
    ret = LoadStringA(hInst, 1, buf, 1);
    ok( !ret, "LoadString returned %d\n", ret);
    ok( buf[0] == 0, "buf[0] = %c (%x)\n", buf[0], buf[0]);
    ok( GetLastError() == 0xdeadbeef, "GetLastError() = %d\n", GetLastError());
}