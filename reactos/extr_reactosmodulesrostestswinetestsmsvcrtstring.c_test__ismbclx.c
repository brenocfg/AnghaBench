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
 int _ismbcl0 (int) ; 
 int _setmbcp (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test__ismbclx(void)
{
    int cp, ret;

    ret = _ismbcl0(0);
    ok(!ret, "got %d\n", ret);

    cp = _setmbcp(1252);

    ret = _ismbcl0(0x8140);
    ok(!ret, "got %d\n", ret);

    _setmbcp(932);

    ret = _ismbcl0(0);
    ok(!ret, "got %d\n", ret);

    ret = _ismbcl0(0x8140);
    ok(ret, "got %d\n", ret);

    _setmbcp(cp);
}