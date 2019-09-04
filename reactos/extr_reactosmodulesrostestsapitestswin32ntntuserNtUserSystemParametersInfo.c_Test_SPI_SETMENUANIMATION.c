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
typedef  int /*<<< orphan*/  dwUserPrefMask ;
typedef  int* PVOID ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  KEY_DESKTOP ; 
 int /*<<< orphan*/  NtUserSystemParametersInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ QueryUserRegValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_GETMENUANIMATION ; 
 int /*<<< orphan*/  SPI_SETMENUANIMATION ; 
 int /*<<< orphan*/  TEST (int) ; 
 int UPM_MENUANIMATION ; 
 int /*<<< orphan*/  VAL_PREFMASK ; 

void
Test_SPI_SETMENUANIMATION(void)
{
    BOOL bOrig, bTemp = 0;
    DWORD dwUserPrefMask;
    DWORD cbSize;

    /* Get original values */
    NtUserSystemParametersInfo(SPI_GETMENUANIMATION, 0, &bOrig, 0);

    /* Value 0 */
    NtUserSystemParametersInfo(SPI_SETMENUANIMATION, 0, NULL, SPIF_UPDATEINIFILE);
    NtUserSystemParametersInfo(SPI_GETMENUANIMATION, 0, &bTemp, 0);
    TEST(bTemp == 0);
    cbSize = sizeof(dwUserPrefMask);
    TEST(QueryUserRegValueW(KEY_DESKTOP, VAL_PREFMASK, &dwUserPrefMask, &cbSize, NULL) == ERROR_SUCCESS);
    TEST((dwUserPrefMask & UPM_MENUANIMATION) == 0);

    /* Value 1 */
    NtUserSystemParametersInfo(SPI_SETMENUANIMATION, 0, (PVOID)1, SPIF_UPDATEINIFILE);
    NtUserSystemParametersInfo(SPI_GETMENUANIMATION, 0, &bTemp, 0);
    TEST(bTemp == 1);
    cbSize = sizeof(dwUserPrefMask);
    TEST(QueryUserRegValueW(KEY_DESKTOP, VAL_PREFMASK, &dwUserPrefMask, &cbSize, NULL) == ERROR_SUCCESS);
    TEST((dwUserPrefMask & UPM_MENUANIMATION) != 0);


    /* Restore original values */
    NtUserSystemParametersInfo(SPI_SETMENUANIMATION, 0, (PVOID)bOrig, SPIF_UPDATEINIFILE);
}