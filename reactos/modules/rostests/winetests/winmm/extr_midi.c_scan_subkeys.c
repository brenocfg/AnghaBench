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
typedef  int /*<<< orphan*/  name ;
typedef  char* LPCSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int KEY_ENUMERATE_SUB_KEYS ; 
 int KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExA (int /*<<< orphan*/ ,int,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ lstrcmpiA (char*,char* const) ; 
 size_t lstrlenA (char* const) ; 

__attribute__((used)) static BOOL scan_subkeys(HKEY parent, const LPCSTR *sub_keys)
{
    char name[64];
    DWORD index = 0;
    DWORD name_len = sizeof(name);
    BOOL found_vmware = FALSE;

    if (sub_keys[0] == NULL)
    {
       /* We're at the deepest level, check "Identifier" value now */
       char *test;
       if (RegQueryValueExA(parent, "Identifier", NULL, NULL, (LPBYTE) name, &name_len) != ERROR_SUCCESS)
           return FALSE;
       for (test = name; test < name + lstrlenA(name) - 6 && ! found_vmware; test++)
       {
           char c = test[6];
           test[6] = '\0';
           found_vmware = (lstrcmpiA(test, "VMware") == 0);
           test[6] = c;
       }
       return found_vmware;
    }

    while (RegEnumKeyExA(parent, index, name, &name_len, NULL, NULL, NULL, NULL) == ERROR_SUCCESS &&
           ! found_vmware) {
        char c = name[lstrlenA(sub_keys[0])];
        name[lstrlenA(sub_keys[0])] = '\0';
        if (lstrcmpiA(name, sub_keys[0]) == 0) {
            HKEY sub_key;
            name[lstrlenA(sub_keys[0])] = c;
            if (RegOpenKeyExA(parent, name, 0, KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE, &sub_key) == ERROR_SUCCESS) {
                found_vmware = scan_subkeys(sub_key, sub_keys + 1);
                RegCloseKey(sub_key);
            }
        }

        name_len = sizeof(name);
        index++;
    }

    return found_vmware;
}