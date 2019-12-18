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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  REGSAM ;
typedef  int /*<<< orphan*/ * LPCSTR ;
typedef  scalar_t__ HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegEnumKeyA (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ RegQueryInfoKeyA (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT find_registry_key(HKEY hkeyParent, LPCSTR subkey, LPCSTR findkey, REGSAM access, HKEY *phkey)
{
    UINT ret;
    CHAR *string = NULL;
    int idx = 0;
    HKEY hkey;
    DWORD dwSize;
    BOOL found = FALSE;

    *phkey = 0;

    ret = RegOpenKeyExA(hkeyParent, subkey, 0, access, &hkey);
    if (ret != ERROR_SUCCESS) return ret;
    ret = RegQueryInfoKeyA(hkey, NULL, NULL, NULL, NULL, &dwSize, NULL, NULL, NULL, NULL, NULL, NULL);
    if (ret != ERROR_SUCCESS) return ret;
    if (!(string = HeapAlloc(GetProcessHeap(), 0, ++dwSize))) return ERROR_NOT_ENOUGH_MEMORY;

    while (!found &&
           RegEnumKeyA(hkey, idx++, string, dwSize) == ERROR_SUCCESS)
    {
        if (!strcmp(string, findkey))
        {
            *phkey = hkey;
            found = TRUE;
        }
        else if (find_registry_key(hkey, string, findkey, access, phkey) == ERROR_SUCCESS) found = TRUE;
    }

    if (*phkey != hkey) RegCloseKey(hkey);
    HeapFree(GetProcessHeap(), 0, string);
    return (found ? ERROR_SUCCESS : ERROR_FILE_NOT_FOUND);
}