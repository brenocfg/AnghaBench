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
typedef  scalar_t__ HDWP ;

/* Variables and functions */
 scalar_t__ EndDeferWindowPos (scalar_t__) ; 
 scalar_t__ NtUserCallOneParam (int,int) ; 
 int /*<<< orphan*/  TEST (int) ; 

void
Test_OneParamRoutine_BeginDeferWindowPos(void) /* 0x1e */
{
    HDWP hWinPosInfo;

    hWinPosInfo = (HDWP)NtUserCallOneParam(5, 0x1e);
    TEST(hWinPosInfo != 0);
    TEST(EndDeferWindowPos(hWinPosInfo) != 0);

}