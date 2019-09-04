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
 int /*<<< orphan*/  KEY_SOUND ; 
 int /*<<< orphan*/  NtUserSystemParametersInfo (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ QueryUserRegValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_GETBEEP ; 
 int /*<<< orphan*/  SPI_SETBEEP ; 
 int /*<<< orphan*/  TEST (int) ; 
 int /*<<< orphan*/  VAL_BEEP ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,char*) ; 

void
Test_SPI_SETBEEP(void)
{
    BOOL bOrig, bTemp = 0;
    WCHAR szReg[10];
    DWORD cbSize;

    /* Get original value */
    NtUserSystemParametersInfo(SPI_GETBEEP, 0, &bOrig, 0);

    /* Value 0 */
    NtUserSystemParametersInfo(SPI_SETBEEP, 0, NULL, SPIF_UPDATEINIFILE);
    NtUserSystemParametersInfo(SPI_GETBEEP, 0, &bTemp, 0);
    TEST(bTemp == 0);
    cbSize = sizeof(szReg);
    TEST(QueryUserRegValueW(KEY_SOUND, VAL_BEEP, &szReg, &cbSize, NULL) == ERROR_SUCCESS);
    TEST(_wcsicmp(szReg, L"No") == 0);

    /* Value 1 */
    NtUserSystemParametersInfo(SPI_SETBEEP, 1, NULL, SPIF_UPDATEINIFILE);
    NtUserSystemParametersInfo(SPI_GETBEEP, 0, &bTemp, 0);
    TEST(bTemp == 1);
    cbSize = sizeof(szReg);
    TEST(QueryUserRegValueW(KEY_SOUND, VAL_BEEP, &szReg, &cbSize, NULL) == ERROR_SUCCESS);
    TEST(_wcsicmp(szReg, L"Yes") == 0);

    /* Value 2 */
    NtUserSystemParametersInfo(SPI_SETBEEP, 2, NULL, SPIF_UPDATEINIFILE);
    NtUserSystemParametersInfo(SPI_GETBEEP, 0, &bTemp, 0);
    TEST(bTemp == 1);
    cbSize = sizeof(szReg);
    TEST(QueryUserRegValueW(KEY_SOUND, VAL_BEEP, &szReg, &cbSize, NULL) == ERROR_SUCCESS);
    TEST(_wcsicmp(szReg, L"Yes") == 0);

    /* Restore original value */
    NtUserSystemParametersInfo(SPI_SETBEEP, 0, &bOrig, SPIF_UPDATEINIFILE);
}