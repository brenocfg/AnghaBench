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
typedef  int /*<<< orphan*/  szReg ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_MOUSE ; 
 int /*<<< orphan*/  NtUserSystemParametersInfo (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ QueryUserRegValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SM_SWAPBUTTON ; 
 int /*<<< orphan*/  SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_SETMOUSEBUTTONSWAP ; 
 int /*<<< orphan*/  TEST (int) ; 
 int /*<<< orphan*/  VAL_SWAP ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,char*) ; 

void
Test_SPI_SETMOUSEBUTTONSWAP(void)
{
    BOOL bOrig, bTemp = 0;
    WCHAR szReg[10];
    DWORD cbSize;

    /* Get original value */
    bOrig = GetSystemMetrics(SM_SWAPBUTTON);

    /* Value 0 */
    NtUserSystemParametersInfo(SPI_SETMOUSEBUTTONSWAP, 0, NULL, SPIF_UPDATEINIFILE);
    bTemp = GetSystemMetrics(SM_SWAPBUTTON);
    TEST(bTemp == 0);
    cbSize = sizeof(szReg);
    TEST(QueryUserRegValueW(KEY_MOUSE, VAL_SWAP, &szReg, &cbSize, NULL) == ERROR_SUCCESS);
    TEST(_wcsicmp(szReg, L"0") == 0);

    /* Value 1 */
    NtUserSystemParametersInfo(SPI_SETMOUSEBUTTONSWAP, 1, NULL, SPIF_UPDATEINIFILE);
    bTemp = GetSystemMetrics(SM_SWAPBUTTON);
    TEST(bTemp == 1);
    cbSize = sizeof(szReg);
    TEST(QueryUserRegValueW(KEY_MOUSE, VAL_SWAP, &szReg, &cbSize, NULL) == ERROR_SUCCESS);
    TEST(_wcsicmp(szReg, L"1") == 0);

    /* Value 2 */
    NtUserSystemParametersInfo(SPI_SETMOUSEBUTTONSWAP, 2, NULL, SPIF_UPDATEINIFILE);
    bTemp = GetSystemMetrics(SM_SWAPBUTTON);
    TEST(bTemp == 1);
    cbSize = sizeof(szReg);
    TEST(QueryUserRegValueW(KEY_MOUSE, VAL_SWAP, &szReg, &cbSize, NULL) == ERROR_SUCCESS);
    TEST(_wcsicmp(szReg, L"2") == 0);

    /* Value -1 */
    NtUserSystemParametersInfo(SPI_SETMOUSEBUTTONSWAP, -1, NULL, SPIF_UPDATEINIFILE);
    bTemp = GetSystemMetrics(SM_SWAPBUTTON);
    TEST(bTemp == 1);
    cbSize = sizeof(szReg);
    TEST(QueryUserRegValueW(KEY_MOUSE, VAL_SWAP, &szReg, &cbSize, NULL) == ERROR_SUCCESS);
    TEST(_wcsicmp(szReg, L"-1") == 0);

    /* Restore original value */
    NtUserSystemParametersInfo(SPI_SETMOUSEBUTTONSWAP, bOrig, 0, SPIF_UPDATEINIFILE);


}