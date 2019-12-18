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
 int /*<<< orphan*/  LC_ALL ; 
 int _stricmp (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__stricmp(void)
{
    int ret;

    ret = _stricmp("test", "test");
    ok(ret == 0, "_stricmp returned %d\n", ret);
    ret = _stricmp("a", "z");
    ok(ret < 0, "_stricmp returned %d\n", ret);
    ret = _stricmp("z", "a");
    ok(ret > 0, "_stricmp returned %d\n", ret);
    ret = _stricmp("\xa5", "\xb9");
    ok(ret < 0, "_stricmp returned %d\n", ret);

    if(!setlocale(LC_ALL, "polish")) {
        win_skip("stricmp tests\n");
        return;
    }

    ret = _stricmp("test", "test");
    ok(ret == 0, "_stricmp returned %d\n", ret);
    ret = _stricmp("a", "z");
    ok(ret < 0, "_stricmp returned %d\n", ret);
    ret = _stricmp("z", "a");
    ok(ret > 0, "_stricmp returned %d\n", ret);
    ret = _stricmp("\xa5", "\xb9");
    ok(ret == 0, "_stricmp returned %d\n", ret);
    ret = _stricmp("a", "\xb9");
    ok(ret < 0, "_stricmp returned %d\n", ret);

    setlocale(LC_ALL, "C");
}