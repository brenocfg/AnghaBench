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
typedef  int UINT_PTR ;
typedef  scalar_t__ HBITMAP ;
typedef  scalar_t__ HANDLE ;
typedef  int DIBSECTION ;
typedef  int BYTE ;
typedef  int BITMAP ;

/* Variables and functions */
 scalar_t__ CreateBitmap (int,int,int,int,int*) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FillMemory (int*,int,int) ; 
 scalar_t__ GDI_OBJECT_TYPE_BITMAP ; 
 scalar_t__ GetLastError () ; 
 int GetObjectA (scalar_t__,int,int*) ; 
 int GetObjectW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void
Test_Bitmap(void)
{
    HBITMAP hBitmap;
    BITMAP bitmap;
    DIBSECTION dibsection;
    BYTE bData[100] = {0};
    BYTE Buffer[100] = {48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,0};

    FillMemory(&bitmap, sizeof(BITMAP), 0x77);
    hBitmap = CreateBitmap(10,10,1,8,bData);
    ok(hBitmap != 0, "CreateBitmap failed, skipping tests.\n");
    if (!hBitmap) return;

    SetLastError(ERROR_SUCCESS);
    ok(GetObjectA((HANDLE)GDI_OBJECT_TYPE_BITMAP, 0, NULL) == sizeof(BITMAP), "\n");
    ok(GetObjectW((HANDLE)GDI_OBJECT_TYPE_BITMAP, 0, NULL) == sizeof(BITMAP), "\n");
    ok(GetObjectA((HANDLE)GDI_OBJECT_TYPE_BITMAP, sizeof(BITMAP), NULL) == sizeof(BITMAP), "\n");
    ok(GetLastError() == ERROR_SUCCESS, "\n");
    ok(GetObjectA(hBitmap, sizeof(DIBSECTION), NULL) == sizeof(BITMAP), "\n");
    ok(GetObjectA(hBitmap, 0, NULL) == sizeof(BITMAP), "\n");
    ok(GetObjectA((HANDLE)((UINT_PTR)hBitmap & 0x0000ffff), 0, NULL) == sizeof(BITMAP), "\n");
    ok(GetObjectW((HANDLE)((UINT_PTR)hBitmap & 0x0000ffff), 0, NULL) == sizeof(BITMAP), "\n");
    ok(GetLastError() == ERROR_SUCCESS, "\n");
    ok(GetObjectA(hBitmap, 5, NULL) == sizeof(BITMAP), "\n");
    ok(GetObjectA(hBitmap, -5, NULL) == sizeof(BITMAP), "\n");
    ok(GetObjectA(hBitmap, 0, Buffer) == 0, "\n");
    ok(GetObjectA(hBitmap, 5, Buffer) == 0, "\n");
    ok(GetLastError() == ERROR_SUCCESS, "\n");
    ok(GetObjectA(hBitmap, sizeof(BITMAP), &bitmap) == sizeof(BITMAP), "\n");
    ok(GetObjectA(hBitmap, sizeof(BITMAP)+2, &bitmap) == sizeof(BITMAP), "\n");
    ok(GetObjectA(hBitmap, sizeof(DIBSECTION), &dibsection) == sizeof(BITMAP), "\n");
    ok(GetObjectA(hBitmap, -5, &bitmap) == sizeof(BITMAP), "\n");
    ok(GetLastError() == ERROR_SUCCESS, "\n");
    ok(GetObjectA((HANDLE)GDI_OBJECT_TYPE_BITMAP, sizeof(BITMAP), &bitmap) == 0, "\n");
    ok(GetLastError() == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %ld\n", GetLastError());

    // todo: test invalid handle + buffer

    DeleteObject(hBitmap);
}