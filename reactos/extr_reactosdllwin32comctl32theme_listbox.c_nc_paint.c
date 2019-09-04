#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_6__ {int left; int top; scalar_t__ bottom; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HTHEME ;
typedef  scalar_t__ HRGN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CombineRgn (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateRectRgn (int,int,scalar_t__,scalar_t__) ; 
 int DCX_INTERSECTRGN ; 
 int DCX_WINDOW ; 
 int /*<<< orphan*/  DefWindowProcW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawThemeBackground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawThemeParentBackground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GetDCEx (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ IsThemeBackgroundPartiallyTransparent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  RGN_AND ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXEDGE ; 
 int /*<<< orphan*/  SM_CYEDGE ; 
 int /*<<< orphan*/  WM_NCPAINT ; 
 int WS_EX_CLIENTEDGE ; 

__attribute__((used)) static void nc_paint (HTHEME theme, HWND hwnd, HRGN region)
{
    HRGN cliprgn = region;
    DWORD exStyle = GetWindowLongW (hwnd, GWL_EXSTYLE);
    if (exStyle & WS_EX_CLIENTEDGE)
    {
        HDC dc;
        RECT r;
        int cxEdge = GetSystemMetrics (SM_CXEDGE),
            cyEdge = GetSystemMetrics (SM_CYEDGE);
    
        GetWindowRect(hwnd, &r);
    
        /* New clipping region passed to default proc to exclude border */
        cliprgn = CreateRectRgn (r.left + cxEdge, r.top + cyEdge,
            r.right - cxEdge, r.bottom - cyEdge);
        if (region != (HRGN)1)
            CombineRgn (cliprgn, cliprgn, region, RGN_AND);
        OffsetRect(&r, -r.left, -r.top);
    
#ifdef __REACTOS__ /* r73789 */
        dc = GetWindowDC(hwnd);
        /* Exclude client part */
        ExcludeClipRect(dc, r.left + cxEdge, r.top + cyEdge,
            r.right - cxEdge, r.bottom -cyEdge);
#else
        dc = GetDCEx(hwnd, region, DCX_WINDOW|DCX_INTERSECTRGN);
        OffsetRect(&r, -r.left, -r.top);
#endif
    
        if (IsThemeBackgroundPartiallyTransparent (theme, 0, 0))
            DrawThemeParentBackground(hwnd, dc, &r);
        DrawThemeBackground (theme, dc, 0, 0, &r, 0);
        ReleaseDC(hwnd, dc);
    }

    /* Call default proc to get the scrollbars etc. painted */
    DefWindowProcW (hwnd, WM_NCPAINT, (WPARAM)cliprgn, 0);
}