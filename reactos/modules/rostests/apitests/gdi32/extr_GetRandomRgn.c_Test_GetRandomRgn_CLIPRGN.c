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
struct TYPE_3__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CLIPRGN ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateRectRgn (int,int,int,int) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetRandomRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetRgnBox (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MoveWindow (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghdcWindow ; 
 int /*<<< orphan*/  ghwnd ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void Test_GetRandomRgn_CLIPRGN()
{
    HDC hdc;
    HRGN hrgn1, hrgn2;
    INT ret;
    RECT rect;

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

    ret = GetRandomRgn(hdc, hrgn1, CLIPRGN);
    ok_int(ret, 0);
    GetRgnBox(hrgn1, &rect);
    ok_long(rect.left, 11);
    ok_long(rect.top, 17);
    ok_long(rect.right, 23);
    ok_long(rect.bottom, 42);

    hrgn2 = CreateRectRgn(1, 2, 3, 4);
    SelectClipRgn(hdc, hrgn2);
    DeleteObject(hrgn2);
    ret = GetRandomRgn(hdc, hrgn1, CLIPRGN);
    ok_int(ret, 1);
    GetRgnBox(hrgn1, &rect);
    ok_long(rect.left, 1);
    ok_long(rect.top, 2);
    ok_long(rect.right, 3);
    ok_long(rect.bottom, 4);

    hrgn2 = CreateRectRgn(2, 3, 4, 5);
    SelectClipRgn(ghdcWindow, hrgn2);
    DeleteObject(hrgn2);
    ret = GetRandomRgn(ghdcWindow, hrgn1, CLIPRGN);
    ok_int(ret, 1);
    GetRgnBox(hrgn1, &rect);
    ok_long(rect.left, 2);
    ok_long(rect.top, 3);
    ok_long(rect.right, 4);
    ok_long(rect.bottom, 5);

    MoveWindow(ghwnd, 200, 400, 100, 100, 0);

    ret = GetRandomRgn(ghdcWindow, hrgn1, CLIPRGN);
    ok_int(ret, 1);
    GetRgnBox(hrgn1, &rect);
    ok_long(rect.left, 2);
    ok_long(rect.top, 3);
    ok_long(rect.right, 4);
    ok_long(rect.bottom, 5);


    DeleteObject(hrgn1);
    DeleteDC(hdc);
}