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
typedef  char wchar_t ;
typedef  scalar_t__ WORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int CT_CTYPE1 ; 
 int CT_CTYPE2 ; 
 int CT_CTYPE3 ; 
 scalar_t__ GetStringTypeW (int,char const*,int,scalar_t__*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ p__crtGetStringTypeW (int /*<<< orphan*/ ,int,char const*,int,scalar_t__*) ; 
 int /*<<< orphan*/  pmemcpy_s ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_crtGetStringTypeW(void)
{
    static const wchar_t str0[] = { '0', '\0' };
    static const wchar_t strA[] = { 'A', '\0' };
    static const wchar_t str_space[] = { ' ', '\0' };
    static const wchar_t str_null[] = { '\0', '\0' };
    static const wchar_t str_rand[] = { 1234, '\0' };

    const wchar_t *str[] = { str0, strA, str_space, str_null, str_rand };

    WORD out_crt, out;
    BOOL ret_crt, ret;
    int i;

    if(!p__crtGetStringTypeW) {
        win_skip("Skipping __crtGetStringTypeW tests\n");
        return;
    }

    if(!pmemcpy_s) {
        win_skip("Too old version of msvcrt.dll\n");
        return;
    }

    for(i=0; i<ARRAY_SIZE(str); i++) {
        ret_crt = p__crtGetStringTypeW(0, CT_CTYPE1, str[i], 1, &out_crt);
        ret = GetStringTypeW(CT_CTYPE1, str[i], 1, &out);
        ok(ret == ret_crt, "%d) ret_crt = %d\n", i, (int)ret_crt);
        ok(out == out_crt, "%d) out_crt = %x, expected %x\n", i, (int)out_crt, (int)out);

        ret_crt = p__crtGetStringTypeW(0, CT_CTYPE2, str[i], 1, &out_crt);
        ret = GetStringTypeW(CT_CTYPE2, str[i], 1, &out);
        ok(ret == ret_crt, "%d) ret_crt = %d\n", i, (int)ret_crt);
        ok(out == out_crt, "%d) out_crt = %x, expected %x\n", i, (int)out_crt, (int)out);

        ret_crt = p__crtGetStringTypeW(0, CT_CTYPE3, str[i], 1, &out_crt);
        ret = GetStringTypeW(CT_CTYPE3, str[i], 1, &out);
        ok(ret == ret_crt, "%d) ret_crt = %d\n", i, (int)ret_crt);
        ok(out == out_crt, "%d) out_crt = %x, expected %x\n", i, (int)out_crt, (int)out);
    }

    ret = p__crtGetStringTypeW(0, 3, str[0], 1, &out);
    ok(!ret, "ret == TRUE\n");
}