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
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int NtGdiRestoreDC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NtGdiSaveDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSpecialDCState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSpecialDCState2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST (int) ; 
 int /*<<< orphan*/  Test_IsSpecialState (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
Test_SaveRestore(HDC hdc, BOOL bMemDC)
{
    SetSpecialDCState(hdc);
    NtGdiSaveDC(hdc);
    SetSpecialDCState2(hdc);

    SetLastError(0);
    TEST(NtGdiRestoreDC(hdc, 2) == 0);
    TEST(GetLastError() == ERROR_INVALID_PARAMETER);

    SetLastError(0);
    TEST(NtGdiRestoreDC(hdc, 0) == 0);
    TEST(GetLastError() == ERROR_INVALID_PARAMETER);

    SetLastError(0);
    TEST(NtGdiRestoreDC(hdc, -2) == 0);
    TEST(GetLastError() == ERROR_INVALID_PARAMETER);

    SetLastError(0);
    TEST(NtGdiRestoreDC(hdc, 1) == 1);
    TEST(GetLastError() == 0);

    Test_IsSpecialState(hdc, bMemDC);
}