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
typedef  int /*<<< orphan*/  dwUserPrefOrg ;
typedef  int /*<<< orphan*/  dwUserPref ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int* PVOID ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  KEY_DESKTOP ; 
 int /*<<< orphan*/  NtUserSystemParametersInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ QueryUserRegValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  TEST (int) ; 
 int /*<<< orphan*/  VAL_PREFMASK ; 

void
Test_UserPref(UINT uiGet, UINT uiSet, DWORD dwPrefMask)
{
    BOOL bOrig, bTemp = 0;
    DWORD dwUserPref, dwUserPrefOrg;
    DWORD cbSize;

    /* Get original values */
    NtUserSystemParametersInfo(uiGet, 0, &bOrig, 0);
    cbSize = sizeof(dwUserPrefOrg);
    QueryUserRegValueW(KEY_DESKTOP, VAL_PREFMASK, &dwUserPrefOrg, &cbSize, NULL);

    /* Value 0 */
    NtUserSystemParametersInfo(uiSet, 0, NULL, SPIF_UPDATEINIFILE);
    NtUserSystemParametersInfo(uiGet, 0, &bTemp, 0);
    TEST(bTemp == 0);
    cbSize = sizeof(dwUserPref);
    TEST(QueryUserRegValueW(KEY_DESKTOP, VAL_PREFMASK, &dwUserPref, &cbSize, NULL) == ERROR_SUCCESS);
    TEST((dwUserPref & dwPrefMask) == 0);
    TEST((dwUserPref & (~dwPrefMask)) == (dwUserPrefOrg & (~dwPrefMask)));

    /* Value 1 without Registry */
    NtUserSystemParametersInfo(uiSet, 0, (PVOID)1, 0);
    NtUserSystemParametersInfo(uiGet, 0, &bTemp, 0);
    TEST(bTemp == 1);
    cbSize = sizeof(dwUserPref);
    TEST(QueryUserRegValueW(KEY_DESKTOP, VAL_PREFMASK, &dwUserPref, &cbSize, NULL) == ERROR_SUCCESS);
    TEST((dwUserPref & dwPrefMask) == 0);
    TEST((dwUserPref & (~dwPrefMask)) == (dwUserPrefOrg & (~dwPrefMask)));

    /* Value 2 without Registry */
    NtUserSystemParametersInfo(uiSet, 0, (PVOID)2, 0);
    NtUserSystemParametersInfo(uiGet, 0, &bTemp, 0);
    TEST(bTemp == 1);
    cbSize = sizeof(dwUserPref);
    TEST(QueryUserRegValueW(KEY_DESKTOP, VAL_PREFMASK, &dwUserPref, &cbSize, NULL) == ERROR_SUCCESS);
    TEST((dwUserPref & dwPrefMask) == 0);
    TEST((dwUserPref & (~dwPrefMask)) == (dwUserPrefOrg & (~dwPrefMask)));

    /* Value 1 with Registry */
    NtUserSystemParametersInfo(uiSet, 0, (PVOID)1, SPIF_UPDATEINIFILE);
    NtUserSystemParametersInfo(uiGet, 0, &bTemp, 0);
    TEST(bTemp == 1);
    cbSize = sizeof(dwUserPref);
    TEST(QueryUserRegValueW(KEY_DESKTOP, VAL_PREFMASK, &dwUserPref, &cbSize, NULL) == ERROR_SUCCESS);
    TEST((dwUserPref & dwPrefMask) == dwPrefMask);
    TEST((dwUserPref & (~dwPrefMask)) == (dwUserPrefOrg & (~dwPrefMask)));

    /* Restore original value */
    NtUserSystemParametersInfo(uiSet, 0, (PVOID)bOrig, SPIF_UPDATEINIFILE);


}