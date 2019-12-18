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
typedef  int (* memcmpfunc ) (unsigned char*,unsigned char*) ;

/* Variables and functions */
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_memcmpfunc(memcmpfunc fn)
{
    unsigned char arg1[0x20], arg2[0x20];
    int r;

    if (!fn)
    {
        win_skip("function is not available\n");
        return;
    }

    memset(arg1, 0, sizeof arg1);
    memset(arg2, 0, sizeof arg2);
    arg1[0x10] = 1;

    r = fn(arg1, arg2);
    ok( r == 1, "wrong error code\n");

    memset(arg1, 1, sizeof arg1);
    memset(arg2, 1, sizeof arg2);
    arg1[0x10] = 0;

    r = fn(arg1, arg2);
    ok( r == 1, "wrong error code\n");

    memset(arg1, 0, sizeof arg1);
    memset(arg2, 1, sizeof arg2);

    r = fn(arg1, arg2);
    ok( r == 0, "wrong error code\n");

    memset(arg1, 1, sizeof arg1);
    memset(arg2, 0, sizeof arg2);

    r = fn(arg1, arg2);
    ok( r == 0, "wrong error code\n");
}