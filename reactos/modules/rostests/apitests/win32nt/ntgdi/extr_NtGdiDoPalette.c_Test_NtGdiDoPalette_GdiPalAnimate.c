#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int member_0; int member_1; int member_2; int member_3; int peRed; int peGreen; int peBlue; int peFlags; } ;
typedef  TYPE_1__ PALETTEENTRY ;
typedef  int /*<<< orphan*/  HPALETTE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateTestPalette () ; 
 int /*<<< orphan*/  DEFAULT_PALETTE ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GdiPalAnimate ; 
 int /*<<< orphan*/  GdiPalGetEntries ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtGdiDoPalette (int /*<<< orphan*/ ,int,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PC_EXPLICIT ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok_int (int,int) ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int) ; 

void
Test_NtGdiDoPalette_GdiPalAnimate(void)
{
    HPALETTE hPal;
    PALETTEENTRY palEntries[5] = {
        {0,0,0,0},
        {0xff,0xff,0xff,0},
        {0x33,0x66,0x99,0},
        {0x25,0x84,0x14,0},
        {0x12,0x34,0x56,0x11}};
    PALETTEENTRY palEntries2[5];

    /* Test stock palette */
    SetLastError(ERROR_SUCCESS);
    ok_long(NtGdiDoPalette(GetStockObject(DEFAULT_PALETTE), 0, 1, palEntries, GdiPalAnimate, FALSE), 0);
    ok_long(GetLastError(), ERROR_SUCCESS);


    /* Test pEntries = NULL */
    hPal = CreateTestPalette();
    ok_long(NtGdiDoPalette(hPal, 0, 1, NULL, GdiPalAnimate, TRUE), 0);
    ok_long(NtGdiDoPalette(hPal, 0, 1, NULL, GdiPalAnimate, FALSE), 0);
    DeleteObject(hPal);

    /* Test PC_RESERVED */
    hPal = CreateTestPalette();
    ok_long(NtGdiDoPalette(hPal, 0, 5, palEntries, GdiPalAnimate, TRUE), 2);
    DeleteObject(hPal);

    hPal = CreateTestPalette();
    ok_long(NtGdiDoPalette(hPal, 1, 5, palEntries, GdiPalAnimate, TRUE), 2);
    DeleteObject(hPal);

    hPal = CreateTestPalette();
    ok_long(NtGdiDoPalette(hPal, 2, 5, palEntries, GdiPalAnimate, TRUE), 1);
    DeleteObject(hPal);

    hPal = CreateTestPalette();
    ok_long(NtGdiDoPalette(hPal, 3, 5, palEntries, GdiPalAnimate, TRUE), 1);
    DeleteObject(hPal);

    hPal = CreateTestPalette();
    ok_long(NtGdiDoPalette(hPal, 4, 5, palEntries, GdiPalAnimate, TRUE), 0);
    DeleteObject(hPal);

    hPal = CreateTestPalette();
    ok_long(NtGdiDoPalette(hPal, 5, 5, palEntries, GdiPalAnimate, TRUE), 0);
    DeleteObject(hPal);

    hPal = CreateTestPalette();
    ok_long(NtGdiDoPalette(hPal, 0, 5, palEntries, GdiPalAnimate, FALSE), 2);
    DeleteObject(hPal);

    hPal = CreateTestPalette();
    ok_long(NtGdiDoPalette(hPal, 3, 5, palEntries, GdiPalAnimate, FALSE), 1);
    DeleteObject(hPal);

    /* Test if entries are set correctly */
    hPal = CreateTestPalette();
    NtGdiDoPalette(hPal, 0, 5, palEntries, GdiPalAnimate, TRUE);
    NtGdiDoPalette(hPal, 0, 5, palEntries2, GdiPalGetEntries, FALSE);
    ok_int(palEntries2[0].peRed, 1);
    ok_int(palEntries2[0].peGreen, 2);
    ok_int(palEntries2[0].peBlue, 3);
    ok_int(palEntries2[0].peFlags, 0);
    ok_int(palEntries2[1].peRed, palEntries[1].peRed);
    ok_int(palEntries2[1].peGreen, palEntries[1].peGreen);
    ok_int(palEntries2[1].peBlue, palEntries[1].peBlue);
    ok_int(palEntries2[1].peFlags, palEntries[1].peFlags);
    ok_int(palEntries2[2].peRed, 11);
    ok_int(palEntries2[2].peGreen, 55);
    ok_int(palEntries2[2].peBlue, 77);
    ok_int(palEntries2[2].peFlags, PC_EXPLICIT);
    ok_int(palEntries2[3].peRed, palEntries[3].peRed);
    ok_int(palEntries2[3].peGreen, palEntries[3].peGreen);
    ok_int(palEntries2[3].peBlue, palEntries[3].peBlue);
    ok_int(palEntries2[3].peFlags, palEntries[3].peFlags);
    DeleteObject(hPal);

}