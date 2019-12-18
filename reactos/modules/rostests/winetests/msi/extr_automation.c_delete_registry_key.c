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
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_key_portable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT delete_registry_key(HKEY hkeyParent, LPCSTR subkey, REGSAM access)
{
    UINT ret;
    CHAR *string = NULL;
    HKEY hkey;
    DWORD dwSize;

    ret = RegOpenKeyExA(hkeyParent, subkey, 0, access, &hkey);
    if (ret != ERROR_SUCCESS) return ret;
    ret = RegQueryInfoKeyA(hkey, NULL, NULL, NULL, NULL, &dwSize, NULL, NULL, NULL, NULL, NULL, NULL);
    if (ret != ERROR_SUCCESS) return ret;
    if (!(string = HeapAlloc(GetProcessHeap(), 0, ++dwSize))) return ERROR_NOT_ENOUGH_MEMORY;

    while (RegEnumKeyA(hkey, 0, string, dwSize) == ERROR_SUCCESS)
        delete_registry_key(hkey, string, access);

    RegCloseKey(hkey);
    HeapFree(GetProcessHeap(), 0, string);
    delete_key_portable(hkeyParent, subkey, access);
    return ERROR_SUCCESS;
}