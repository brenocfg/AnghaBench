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
typedef  scalar_t__ HWND ;
typedef  scalar_t__ HDC ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ GetDC (int /*<<< orphan*/ *) ; 
 scalar_t__ GetDesktopWindow () ; 
 int IsWindow (scalar_t__) ; 
 scalar_t__ NtUserCallOneParam (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST (int) ; 

void
Test_OneParamRoutine_WindowFromDC(void) /* 0x1f */
{
    HDC hDC = GetDC(NULL);
    HWND hWnd;

    hWnd = (HWND)NtUserCallOneParam((DWORD)hDC, 0x1f);
    TEST(hWnd != 0);
    TEST(IsWindow(hWnd));
    TEST(hWnd == GetDesktopWindow());

}