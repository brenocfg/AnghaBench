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
struct TYPE_4__ {int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  BeginPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FrameRect (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GRAY_BRUSH ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WHITE_PEN ; 

__attribute__((used)) static void SB_OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rc;
    
    hdc = BeginPaint(hWnd, &ps);

    GetClientRect(hWnd, &rc);

    /* dark frame */
    rc.right += 1;
    rc.bottom -= 1;
    FrameRect(hdc, &rc, GetStockObject(GRAY_BRUSH));

    /* white highlight */
    SelectObject(hdc, GetStockObject(WHITE_PEN));
    MoveToEx(hdc, rc.right, 1, NULL);
    LineTo(hdc, 1, 1);
    LineTo(hdc, 1, rc.bottom - 1);

    
    MoveToEx(hdc, 0, rc.bottom, NULL);
    LineTo(hdc, rc.right, rc.bottom);

    EndPaint(hWnd, &ps);
}