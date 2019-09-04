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
typedef  int UINT_PTR ;
struct TYPE_8__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_7; int member_8; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; } ;
struct TYPE_10__ {TYPE_1__ member_0; } ;
struct TYPE_9__ {scalar_t__ bmBits; int /*<<< orphan*/  bmBitsPixel; int /*<<< orphan*/  bmPlanes; int /*<<< orphan*/  bmWidthBytes; int /*<<< orphan*/  bmHeight; int /*<<< orphan*/  bmWidth; int /*<<< orphan*/  bmType; } ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBITMAP ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_2__ DIBSECTION ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_3__ BITMAPINFO ;
typedef  TYPE_2__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 scalar_t__ CreateDIBSection (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FillMemory (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetObject (scalar_t__,int,TYPE_2__*) ; 
 int GetObjectA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int GetObjectW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int) ; 

void
Test_Dibsection(void)
{
    BITMAPINFO bmi = {{sizeof(BITMAPINFOHEADER), 10, 9, 1, 16, BI_RGB, 0, 10, 10, 0,0}};
    HBITMAP hBitmap;
    BITMAP bitmap;
    DIBSECTION dibsection;
    PVOID pData;
    HDC hDC;

    FillMemory(&dibsection, sizeof(DIBSECTION), 0x77);
    hDC = GetDC(0);
    hBitmap = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, &pData, NULL, 0);
    ok(hBitmap != 0, "CreateDIBSection failed with %ld, skipping tests.\n", GetLastError());
    if (!hBitmap) return;

    ok(GetObjectA((HANDLE)((UINT_PTR)hBitmap & 0x0000ffff), 0, NULL) == sizeof(BITMAP), "\n");
    ok(GetObjectW((HANDLE)((UINT_PTR)hBitmap & 0x0000ffff), 0, NULL) == sizeof(BITMAP), "\n");

    SetLastError(ERROR_SUCCESS);
    ok_long(GetObject(hBitmap, sizeof(DIBSECTION), NULL), sizeof(BITMAP));
    ok_long(GetObject(hBitmap, 0, NULL), sizeof(BITMAP));
    ok_long(GetObject(hBitmap, 5, NULL), sizeof(BITMAP));
    ok_long(GetObject(hBitmap, -5, NULL), sizeof(BITMAP));
    ok_long(GetObject(hBitmap, 0, &dibsection), 0);
    ok_long(GetObject(hBitmap, 5, &dibsection), 0);
    ok_long(GetObject(hBitmap, sizeof(BITMAP), &bitmap), sizeof(BITMAP));
    ok_long(GetObject(hBitmap, sizeof(BITMAP)+2, &bitmap), sizeof(BITMAP));
    ok_long(bitmap.bmType, 0);
    ok_long(bitmap.bmWidth, 10);
    ok_long(bitmap.bmHeight, 9);
    ok_long(bitmap.bmWidthBytes, 20);
    ok_long(bitmap.bmPlanes, 1);
    ok_long(bitmap.bmBitsPixel, 16);
    ok(bitmap.bmBits == pData, "\n");
    ok_long(GetObject(hBitmap, sizeof(DIBSECTION), &dibsection), sizeof(DIBSECTION));
    ok_long(GetObject(hBitmap, sizeof(DIBSECTION)+2, &dibsection), sizeof(DIBSECTION));
    ok_long(GetObject(hBitmap, -5, &dibsection), sizeof(DIBSECTION));
    ok_err(ERROR_SUCCESS);
    DeleteObject(hBitmap);
    ReleaseDC(0, hDC);
}