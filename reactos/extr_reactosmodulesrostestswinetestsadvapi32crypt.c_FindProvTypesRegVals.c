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
typedef  int* PSTR ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  LMEM_ZEROINIT ; 
 char* LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegEnumKeyExA (int /*<<< orphan*/ ,int,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int strlen (char*) ; 

__attribute__((used)) static BOOL FindProvTypesRegVals(DWORD *pdwIndex, DWORD *pdwProvType, LPSTR *pszTypeName,
				 DWORD *pcbTypeName, DWORD *pdwTypeCount)
{
	HKEY hKey;
	HKEY hSubKey;
	PSTR ch;
	LPSTR szName;
	DWORD cbName;
	BOOL ret = FALSE;

	if (RegOpenKeyA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Cryptography\\Defaults\\Provider Types", &hKey))
		return FALSE;

	if (RegQueryInfoKeyA(hKey, NULL, NULL, NULL, pdwTypeCount, &cbName, NULL,
			NULL, NULL, NULL, NULL, NULL))
		goto cleanup;
	cbName++;

	if (!(szName = LocalAlloc(LMEM_ZEROINIT, cbName)))
		goto cleanup;

	while (!RegEnumKeyExA(hKey, *pdwIndex, szName, &cbName, NULL, NULL, NULL, NULL))
	{
		cbName++;
		ch = szName + strlen(szName);
		/* Convert "Type 000" to 0, etc/ */
		*pdwProvType = *(--ch) - '0';
		*pdwProvType += (*(--ch) - '0') * 10;
		*pdwProvType += (*(--ch) - '0') * 100;

		if (RegOpenKeyA(hKey, szName, &hSubKey))
			break;

		if (!RegQueryValueExA(hSubKey, "TypeName", NULL, NULL, NULL, pcbTypeName))
		{
			if (!(*pszTypeName = LocalAlloc(LMEM_ZEROINIT, *pcbTypeName)))
				break;

			if (!RegQueryValueExA(hSubKey, "TypeName", NULL, NULL, (LPBYTE)*pszTypeName, pcbTypeName))
			{
				ret = TRUE;
				break;
			}

			LocalFree(*pszTypeName);
		}

		RegCloseKey(hSubKey);

		(*pdwIndex)++;
	}
	RegCloseKey(hSubKey);
	LocalFree(szName);

cleanup:
	RegCloseKey(hKey);

	return ret;
}