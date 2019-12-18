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
typedef  int /*<<< orphan*/  abcW ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int STRUNCATE ; 
 int _TRUNCATE ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int p_wcsncat_s (char*,int,char*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_wcsncat_s(void)
{
    static wchar_t abcW[] = {'a','b','c',0};
    int ret;
    wchar_t dst[4];
    wchar_t src[4];

    if (!p_wcsncat_s)
    {
        win_skip("skipping wcsncat_s tests\n");
        return;
    }

    memcpy(src, abcW, sizeof(abcW));
    dst[0] = 0;
    ret = p_wcsncat_s(NULL, 4, src, 4);
    ok(ret == EINVAL, "err = %d\n", ret);
    ret = p_wcsncat_s(dst, 0, src, 4);
    ok(ret == EINVAL, "err = %d\n", ret);
    ret = p_wcsncat_s(dst, 0, src, _TRUNCATE);
    ok(ret == EINVAL, "err = %d\n", ret);
    ret = p_wcsncat_s(dst, 4, NULL, 0);
    ok(ret == 0, "err = %d\n", ret);

    dst[0] = 0;
    ret = p_wcsncat_s(dst, 2, src, 4);
    ok(ret == ERANGE, "err = %d\n", ret);

    dst[0] = 0;
    ret = p_wcsncat_s(dst, 2, src, _TRUNCATE);
    ok(ret == STRUNCATE, "err = %d\n", ret);
    ok(dst[0] == 'a' && dst[1] == 0, "dst is %s\n", wine_dbgstr_w(dst));

    memcpy(dst, abcW, sizeof(abcW));
    dst[3] = 'd';
    ret = p_wcsncat_s(dst, 4, src, 4);
    ok(ret == EINVAL, "err = %d\n", ret);
}