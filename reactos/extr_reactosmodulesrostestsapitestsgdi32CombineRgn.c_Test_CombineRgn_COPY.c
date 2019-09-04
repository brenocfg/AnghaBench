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
typedef  int /*<<< orphan*/ * HRGN ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_PEN ; 
 int /*<<< orphan*/  CombineRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateRectRgn (int,int,int,int) ; 
 int /*<<< orphan*/  ERROR ; 
 int ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  EqualRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GetLastError () ; 
 int /*<<< orphan*/ * GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGN_COPY ; 
 int /*<<< orphan*/  SIMPLEREGION ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Test_CombineRgn_COPY()
{
    HRGN hrgn1, hrgn2, hrgn3;

    hrgn1 = CreateRectRgn(0, 0, 0, 0);
    hrgn2 = CreateRectRgn(0, 0, 10, 10);
    hrgn3 = CreateRectRgn(5, 5, 20, 20);

    SetLastError(0xbadbabe);
    ok_long(CombineRgn(NULL, NULL, NULL, RGN_COPY), ERROR);
    ok_long(CombineRgn(NULL, hrgn1, NULL, RGN_COPY), ERROR);
    ok_long(CombineRgn(NULL, NULL, hrgn1, RGN_COPY), ERROR);
    ok_long(CombineRgn(NULL, hrgn1, hrgn2, RGN_COPY), ERROR);
    ok((GetLastError() == 0xbadbabe) || (GetLastError() == ERROR_INVALID_HANDLE), "wrong error: %ld\n", GetLastError());

    ok_long(CombineRgn(hrgn1, hrgn2, hrgn3, RGN_COPY), SIMPLEREGION);
    ok(EqualRgn(hrgn1, hrgn2), "Region is not correct\n");

    ok_long(CombineRgn(hrgn1, hrgn1, NULL, RGN_COPY), SIMPLEREGION);
    ok(EqualRgn(hrgn1, hrgn2), "Region is not correct\n");

    ok_long(CombineRgn(hrgn1, hrgn3, GetStockObject(BLACK_PEN), RGN_COPY), SIMPLEREGION);
    ok(EqualRgn(hrgn1, hrgn3), "Region is not correct\n");

    ok_long(CombineRgn(hrgn1, GetStockObject(BLACK_PEN), hrgn2, RGN_COPY), ERROR);
    ok(EqualRgn(hrgn1, hrgn3), "Region is not correct\n");

    ok_long(CombineRgn(hrgn1, NULL, hrgn2, RGN_COPY), ERROR);
    ok(EqualRgn(hrgn1, hrgn3), "Region is not correct\n");

    ok_long(CombineRgn(hrgn1, NULL, NULL, RGN_COPY), ERROR);
    ok(EqualRgn(hrgn1, hrgn3), "Region is not correct\n");

    ok((GetLastError() == 0xbadbabe) || (GetLastError() == ERROR_INVALID_HANDLE), "wrong error: %ld\n", GetLastError());

}