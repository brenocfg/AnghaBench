#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hdc; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ PAINTSTRUCT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  ChildWnd ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_BRUSH ; 
 int /*<<< orphan*/  BeginPaint (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void OnPaint(HWND hWnd, ChildWnd* pChildWnd)
{
    PAINTSTRUCT ps;
    RECT rt;
    GetClientRect(hWnd, &rt);
    BeginPaint(hWnd, &ps);

//    lastBrush = SelectObject(ps.hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
//    Rectangle(ps.hdc, rt.left, rt.top-1, rt.right, rt.bottom+1);
//    SelectObject(ps.hdc, lastBrush);
//    rt.top = rt.bottom - GetSystemMetrics(SM_CYHSCROLL);
    FillRect(ps.hdc, &rt, GetStockObject(BLACK_BRUSH));
/*
    rt.left = pChildWnd->nSplitPos-SPLIT_WIDTH/2;
    rt.right = pChildWnd->nSplitPos+SPLIT_WIDTH/2+1;
    lastBrush = SelectBrush(ps.hdc, (HBRUSH)GetStockObject(COLOR_SPLITBAR));
    Rectangle(ps.hdc, rt.left, rt.top-1, rt.right, rt.bottom+1);
    SelectObject(ps.hdc, lastBrush);
#ifdef _NO_EXTENSIONS
    rt.top = rt.bottom - GetSystemMetrics(SM_CYHSCROLL);
    FillRect(ps.hdc, &rt, GetStockObject(BLACK_BRUSH));
#endif
 */
    EndPaint(hWnd, &ps);
}