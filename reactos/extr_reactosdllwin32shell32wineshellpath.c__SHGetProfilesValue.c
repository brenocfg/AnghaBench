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
typedef  char* LPWSTR ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (scalar_t__) ; 
 int MAX_PATH ; 
 scalar_t__ REG_EXPAND_SZ ; 
 scalar_t__ REG_SZ ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  lstrcpynW (char*,char*,int) ; 
 int strlenW (char*) ; 

__attribute__((used)) static HRESULT _SHGetProfilesValue(HKEY profilesKey, LPCWSTR szValueName,
 LPWSTR szValue, LPCWSTR szDefault)
{
    HRESULT hr;
    DWORD type, dwPathLen = MAX_PATH * sizeof(WCHAR);
    LONG lRet;

    TRACE("%p,%s,%p,%s\n", profilesKey, debugstr_w(szValueName), szValue,
     debugstr_w(szDefault));
    lRet = RegQueryValueExW(profilesKey, szValueName, NULL, &type,
     (LPBYTE)szValue, &dwPathLen);
    if (!lRet && (type == REG_SZ || type == REG_EXPAND_SZ) && dwPathLen
     && *szValue)
    {
        dwPathLen /= sizeof(WCHAR);
        szValue[dwPathLen] = '\0';
        hr = S_OK;
    }
    else
    {
        /* Missing or invalid value, set a default */
        lstrcpynW(szValue, szDefault, MAX_PATH);
        TRACE("Setting missing value %s to %s\n", debugstr_w(szValueName),
                                                  debugstr_w(szValue));
        lRet = RegSetValueExW(profilesKey, szValueName, 0, REG_EXPAND_SZ,
                              (LPBYTE)szValue,
                              (strlenW(szValue) + 1) * sizeof(WCHAR));
        if (lRet)
            hr = HRESULT_FROM_WIN32(lRet);
        else
            hr = S_OK;
    }
    TRACE("returning 0x%08x (output value is %s)\n", hr, debugstr_w(szValue));
    return hr;
}