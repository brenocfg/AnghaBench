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
typedef  int /*<<< orphan*/  rc ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_CACHE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateWindowW (char*,char*,int,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DrawThemeParentBackground (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EMPTY_CACHE () ; 
 int /*<<< orphan*/  FlushMessages () ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegisterSimpleClass (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestProc ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ *) ; 
 int WS_CHILD ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  draw_parent_chain ; 
 int /*<<< orphan*/  empty_chain ; 
 int /*<<< orphan*/ * hWnd1 ; 
 int /*<<< orphan*/ * hWnd2 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

void Test_Messages()
{
    HDC hdc;
    RECT rc;

    RegisterSimpleClass(TestProc, L"testClass");

    hWnd1 = CreateWindowW(L"testClass", L"Test parent", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 200, 200, 0, NULL, NULL, NULL);
    ok (hWnd1 != NULL, "Expected CreateWindowW to succeed\n");

    hWnd2 = CreateWindowW(L"testClass", L"test window", WS_CHILD | WS_VISIBLE, 0, 0, 100, 100, hWnd1, NULL, NULL, NULL);
    ok (hWnd2 != NULL, "Expected CreateWindowW to succeed\n");

    FlushMessages();
    EMPTY_CACHE();

    hdc = GetDC(hWnd1);

    DrawThemeParentBackground(hWnd2, hdc, NULL);
    FlushMessages();
    COMPARE_CACHE(draw_parent_chain);

    DrawThemeParentBackground(hWnd1, hdc, NULL);
    FlushMessages();
    COMPARE_CACHE(empty_chain);

    ShowWindow(hWnd1, SW_SHOW);
    UpdateWindow(hWnd1);
    ShowWindow(hWnd2, SW_SHOW);
    UpdateWindow(hWnd2);

    FlushMessages();
    EMPTY_CACHE();

    DrawThemeParentBackground(hWnd2, NULL, NULL);
    FlushMessages();
    COMPARE_CACHE(empty_chain);

    DrawThemeParentBackground(hWnd1, NULL, NULL);
    FlushMessages();
    COMPARE_CACHE(empty_chain);

    DrawThemeParentBackground(hWnd2, hdc, NULL);
    FlushMessages();
    COMPARE_CACHE(draw_parent_chain);

    DrawThemeParentBackground(hWnd1, hdc, NULL);
    FlushMessages();
    COMPARE_CACHE(empty_chain);
    
    memset(&rc, 0, sizeof(rc));
    
    DrawThemeParentBackground(hWnd2, hdc, &rc);
    FlushMessages();
    COMPARE_CACHE(draw_parent_chain);

    DrawThemeParentBackground(hWnd1, hdc, &rc);
    FlushMessages();
    COMPARE_CACHE(empty_chain);
}