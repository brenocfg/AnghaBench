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
typedef  int wint_t ;
typedef  int /*<<< orphan*/ * _locale_t ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  ok (int,char*,int,int) ; 
 int /*<<< orphan*/ * p__create_locale (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  p__free_locale (int /*<<< orphan*/ *) ; 
 int p__towlower_l (int,int /*<<< orphan*/ *) ; 
 int p__towupper_l (int,int /*<<< orphan*/ *) ; 
 int p_towlower (int) ; 
 int p_towupper (int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_C_locale(void)
{
    int i, j;
    wint_t ret, exp;
    _locale_t locale;
    static const char *locales[] = { NULL, "C" };

    /* C locale only converts case for [a-zA-Z] */
    setlocale(LC_ALL, "C");
    for (i = 0; i <= 0xffff; i++)
    {
        ret = p_towlower(i);
        if (i >= 'A' && i <= 'Z')
        {
            exp = i + 'a' - 'A';
            ok(ret == exp, "expected %x, got %x for C locale\n", exp, ret);
        }
        else
            ok(ret == i, "expected self %x, got %x for C locale\n", i, ret);

        ret = p_towupper(i);
        if (i >= 'a' && i <= 'z')
        {
            exp = i + 'A' - 'a';
            ok(ret == exp, "expected %x, got %x for C locale\n", exp, ret);
        }
        else
            ok(ret == i, "expected self %x, got %x for C locale\n", i, ret);
    }

    if (!p__towlower_l || !p__towupper_l || !p__create_locale)
    {
        win_skip("_towlower_l/_towupper_l/_create_locale not available\n");
        return;
    }

    for (i = 0; i < ARRAY_SIZE(locales); i++) {
        locale = locales[i] ? p__create_locale(LC_ALL, locales[i]) : NULL;

        for (j = 0; j <= 0xffff; j++) {
            ret = p__towlower_l(j, locale);
            if (j >= 'A' && j <= 'Z')
            {
                exp = j + 'a' - 'A';
                ok(ret == exp, "expected %x, got %x for C locale\n", exp, ret);
            }
            else
                ok(ret == j, "expected self %x, got %x for C locale\n", j, ret);

            ret = p__towupper_l(j, locale);
            if (j >= 'a' && j <= 'z')
            {
                exp = j + 'A' - 'a';
                ok(ret == exp, "expected %x, got %x for C locale\n", exp, ret);
            }
            else
                ok(ret == j, "expected self %x, got %x for C locale\n", j, ret);
        }

        p__free_locale(locale);
    }
}