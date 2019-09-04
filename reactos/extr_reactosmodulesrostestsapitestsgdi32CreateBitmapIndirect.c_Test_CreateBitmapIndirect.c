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
struct TYPE_4__ {int bmBitsPixel; int bmHeight; int bmPlanes; int bmType; int bmWidth; int bmWidthBytes; scalar_t__ bmBits; } ;
typedef  scalar_t__ HBITMAP ;
typedef  TYPE_1__ BITMAP ;

/* Variables and functions */
 scalar_t__ CreateBitmapIndirect (TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

void Test_CreateBitmapIndirect()
{
    HBITMAP win_hBmp;
    BITMAP win_bitmap;

    win_bitmap.bmBits = 0;
    win_bitmap.bmBitsPixel = 1;
    win_bitmap.bmHeight = 0;
    win_bitmap.bmPlanes = 1;
    win_bitmap.bmType = 1;
    win_bitmap.bmWidth = 0;
    win_bitmap.bmWidthBytes = 2;
    win_hBmp = CreateBitmapIndirect(&win_bitmap);
    ok(win_hBmp != 0, "CreateBitmapIndirect failed\n");

    DeleteObject(win_hBmp);

    RtlZeroMemory(&win_bitmap,sizeof(BITMAP));
    win_bitmap.bmBits = 0;
    win_bitmap.bmBitsPixel = 1;
    win_bitmap.bmHeight = 0;
    win_bitmap.bmPlanes = 1;
    win_bitmap.bmType = 1;
    win_bitmap.bmWidth = 0;
    win_bitmap.bmWidthBytes = 1;
    win_hBmp = CreateBitmapIndirect(&win_bitmap);
    ok(win_hBmp == 0, "CreateBitmapIndirect succeeded\n");

    RtlZeroMemory(&win_bitmap,sizeof(BITMAP));
    win_bitmap.bmBits = 0;
    win_bitmap.bmBitsPixel = 1;
    win_bitmap.bmHeight = 0;
    win_bitmap.bmPlanes = 1;
    win_bitmap.bmType = 1;
    win_bitmap.bmWidth = 0;
    win_bitmap.bmWidthBytes = 3;
    win_hBmp = CreateBitmapIndirect(&win_bitmap);
    ok(win_hBmp == 0, "CreateBitmapIndirect succeeded\n");

    RtlZeroMemory(&win_bitmap,sizeof(BITMAP));
    win_bitmap.bmBits = 0;
    win_bitmap.bmBitsPixel = 1;
    win_bitmap.bmHeight = 0;
    win_bitmap.bmPlanes = 1;
    win_bitmap.bmType = 1;
    win_bitmap.bmWidth = 0;
    win_bitmap.bmWidthBytes = 4;
    win_hBmp = CreateBitmapIndirect(&win_bitmap);
    ok(win_hBmp != 0, "CreateBitmapIndirect failed\n");

    RtlZeroMemory(&win_bitmap,sizeof(BITMAP));
    win_bitmap.bmBits = 0;
    win_bitmap.bmBitsPixel = 8;
    win_bitmap.bmHeight = 0xF000;
    win_bitmap.bmPlanes = 1;
    win_bitmap.bmType = 1;
    win_bitmap.bmWidth = 0x8000;
    win_bitmap.bmWidthBytes = win_bitmap.bmWidth;
    win_hBmp = CreateBitmapIndirect(&win_bitmap);
    //ok(win_hBmp != 0, "CreateBitmapIndirect failed\n"); // fails on win 2003

    DeleteObject(win_hBmp);
}