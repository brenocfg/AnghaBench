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
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  LMEM_ZEROINIT ; 
 char* LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegEnumKeyExA (int /*<<< orphan*/ ,int,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryInfoKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL FindProvRegVals(DWORD dwIndex, DWORD *pdwProvType, LPSTR *pszProvName, 
			    DWORD *pcbProvName, DWORD *pdwProvCount)
{
	HKEY hKey;
	HKEY subkey;
	DWORD size = sizeof(DWORD);
	
	if (RegOpenKeyA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Cryptography\\Defaults\\Provider", &hKey))
		return FALSE;
	
	RegQueryInfoKeyA(hKey, NULL, NULL, NULL, pdwProvCount, pcbProvName,
				 NULL, NULL, NULL, NULL, NULL, NULL);
	(*pcbProvName)++;

	if (!(*pszProvName = LocalAlloc(LMEM_ZEROINIT, *pcbProvName)))
		return FALSE;
	
	RegEnumKeyExA(hKey, dwIndex, *pszProvName, pcbProvName, NULL, NULL, NULL, NULL);
	(*pcbProvName)++;

	RegOpenKeyA(hKey, *pszProvName, &subkey);
	RegQueryValueExA(subkey, "Type", NULL, NULL, (LPBYTE)pdwProvType, &size);
	
	RegCloseKey(subkey);
	RegCloseKey(hKey);
	
	return TRUE;
}