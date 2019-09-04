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
typedef  int /*<<< orphan*/  szDosDeviceName ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int* PDWORD ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ARRAYSIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumValueW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ _wcsnicmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * wcschr (int /*<<< orphan*/ *,int) ; 
 int wcslen (char*) ; 
 scalar_t__ wcstoul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
VOID
GetUsedPorts(
    PDWORD pPortMap)
{
    WCHAR szDeviceName[64];
    WCHAR szDosDeviceName[64];
    DWORD dwIndex, dwType, dwPortNumber;
    DWORD dwDeviceNameSize, dwDosDeviceNameSize;
    PWSTR ptr;
    HKEY hKey;
    DWORD dwError;

    *pPortMap = 0;

    dwError = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                            L"Hardware\\DeviceMap\\PARALLEL PORTS",
                            0,
                            KEY_READ,
                            &hKey);
    if (dwError == ERROR_SUCCESS)
    {
        for (dwIndex = 0; ; dwIndex++)
        {
            dwDeviceNameSize = ARRAYSIZE(szDeviceName);
            dwDosDeviceNameSize = sizeof(szDosDeviceName);
            dwError = RegEnumValueW(hKey,
                                    dwIndex,
                                    szDeviceName,
                                    &dwDeviceNameSize,
                                    NULL,
                                    &dwType,
                                    (LPBYTE)szDosDeviceName,
                                    &dwDosDeviceNameSize);
            if (dwError != ERROR_SUCCESS)
                break;

            if (dwType == REG_SZ)
            {
                TRACE("%S --> %S\n", szDeviceName, szDosDeviceName);
                if (_wcsnicmp(szDosDeviceName, L"\\DosDevices\\LPT", wcslen(L"\\DosDevices\\LPT")) == 0)
                {
                     ptr = szDosDeviceName + wcslen(L"\\DosDevices\\LPT");
                     if (wcschr(ptr, L'.') == NULL)
                     {
                         TRACE("Device number %S\n", ptr);
                         dwPortNumber = wcstoul(ptr, NULL, 10);
                         if (dwPortNumber != 0)
                         {
                             *pPortMap |=(1 << dwPortNumber);
                         }
                     }
                }
            }
        }

        RegCloseKey(hKey);
    }

    TRACE("Done\n");
}