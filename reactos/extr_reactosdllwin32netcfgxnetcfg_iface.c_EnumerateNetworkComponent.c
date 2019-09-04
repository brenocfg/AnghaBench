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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  NetCfgComponentItem ;
typedef  char* LPOLESTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (char*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  EnumClientServiceProtocol (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringFromCLSID (int /*<<< orphan*/  const*,char**) ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,char*,char*) ; 

HRESULT
EnumerateNetworkComponent(
    const GUID *pGuid, NetCfgComponentItem ** pHead)
{
    HKEY hKey;
    LPOLESTR pszGuid;
    HRESULT hr;
    WCHAR szName[150];

    hr = StringFromCLSID(pGuid, &pszGuid);
    if (SUCCEEDED(hr))
    {
        swprintf(szName, L"SYSTEM\\CurrentControlSet\\Control\\Network\\%s", pszGuid);
        if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, szName, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
        {
            hr = EnumClientServiceProtocol(hKey, pGuid, pHead);
            RegCloseKey(hKey);
        }
        CoTaskMemFree(pszGuid);
    }
    return hr;
}