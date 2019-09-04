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
typedef  int /*<<< orphan*/  HPALETTE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateTestPalette () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GdiPalGetEntries ; 
 int /*<<< orphan*/  NtGdiDoPalette (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int) ; 

void
Test_NtGdiDoPalette_GdiPalGetEntries(void)
{
    HPALETTE hPal;

    hPal = CreateTestPalette();

    /* Test pEntries = NULL */
    ok_long(NtGdiDoPalette(hPal, 0, 1, NULL, GdiPalGetEntries, TRUE), 0);
    ok_long(NtGdiDoPalette(hPal, 0, 1, NULL, GdiPalGetEntries, FALSE), 5);
    ok_long(NtGdiDoPalette(hPal, 2, 1, NULL, GdiPalGetEntries, FALSE), 5);
    ok_long(NtGdiDoPalette(hPal, 20, 1, NULL, GdiPalGetEntries, FALSE), 5);
    ok_long(NtGdiDoPalette(hPal, -20, 1, NULL, GdiPalGetEntries, FALSE), 5);
    ok_long(NtGdiDoPalette(hPal, 2, 0, NULL, GdiPalGetEntries, FALSE), 5);


// Test flags 0xf0

}