#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bmi ;
struct TYPE_8__ {int biSize; int biBitCount; int biPlanes; int /*<<< orphan*/  biCompression; void* biWidth; void* biHeight; } ;
struct TYPE_10__ {TYPE_1__ bmiHeader; } ;
struct TYPE_9__ {void* member_2; void* member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ RECT ;
typedef  void* INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  TYPE_3__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateDIBSection (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int DT_CENTER ; 
 int DT_SINGLELINE ; 
 int DT_VCENTER ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawTextA (int /*<<< orphan*/ ,char const*,int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HBITMAP create_bitmap(INT cx, INT cy, COLORREF color, const char *comment)
{
    HDC hdc;
    BITMAPINFO bmi;
    HBITMAP hbmp, hbmp_old;
    HBRUSH hbrush;
    RECT rc = { 0, 0, cx, cy };

    hdc = CreateCompatibleDC(0);

    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biHeight = cx;
    bmi.bmiHeader.biWidth = cy;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    hbmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, NULL, NULL, 0);

    hbmp_old = SelectObject(hdc, hbmp);

    hbrush = CreateSolidBrush(color);
    FillRect(hdc, &rc, hbrush);
    DeleteObject(hbrush);

    DrawTextA(hdc, comment, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    SelectObject(hdc, hbmp_old);
    DeleteDC(hdc);

    return hbmp;
}