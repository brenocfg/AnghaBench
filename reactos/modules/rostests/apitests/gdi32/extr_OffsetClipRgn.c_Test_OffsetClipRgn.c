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
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/ * HRGN ;
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CLIPRGN ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateRectRgn (int,int,int,int) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int ERROR ; 
 int ERROR_INVALID_HANDLE ; 
 int EqualRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GetLastError () ; 
 int GetRandomRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MM_ANISOTROPIC ; 
 int NULLREGION ; 
 int OffsetClipRgn (int /*<<< orphan*/ *,int,int) ; 
 int SIMPLEREGION ; 
 int SelectClipRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SetMapMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SetViewportExtEx (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int SetWindowExtEx (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_int (int,int) ; 

void Test_OffsetClipRgn()
{
    HDC hdc;
    HRGN hrgn, hrgn2;
    //RECT rect;

    hdc = CreateCompatibleDC(NULL);
    ok(hdc != 0, "CreateCompatibleDC failed, skipping tests.\n");
    if (!hdc) return;

    hrgn2 = CreateRectRgn(0, 0, 0, 0);

    /* Test NULL DC */
    SetLastError(0x12345);
    ok_int(OffsetClipRgn(NULL, 0, 0), ERROR);
    ok_int(GetLastError(), ERROR_INVALID_HANDLE);

    /* Test invalid DC */
    SetLastError(0x12345);
    ok_int(OffsetClipRgn((HDC)(ULONG_PTR)0x12345, 0, 0), ERROR);
    ok((GetLastError() == 0x12345) || (GetLastError() == ERROR_INVALID_HANDLE), "Expected 0x12345 or ERROR_INVALID_HANDLE, got %ld\n", GetLastError());
    SetLastError(0x12345);

    /* Test without a clip region set */
    SetLastError(0x12345);
    ok_int(SelectClipRgn(hdc, NULL), SIMPLEREGION);
    ok_int(OffsetClipRgn(hdc, 0, 0), SIMPLEREGION);
    ok_int(GetLastError(), 0x12345);
    SetLastError(0x12345);

    /* Set a clip region */
    hrgn = CreateRectRgn(10, 10, 20, 30);
    ok_int(SelectClipRgn(hdc, hrgn), NULLREGION);
    DeleteObject(hrgn);
    ok_int(OffsetClipRgn(hdc, 10, 10), SIMPLEREGION);
    ok_int(GetRandomRgn(hdc, hrgn2, CLIPRGN), 1);
    hrgn = CreateRectRgn(20, 20, 30, 40);
    ok_int(EqualRgn(hrgn, hrgn2), TRUE);

    /* Set different scaling */
    SetMapMode(hdc, MM_ANISOTROPIC);
    ok_int(SetViewportExtEx(hdc, 100, 100, NULL), 1);
    ok_int(SetWindowExtEx(hdc, 200, 50, NULL), 1);
    ok_int(OffsetClipRgn(hdc, 10, 10), SIMPLEREGION);
    ok_int(GetRandomRgn(hdc, hrgn2, CLIPRGN), 1);
    hrgn = CreateRectRgn(25, 40, 35, 60);
    ok_int(EqualRgn(hrgn, hrgn2), TRUE);

#if 0
    /* Set different scaling */
    SetMapMode(hdc, MM_ANISOTROPIC);
    ok_int(SetViewportExtEx(hdc, 100, 100, NULL), 1);
    ok_int(SetWindowExtEx(hdc, 80, 350, NULL), 1);
    ok_int(OffsetClipRgn(hdc, 10, 10), SIMPLEREGION);
    ok_int(GetRandomRgn(hdc, hrgn2, CLIPRGN), 1);
    hrgn = CreateRectRgn(33, 23, 43, 43);
    ok_int(EqualRgn(hrgn, hrgn2), TRUE);
#endif

    ok_int(GetLastError(), 0x12345);

}