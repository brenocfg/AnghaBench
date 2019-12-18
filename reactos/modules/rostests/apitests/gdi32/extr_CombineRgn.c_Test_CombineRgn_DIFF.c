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
 int /*<<< orphan*/  COMPLEXREGION ; 
 int /*<<< orphan*/  CombineRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateRectRgn (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ERROR ; 
 int ERROR_INVALID_HANDLE ; 
 int GetLastError () ; 
 int /*<<< orphan*/ * GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULLREGION ; 
 int /*<<< orphan*/  RGN_DIFF ; 
 int /*<<< orphan*/  SIMPLEREGION ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Test_CombineRgn_DIFF()
{
    HRGN hrgn1, hrgn2, hrgn3;

    hrgn1 = CreateRectRgn(0, 0, 0, 0);
    hrgn2 = CreateRectRgn(0, 0, 10, 10);
    hrgn3 = CreateRectRgn(5, 0, 10, 5);

    SetLastError(0xbadbabe);
    ok_long(CombineRgn(NULL, NULL, NULL, RGN_DIFF), ERROR);
    ok_long(CombineRgn(hrgn1, NULL, NULL, RGN_DIFF), ERROR);
    ok_long(CombineRgn(hrgn1, hrgn2, NULL, RGN_DIFF), ERROR);
    ok_long(CombineRgn(hrgn1, NULL, hrgn2, RGN_DIFF), ERROR);
    ok_long(CombineRgn(hrgn1, GetStockObject(BLACK_PEN), hrgn2, RGN_DIFF), ERROR);
    ok_long(CombineRgn(hrgn1, hrgn2, GetStockObject(BLACK_PEN), RGN_DIFF), ERROR);
    ok((GetLastError() == 0xbadbabe) || (GetLastError() == ERROR_INVALID_HANDLE), "wrong error: %ld\n", GetLastError());

    ok_long(CombineRgn(hrgn1, hrgn1, hrgn1, RGN_DIFF), NULLREGION);
    ok_long(CombineRgn(hrgn1, hrgn2, hrgn2, RGN_DIFF), NULLREGION);
    ok_long(CombineRgn(hrgn1, hrgn1, hrgn2, RGN_DIFF), NULLREGION);

    ok_long(CombineRgn(hrgn1, hrgn2, hrgn1, RGN_DIFF), SIMPLEREGION);
    ok_long(CombineRgn(hrgn1, hrgn2, hrgn3, RGN_DIFF), COMPLEXREGION);
    ok_long(CombineRgn(hrgn1, hrgn1, hrgn3, RGN_DIFF), COMPLEXREGION);
    ok_long(CombineRgn(hrgn1, hrgn1, hrgn2, RGN_DIFF), NULLREGION);


}