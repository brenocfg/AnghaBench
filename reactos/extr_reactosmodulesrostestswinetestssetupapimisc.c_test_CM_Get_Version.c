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
typedef  int WORD ;

/* Variables and functions */
 int CM_Get_Version () ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_CM_Get_Version(void)
{
    WORD ret;

    ret = CM_Get_Version();
    ok(ret == 0x0400, "got version %#x\n", ret);
}