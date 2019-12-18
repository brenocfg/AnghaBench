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

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  LC_ALL ; 
 int _getmbcp () ; 
 int /*<<< orphan*/  _setmbcp (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int p_wctob (int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_wctob(void)
{
    int ret, cp = _getmbcp();

    if(!p_wctob || !setlocale(LC_ALL, "chinese-traditional")) {
        win_skip("Skipping wctob tests\n");
        return;
    }

    ret = p_wctob(0x8141);
    ok(ret == EOF, "ret = %x\n", ret);

    ret = p_wctob(0x81);
    ok(ret == EOF, "ret = %x\n", ret);

    ret = p_wctob(0xe0);
    ok(ret == 0x61, "ret = %x\n", ret);

    _setmbcp(1250);
    ret = p_wctob(0x81);
    ok(ret == EOF, "ret = %x\n", ret);

    setlocale(LC_ALL, "C");
    ret = p_wctob(0x8141);
    ok(ret == EOF, "ret = %x\n", ret);

    ret = p_wctob(0x81);
    ok(ret == (int)(char)0x81, "ret = %x\n", ret);

    ret = p_wctob(0x9f);
    ok(ret == (int)(char)0x9f, "ret = %x\n", ret);

    ret = p_wctob(0xe0);
    ok(ret == (int)(char)0xe0, "ret = %x\n", ret);

    _setmbcp(cp);
}