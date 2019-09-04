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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateBitmap (int,int,int,int,char*) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int GetPixel (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void Test_GetPixel_1bpp()
{
    HDC hdc;
    HBITMAP hbmp;
    char buffer[] = {0x80, 0x0};
    COLORREF color;

    hbmp = CreateBitmap(2,1,1,1,buffer);
    ok(hbmp != NULL, "Failed to create a monochrom bitmap...\n");
    hdc = CreateCompatibleDC(0);
    hbmp = SelectObject(hdc, hbmp);
    ok(hbmp != NULL, "Could not select the bitmap into the DC.\n");

    color = GetPixel(hdc, 0, 0);
    ok(color == 0xFFFFFF, "Wrong color at 0,0 : 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 1, 0);
    ok(color == 0, "Wrong color at 1,0 : 0x%08x\n", (UINT)color);

    SetBkColor(hdc, 0x0000FF);
    SetTextColor(hdc, 0x00FF00);
    color = GetPixel(hdc, 0, 0);
    ok(color == 0xFFFFFF, "Wrong color at 0,0 : 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 1, 0);
    ok(color == 0, "Wrong color at 1,0 : 0x%08x\n", (UINT)color);

    SetBkColor(hdc, 0x12345678);
    SetTextColor(hdc, 0x87654321);
    color = GetPixel(hdc, 0, 0);
    ok(color == 0xFFFFFF, "Wrong color at 0,0 : 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 1, 0);
    ok(color == 0, "Wrong color at 1,0 : 0x%08x\n", (UINT)color);

    hbmp = SelectObject(hdc, hbmp);
    DeleteObject(hbmp);
    DeleteDC(hdc);
}