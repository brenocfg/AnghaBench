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
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GETTEXTMARGIN ; 
 int /*<<< orphan*/  BCM_SETTEXTMARGIN ; 
 int /*<<< orphan*/  BS_DEFPUSHBUTTON ; 
 int /*<<< orphan*/ * CreateWindowW (char*,char*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  SetWindowTheme (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_rect (int /*<<< orphan*/ ,int,int,int,int) ; 

void Test_TextMargin()
{
    RECT rc;
    BOOL ret;
    HWND hwnd1;
    
    hwnd1 = CreateWindowW(L"Button", L"Test1", 0, 10, 10, 100, 100, 0, NULL, NULL, NULL);
    ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");
    SetWindowTheme(hwnd1, L"", L"");

    ret = SendMessageW(hwnd1, BCM_GETTEXTMARGIN, 0, (LPARAM)&rc);
    ok (ret == TRUE, "Expected BCM_GETTEXTMARGIN to succeed\n");
    ok_rect(rc, 1, 1, 1, 1);
    
    SetRect(&rc, 0,0,0,0);
    ret = SendMessageW(hwnd1, BCM_SETTEXTMARGIN, 0, (LPARAM)&rc);
    ok (ret == TRUE, "Expected BCM_SETTEXTMARGIN to succeed\n");
    
    ret = SendMessageW(hwnd1, BCM_GETTEXTMARGIN, 0, (LPARAM)&rc);
    ok (ret == TRUE, "Expected BCM_GETTEXTMARGIN to succeed\n");
    ok_rect(rc, 0, 0, 0, 0);
    
    SetRect(&rc, -1,-1,-1,-1);
    ret = SendMessageW(hwnd1, BCM_SETTEXTMARGIN, 0, (LPARAM)&rc);
    ok (ret == TRUE, "Expected BCM_SETTEXTMARGIN to succeed\n");
    
    ret = SendMessageW(hwnd1, BCM_GETTEXTMARGIN, 0, (LPARAM)&rc);
    ok (ret == TRUE, "Expected BCM_GETTEXTMARGIN to succeed\n");
    ok_rect(rc, -1, -1, -1, -1);

    SetRect(&rc, 1000,1000,1000,1000);
    ret = SendMessageW(hwnd1, BCM_SETTEXTMARGIN, 0, (LPARAM)&rc);
    ok (ret == TRUE, "Expected BCM_SETTEXTMARGIN to succeed\n");
    
    ret = SendMessageW(hwnd1, BCM_GETTEXTMARGIN, 0, (LPARAM)&rc);
    ok (ret == TRUE, "Expected BCM_GETTEXTMARGIN to succeed\n");
    ok_rect(rc, 1000, 1000, 1000, 1000);
    
    DestroyWindow(hwnd1);

    hwnd1 = CreateWindowW(L"Button", L"Test1", BS_DEFPUSHBUTTON, 10, 10, 100, 100, 0, NULL, NULL, NULL);
    ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");
    SetWindowTheme(hwnd1, L"", L"");

    ret = SendMessageW(hwnd1, BCM_GETTEXTMARGIN, 0, (LPARAM)&rc);
    ok (ret == TRUE, "Expected BCM_GETTEXTMARGIN to succeed\n");
    ok_rect(rc, 1, 1, 1, 1);

    DestroyWindow(hwnd1);

}