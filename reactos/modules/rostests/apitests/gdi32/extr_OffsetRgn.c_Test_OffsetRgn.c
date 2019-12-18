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
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  COMPLEXREGION ; 
 int /*<<< orphan*/  CombineRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateRectRgn (int,int,int,int) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int INT_MIN ; 
 int /*<<< orphan*/  NULLREGION ; 
 int /*<<< orphan*/  OffsetRgn (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  RGN_OR ; 
 int /*<<< orphan*/  RGN_XOR ; 
 int /*<<< orphan*/  SIMPLEREGION ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Test_OffsetRgn()
{
    HRGN hrgn1, hrgn2;
    HDC hdc;

    hrgn1 = CreateRectRgn(0, 0, 0, 0);
    ok(hrgn1 != NULL, "CreateRectRgn failed\n");
    ok_int(OffsetRgn(hrgn1, INT_MIN + 10, 10), NULLREGION);
    ok_int(OffsetRgn(hrgn1, 0xF000000, 0xF000000), NULLREGION);
    DeleteObject(hrgn1);

    hrgn1 = CreateRectRgn(0, 0, 100, 100);
    ok(hrgn1 != NULL, "CreateRectRgn failed\n");
    ok_int(OffsetRgn(hrgn1, 10, 10), SIMPLEREGION);
    ok_int(OffsetRgn(hrgn1, 0x8000000 - 110, 10), ERROR);
    ok_int(OffsetRgn(hrgn1, 0x8000000 - 111, 10), SIMPLEREGION);
    DeleteObject(hrgn1);

    hrgn1 = CreateRectRgn(0, 0, 100, 100);
    ok(hrgn1 != NULL, "CreateRectRgn failed\n");
    ok_int(OffsetRgn(hrgn1, -10, 10), SIMPLEREGION);
    ok_int(OffsetRgn(hrgn1, -(0x8000000 - 9), 10), ERROR);
    ok_int(OffsetRgn(hrgn1, -(0x8000000 - 10), 10), SIMPLEREGION);
    DeleteObject(hrgn1);

    hrgn1 = CreateRectRgn(0, 0, 10, 10);
    hrgn2 = CreateRectRgn(1000, 20, 1010, 30);
    ok_int(CombineRgn(hrgn1, hrgn1, hrgn2, RGN_OR), COMPLEXREGION);
    ok_int(OffsetRgn(hrgn1, 0x8000000 - 100, 10), ERROR);
    ok_int(CombineRgn(hrgn1, hrgn1, hrgn2, RGN_XOR), SIMPLEREGION);
    DeleteObject(hrgn2);
    hrgn2 = CreateRectRgn(0, 0, 10, 10);
    ok_int(CombineRgn(hrgn1, hrgn1, hrgn2, RGN_XOR), NULLREGION);

    hrgn1 = CreateRectRgn(0, 0, 0, 0);
    hdc = CreateCompatibleDC(NULL);
    ok_int(GetClipRgn(hdc, hrgn1), 0);
    ok_int(OffsetRgn(hrgn1, 10, 10), NULLREGION);

}