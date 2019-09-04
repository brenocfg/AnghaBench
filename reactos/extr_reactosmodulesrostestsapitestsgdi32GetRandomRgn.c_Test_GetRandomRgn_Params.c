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
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/ * HRGN ;
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 int CLIPRGN ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateRectRgn (int,int,int,int) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int ERROR_INVALID_HANDLE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetRandomRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  ok_err (int) ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void Test_GetRandomRgn_Params()
{
    HDC hdc;
    HRGN hrgn;
    INT ret;

    hdc = CreateCompatibleDC(0);
    if (!hdc)
    {
        printf("Coun't create a dc\n");
        return;
    }

    hrgn = CreateRectRgn(11, 17, 23, 42);
    if (!hrgn)
    {
        printf("Coun't create a region\n");
        return;
    }

    SetLastError(0xbadbad00);
    ret = GetRandomRgn(NULL, NULL, 0);
    ok_int(ret, -1);
    ok((GetLastError() == 0xbadbad00) || (GetLastError() == ERROR_INVALID_HANDLE), "wrong error: %ld\n", GetLastError());

    SetLastError(0xbadbad00);
    ret = GetRandomRgn(NULL, NULL, CLIPRGN);
    ok_int(ret, -1);
    ok((GetLastError() == 0xbadbad00) || (GetLastError() == ERROR_INVALID_HANDLE), "wrong error: %ld\n", GetLastError());

    SetLastError(0xbadbad00);
    ret = GetRandomRgn(NULL, hrgn, 0);
    ok_int(ret, -1);
    ok((GetLastError() == 0xbadbad00) || (GetLastError() == ERROR_INVALID_HANDLE), "wrong error: %ld\n", GetLastError());

    SetLastError(0xbadbad00);
    ret = GetRandomRgn(NULL, hrgn, CLIPRGN);
    ok_int(ret, -1);
    ok((GetLastError() == 0xbadbad00) || (GetLastError() == ERROR_INVALID_HANDLE), "wrong error: %ld\n", GetLastError());

    SetLastError(0xbadbad00);
    ret = GetRandomRgn(hdc, NULL, 0);
    ok_int(ret, 0);
    ok_err(0xbadbad00);

    SetLastError(0xbadbad00);
    ret = GetRandomRgn(hdc, NULL, CLIPRGN);
    ok_int(ret, 0);
    ok_err(0xbadbad00);

    SetLastError(0xbadbad00);
    ret = GetRandomRgn(hdc, hrgn, 0);
    ok_int(ret, 0);
    ok_err(0xbadbad00);
#if 0 // this is vista+
    SetLastError(0xbadbad00);
    ret = GetRandomRgn(hdc, hrgn, 5);
    ok_int(ret, 1);
    ok_err(0xbadbad00);
#endif
    SetLastError(0xbadbad00);
    ret = GetRandomRgn(hdc, hrgn, 6);
    ok_int(ret, 0);
    ok_err(0xbadbad00);

    SetLastError(0xbadbad00);
    ret = GetRandomRgn(hdc, hrgn, 27);
    ok_int(ret, 0);
    ok_err(0xbadbad00);

    SetLastError(0xbadbad00);
    ret = GetRandomRgn(hdc, hrgn, -1);
    ok_int(ret, 0);
    ok_err(0xbadbad00);

    SetLastError(0xbadbad00);
    ret = GetRandomRgn(hdc, hrgn, CLIPRGN);
    ok_int(ret, 0);
    ok_err(0xbadbad00);

    SetLastError(0xbadbad00);
    ret = GetRandomRgn((HDC)0x123, hrgn, CLIPRGN);
    ok_int(ret, -1);
    ok((GetLastError() == 0xbadbad00) || (GetLastError() == ERROR_INVALID_HANDLE), "wrong error: %ld\n", GetLastError());

    DeleteObject(hrgn);
    DeleteDC(hdc);
}