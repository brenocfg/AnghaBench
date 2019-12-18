#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LPPOINT ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleBitmap (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateRectRgn (int,int,int,int) ; 
 int /*<<< orphan*/  DPtoLP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetRandomRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetRgnBox (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MoveWindow (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSRGN ; 
 int /*<<< orphan*/  SelectClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghdcWindow ; 
 int /*<<< orphan*/  ghwnd ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok_long (int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void Test_GetRandomRgn_SYSRGN()
{
    HDC hdc;
    HRGN hrgn1, hrgn2;
    INT ret;
    RECT rect, rect2;
    HBITMAP hbmp;

    hrgn1 = CreateRectRgn(11, 17, 23, 42);
    if (!hrgn1)
    {
        printf("Coun't create a region\n");
        return;
    }

    hdc = CreateCompatibleDC(0);
    if (!hdc)
    {
        printf("Coun't create a dc\n");
        return;
    }

    ret = GetRandomRgn(hdc, hrgn1, SYSRGN);
    ok_int(ret, 1);
    GetRgnBox(hrgn1, &rect);
    ok_long(rect.left, 0);
    ok_long(rect.top, 0);
    ok_long(rect.right, 1);
    ok_long(rect.bottom, 1);

    hrgn2 = CreateRectRgn(1, 2, 3, 4);
    SelectClipRgn(hdc, hrgn2);
    DeleteObject(hrgn2);
    ret = GetRandomRgn(hdc, hrgn1, SYSRGN);
    ok_int(ret, 1);
    GetRgnBox(hrgn1, &rect);
    ok_long(rect.left, 0);
    ok_long(rect.top, 0);
    ok_long(rect.right, 1);
    ok_long(rect.bottom, 1);

    hbmp = CreateCompatibleBitmap(hdc, 4, 7);
    SelectObject(hdc, hbmp);
    ret = GetRandomRgn(hdc, hrgn1, SYSRGN);
    ok_int(ret, 1);
    GetRgnBox(hrgn1, &rect);
    ok_long(rect.left, 0);
    ok_long(rect.top, 0);
    ok_long(rect.right, 4);
    ok_long(rect.bottom, 7);
    DeleteObject(hbmp);

    MoveWindow(ghwnd, 100, 100, 100, 100, 0);
    ret = GetRandomRgn(ghdcWindow, hrgn1, SYSRGN);
    ok_int(ret, 1);
    GetRgnBox(hrgn1, &rect);
    DPtoLP(ghdcWindow, (LPPOINT)&rect, 2);
#if 0 // FIXME: this needs calculation
    ok_long(rect.left, 104);
    ok_long(rect.top, 124);
    ok_long(rect.right, 209);
    ok_long(rect.bottom, 196);
#endif

    MoveWindow(ghwnd, 200, 400, 200, 200, 0);

    ret = GetRandomRgn(ghdcWindow, hrgn1, SYSRGN);
    ok_int(ret, 1);
    GetRgnBox(hrgn1, &rect2);
    DPtoLP(ghdcWindow, (LPPOINT)&rect2, 2);
#if 0 // FIXME: this needs calculation
    ok_long(rect2.left, rect.left + 100);
    ok_long(rect2.top, rect.top + 300);
    ok_long(rect2.right, rect.right + 200 - 13);
    ok_long(rect2.bottom, rect.bottom + 400);
#endif

    DeleteObject(hrgn1);
    DeleteDC(hdc);

}