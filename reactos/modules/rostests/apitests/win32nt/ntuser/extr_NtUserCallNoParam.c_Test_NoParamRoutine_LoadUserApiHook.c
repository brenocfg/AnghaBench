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
 int /*<<< orphan*/  NtUserCallNoParam (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _NOPARAM_ROUTINE_LOADUSERAPIHOOK ; 

void
Test_NoParamRoutine_LoadUserApiHook(void) /* 0x1d */
{
    //DWORD dwRet;
    /* dwRet = */NtUserCallNoParam(_NOPARAM_ROUTINE_LOADUSERAPIHOOK);

//  TEST(dwRet != 0);

}