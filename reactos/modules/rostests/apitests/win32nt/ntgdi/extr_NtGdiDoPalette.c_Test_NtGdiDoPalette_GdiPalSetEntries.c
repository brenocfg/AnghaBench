#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  palEntries2 ;
typedef  int /*<<< orphan*/  palEntries ;
struct TYPE_6__ {int member_0; int member_1; int member_2; int member_3; int /*<<< orphan*/  peFlags; int /*<<< orphan*/  peBlue; int /*<<< orphan*/  peGreen; int /*<<< orphan*/  peRed; } ;
typedef  TYPE_1__ PALETTEENTRY ;
typedef  scalar_t__ HPALETTE ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 scalar_t__ CreateTestPalette () ; 
 int /*<<< orphan*/  DEFAULT_PALETTE ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GdiPalGetEntries ; 
 int /*<<< orphan*/  GdiPalSetEntries ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtGdiDoPalette (scalar_t__,int,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SelectPalette (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcmp (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int) ; 

void
Test_NtGdiDoPalette_GdiPalSetEntries(void)
{
    HDC hDC;
    HPALETTE hPal, hOldPal;
    PALETTEENTRY palEntries[5] = {
        {0,0,0,0},
        {0xff,0xff,0xff,0},
        {0x33,0x66,0x99,0},
        {0x25,0x84,0x14,0},
        {0x12,0x34,0x56,0x11}};
    PALETTEENTRY palEntries2[5];

    hPal = CreateTestPalette();

    /* Test invalid handle */
    SetLastError(ERROR_SUCCESS);
    ok_long(NtGdiDoPalette((HPALETTE)23, 0, 1, palEntries, GdiPalSetEntries, TRUE), 0);
    ok_long(GetLastError(), ERROR_SUCCESS);

    /* Test system palette */
    ok_long(NtGdiDoPalette(GetStockObject(DEFAULT_PALETTE), 0, 1, palEntries, GdiPalSetEntries, TRUE), 0);
    ok_long(GetLastError(), ERROR_SUCCESS);

    ok_long(NtGdiDoPalette(hPal, 0, 1, palEntries, GdiPalSetEntries, TRUE), 1);
    ok_long(NtGdiDoPalette(hPal, 0, 2, palEntries, GdiPalSetEntries, TRUE), 2);
    ok_long(NtGdiDoPalette(hPal, 0, 3, palEntries, GdiPalSetEntries, TRUE), 3);
    ok_long(NtGdiDoPalette(hPal, 0, 5, palEntries, GdiPalSetEntries, TRUE), 5);
    ok_long(NtGdiDoPalette(hPal, 0, 6, palEntries, GdiPalSetEntries, TRUE), 5);
    ok_long(NtGdiDoPalette(hPal, 3, 6, palEntries, GdiPalSetEntries, TRUE), 2);
//  TEST(NtGdiDoPalette(hPal, 4, 23247, palEntries, GdiPalSetEntries, TRUE), 0);

    /* Test bInbound, FALSE */
    NtGdiDoPalette(hPal, 0, 5, palEntries, GdiPalSetEntries, TRUE);
    ZeroMemory(palEntries2, sizeof(palEntries2));
    ok_long(NtGdiDoPalette(hPal, 0, 5, palEntries2, GdiPalSetEntries, FALSE), 5);
    /* we should get the old values returned in our buffer! */
    ok_int(memcmp(palEntries2, palEntries, sizeof(palEntries)), 0);

    /* check what we have in our palette now */
    ZeroMemory(palEntries2, sizeof(palEntries2));
    ok_long(NtGdiDoPalette(hPal, 0, 5, palEntries2, GdiPalGetEntries, FALSE), 5);
    ok_int(memcmp(palEntries2, palEntries, sizeof(palEntries)), 0);

    ok_long(NtGdiDoPalette(hPal, 0, 4, palEntries2, GdiPalSetEntries, TRUE), 4);
    ok_long(GetLastError(), ERROR_SUCCESS);

    /* Test if entries are set correctly */
    hPal = CreateTestPalette();
    NtGdiDoPalette(hPal, 0, 5, palEntries, GdiPalSetEntries, TRUE);
    NtGdiDoPalette(hPal, 0, 5, palEntries2, GdiPalGetEntries, FALSE);
    ok_int(palEntries2[0].peRed, 0);
    ok_int(palEntries2[0].peGreen, 0);
    ok_int(palEntries2[0].peBlue, 0);
    ok_int(palEntries2[0].peFlags, 0);

    /* Test that the buffer was not changed */


    /* Test with palette selected into dc */
    hDC = CreateCompatibleDC(NULL);
    hOldPal = SelectPalette(hDC, hPal, 0);
    ok_long(NtGdiDoPalette(hPal, 0, 4, palEntries, GdiPalSetEntries, TRUE), 4);
    SelectPalette(hDC, hOldPal, 0);

    /* Test pEntries = NULL */
    ok_long(NtGdiDoPalette(hPal, 0, 1, NULL, GdiPalGetEntries, TRUE), 0);

}