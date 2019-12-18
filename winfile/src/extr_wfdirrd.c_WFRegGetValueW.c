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
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  LPDWORD ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

LONG WFRegGetValueW(HKEY hkey, LPCWSTR lpSubKey, LPCWSTR lpValue, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData)
{
	DWORD dwStatus;
	HKEY hkeySub;

	if ((dwStatus = RegOpenKey(hkey, lpSubKey, &hkeySub)) == ERROR_SUCCESS)
	{
			dwStatus = RegQueryValueEx(hkeySub, lpValue, NULL, pdwType, pvData, pcbData);

			RegCloseKey(hkeySub);
	}

	return dwStatus;
}