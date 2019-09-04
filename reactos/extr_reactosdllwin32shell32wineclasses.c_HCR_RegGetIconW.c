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
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ExpandEnvironmentStringsW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ParseFieldW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  PathUnquoteSpacesW (int /*<<< orphan*/ *) ; 
 scalar_t__ REG_EXPAND_SZ ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _countof (int /*<<< orphan*/ *) ; 
 int atoiW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static BOOL HCR_RegGetIconW(HKEY hkey, LPWSTR szDest, LPCWSTR szName, DWORD len, int* picon_idx)
{
    DWORD dwType;
    WCHAR sTemp[MAX_PATH];
    WCHAR sNum[7];

    if (!RegQueryValueExW(hkey, szName, 0, &dwType, (LPBYTE)szDest, &len))
    {
      if (dwType == REG_EXPAND_SZ)
      {
        ExpandEnvironmentStringsW(szDest, sTemp, MAX_PATH);
        lstrcpynW(szDest, sTemp, len);
      }
        if (ParseFieldW (szDest, 2, sNum, _countof(sNum)))
             *picon_idx = atoiW(sNum);
          else
             *picon_idx=0; /* sometimes the icon number is missing */
      ParseFieldW (szDest, 1, szDest, len);
          PathUnquoteSpacesW(szDest);
      return TRUE;
    }
    return FALSE;
}