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
typedef  scalar_t__ WCHAR ;
typedef  scalar_t__ UNICODE_STRING ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ GetLastError () ; 
 int MAX_PATH ; 
 int NtUserSystemParametersInfo (int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (scalar_t__*,...) ; 
 int /*<<< orphan*/  SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_GETDESKWALLPAPER ; 
 int /*<<< orphan*/  SPI_SETDESKWALLPAPER ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TEST (int) ; 
 scalar_t__ wcscmp (scalar_t__*,...) ; 

void
Test_SPI_SETDESKWALLPAPER(void)
{
    UNICODE_STRING ustrOld, ustrNew;
    WCHAR szOld[MAX_PATH];
    WCHAR szNew[MAX_PATH];

    /* Get old Wallpaper */
    TEST(NtUserSystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, szOld, 0) == 1);
    RtlInitUnicodeString(&ustrOld, szOld);

    /* Set no Wallpaper */
    TEST(NtUserSystemParametersInfo(SPI_SETDESKWALLPAPER, 0, L"", 0) == 1);
    TEST(NtUserSystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, szNew, 0) == 1);
    TEST(szNew[0] == 0);

    /* Set no Wallpaper 2 */
    RtlInitUnicodeString(&ustrNew, L"");
    TEST(NtUserSystemParametersInfo(SPI_SETDESKWALLPAPER, 0, &ustrNew, 0) == 1);
    TEST(NtUserSystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, szNew, 0) == 1);
    TEST(szNew[0] == 0);

    /* Reset Wallpaper */
    TEST(NtUserSystemParametersInfo(SPI_SETDESKWALLPAPER, 0, NULL, 0) == 1);
    TEST(NtUserSystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, szNew, 0) == 1);
    TEST(wcscmp(szNew, szOld) == 0);

    /* Set new Wallpaper */
    RtlInitUnicodeString(&ustrNew, L"test.bmp");
    TEST(NtUserSystemParametersInfo(SPI_SETDESKWALLPAPER, 0, &ustrNew, 0) == 1);
    TEST(NtUserSystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, szNew, 0) == 1);
    TEST(wcscmp(szNew, L"test.bmp") == 0);

    /* Get Wallpaper, too small buffer  */
    szNew[0] = 0; szNew[1] = 0; szNew[2] = 0;
    TEST(NtUserSystemParametersInfo(SPI_GETDESKWALLPAPER, 3, szNew, 0) == 1);
    TEST(szNew[0] != 0);
    TEST(szNew[1] != 0);
    TEST(szNew[2] != 0);

    /* Set invalid Wallpaper */
    SetLastError(0xdeadbeef);
    RtlInitUnicodeString(&ustrNew, L"*#!!-&");
    TEST(NtUserSystemParametersInfo(SPI_SETDESKWALLPAPER, 0, &ustrNew, 0) == 0);
    TEST(GetLastError() == ERROR_FILE_NOT_FOUND);
    TEST(NtUserSystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, szNew, 0) == 1);
    TEST(wcscmp(szNew, L"*#!!-&") == 0);

    /* Restore old Wallpaper */
    TEST(NtUserSystemParametersInfo(SPI_SETDESKWALLPAPER, MAX_PATH, &ustrOld, SPIF_UPDATEINIFILE) == 1);

}