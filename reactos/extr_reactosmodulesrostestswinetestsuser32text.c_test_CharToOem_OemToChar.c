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
typedef  int /*<<< orphan*/  tests ;
typedef  int /*<<< orphan*/  helloWorldW ;
typedef  int /*<<< orphan*/  helloWorld ;
typedef  int /*<<< orphan*/  buf ;
typedef  char WCHAR ;
typedef  char BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_OEMCP ; 
 char CharToOemA (char const*,char*) ; 
 char CharToOemBuffA (char const*,char*,int) ; 
 char CharToOemBuffW (char const*,char*,int) ; 
 char CharToOemW (char const*,char*) ; 
#define  FALSE 129 
 int MB_PRECOMPOSED ; 
 int MB_USEGLYPHCHARS ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int,char*,int,char*,int) ; 
 char OemToCharA (char const*,char*) ; 
 char OemToCharBuffA (char const*,char*,int) ; 
 char OemToCharBuffW (char const*,char*,int) ; 
 char OemToCharW (char const*,char*) ; 
#define  TRUE 128 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_CharToOem_OemToChar(void)
{
    static const WCHAR helloWorldW[] = {'H','e','l','l','o',' ','W','o','r','l','d',0};
    static const WCHAR emptyW[] = {0};
    static const char helloWorld[] = "Hello World";
    static const struct
    {
        BOOL src, dst, ret;
    }
    tests[] =
    {
        { FALSE, FALSE, FALSE },
        { TRUE,  FALSE, FALSE },
        { FALSE, TRUE,  FALSE },
        { TRUE,  TRUE,  TRUE  },
    };
    BOOL ret;
    int i;
    char oem;
    WCHAR uni, expect;

    for (i = 0; i < sizeof(tests)/sizeof(tests[0]); i++)
    {
        const char *expected = tests[i].ret ? helloWorld : "";
        const char *src = tests[i].src ? helloWorld : NULL;
        char buf[64], *dst = tests[i].dst ? buf : NULL;

        memset(buf, 0, sizeof(buf));
        ret = CharToOemA(src, dst);
        ok(ret == tests[i].ret, "test %d: expected %d, got %d\n", i, tests[i].ret, ret);
        ok(!strcmp(buf, expected), "test %d: got '%s'\n", i, buf);

        memset(buf, 0, sizeof(buf));
        ret = CharToOemBuffA(src, dst, sizeof(helloWorld));
        ok(ret == tests[i].ret, "test %d: expected %d, got %d\n", i, tests[i].ret, ret);
        ok(!strcmp(buf, expected), "test %d: got '%s'\n", i, buf);

        memset(buf, 0, sizeof(buf));
        ret = OemToCharA(src, dst);
        ok(ret == tests[i].ret, "test %d: expected %d, got %d\n", i, tests[i].ret, ret);
        ok(!strcmp(buf, expected), "test %d: got '%s'\n", i, buf);

        memset(buf, 0, sizeof(buf));
        ret = OemToCharBuffA(src, dst, sizeof(helloWorld));
        ok(ret == tests[i].ret, "test %d: expected %d, got %d\n", i, tests[i].ret, ret);
        ok(!strcmp(buf, expected), "test %d: got '%s'\n", i, buf);
    }

    for (i = 0; i < sizeof(tests)/sizeof(tests[0]); i++)
    {
        const char *expected = tests[i].ret ? helloWorld : "";
        const WCHAR *src = tests[i].src ? helloWorldW : NULL;
        char buf[64], *dst = tests[i].dst ? buf : NULL;

        memset(buf, 0, sizeof(buf));
        ret = CharToOemW(src, dst);
        ok(ret == tests[i].ret, "test %d: expected %d, got %d\n", i, tests[i].ret, ret);
        ok(!strcmp(buf, expected), "test %d: got '%s'\n", i, buf);

        memset(buf, 0, sizeof(buf));
        ret = CharToOemBuffW(src, dst, sizeof(helloWorldW)/sizeof(WCHAR));
        ok(ret == tests[i].ret, "test %d: expected %d, got %d\n", i, tests[i].ret, ret);
        ok(!strcmp(buf, expected), "test %d: got '%s'\n", i, buf);
    }

    for (i = 0; i < sizeof(tests)/sizeof(tests[0]); i++)
    {
        const WCHAR *expected = tests[i].ret ? helloWorldW : emptyW;
        const char *src = tests[i].src ? helloWorld : NULL;
        WCHAR buf[64], *dst = tests[i].dst ? buf : NULL;

        memset(buf, 0, sizeof(buf));
        ret = OemToCharW(src, dst);
        ok(ret == tests[i].ret, "test %d: expected %d, got %d\n", i, tests[i].ret, ret);
        ok(!lstrcmpW(buf, expected), "test %d: got '%s'\n", i, wine_dbgstr_w(buf));

        memset(buf, 0, sizeof(buf));
        ret = OemToCharBuffW(src, dst, sizeof(helloWorld));
        ok(ret == tests[i].ret, "test %d: expected %d, got %d\n", i, tests[i].ret, ret);
        ok(!lstrcmpW(buf, expected), "test %d: got '%s'\n", i, wine_dbgstr_w(buf));
    }

    for (i = 0; i < 0x100; i++)
    {
        oem = i;
        ret = OemToCharBuffW( &oem, &uni, 1 );
        ok( ret, "%02x: returns FALSE\n", i );
        MultiByteToWideChar( CP_OEMCP, MB_PRECOMPOSED | MB_USEGLYPHCHARS, &oem, 1, &expect, 1 );
        ok( uni == expect, "%02x: got %04x expected %04x\n", i, uni, expect );
    }
}