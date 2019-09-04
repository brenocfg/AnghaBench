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
typedef  int /*<<< orphan*/  UINT ;
typedef  int REGSAM ;
typedef  scalar_t__ MSIINSTALLCONTEXT ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int KEY_ALL_ACCESS ; 
 int KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 scalar_t__ MSIINSTALLCONTEXT_MACHINE ; 
 scalar_t__ MSIINSTALLCONTEXT_USERUNMANAGED ; 
 int /*<<< orphan*/  RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int SQUASHED_GUID_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_user_sid () ; 
 int /*<<< orphan*/  sprintfW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  squash_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcatW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szInstaller_LocalClassesProd ; 
 int /*<<< orphan*/  szInstaller_LocalManagedProd_fmt ; 
 int /*<<< orphan*/  szUserProducts ; 

UINT MSIREG_OpenProductKey(LPCWSTR szProduct, LPCWSTR szUserSid, MSIINSTALLCONTEXT context, HKEY *key, BOOL create)
{
    HKEY root = HKEY_LOCAL_MACHINE;
    REGSAM access = KEY_WOW64_64KEY | KEY_ALL_ACCESS;
    WCHAR *usersid = NULL, squashed_pc[SQUASHED_GUID_SIZE], keypath[MAX_PATH];

    if (!squash_guid( szProduct, squashed_pc )) return ERROR_FUNCTION_FAILED;
    TRACE("%s squashed %s\n", debugstr_w(szProduct), debugstr_w(squashed_pc));

    if (context == MSIINSTALLCONTEXT_MACHINE)
    {
        strcpyW(keypath, szInstaller_LocalClassesProd);
        strcatW( keypath, squashed_pc );
    }
    else if (context == MSIINSTALLCONTEXT_USERUNMANAGED)
    {
        root = HKEY_CURRENT_USER;
        strcpyW(keypath, szUserProducts);
        strcatW( keypath, squashed_pc );
    }
    else
    {
        if (!szUserSid)
        {
            if (!(usersid = get_user_sid()))
            {
                ERR("Failed to retrieve user SID\n");
                return ERROR_FUNCTION_FAILED;
            }
            szUserSid = usersid;
        }
        sprintfW( keypath, szInstaller_LocalManagedProd_fmt, szUserSid, squashed_pc );
        LocalFree(usersid);
    }
    if (create) return RegCreateKeyExW(root, keypath, 0, NULL, 0, access, NULL, key, NULL);
    return RegOpenKeyExW(root, keypath, 0, access, key);
}