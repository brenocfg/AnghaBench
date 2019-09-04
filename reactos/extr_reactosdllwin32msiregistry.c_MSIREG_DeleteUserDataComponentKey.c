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
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int KEY_ALL_ACCESS ; 
 int KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegDeleteTreeW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int SQUASHED_GUID_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_user_sid () ; 
 int /*<<< orphan*/  sprintfW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  squash_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szUserDataComponents_fmt ; 

UINT MSIREG_DeleteUserDataComponentKey(LPCWSTR szComponent, LPCWSTR szUserSid)
{
    REGSAM access = KEY_WOW64_64KEY | KEY_ALL_ACCESS;
    WCHAR *usersid, squashed_comp[SQUASHED_GUID_SIZE], keypath[0x200];
    HKEY hkey;
    LONG r;

    if (!squash_guid( szComponent, squashed_comp )) return ERROR_FUNCTION_FAILED;
    TRACE("%s squashed %s\n", debugstr_w(szComponent), debugstr_w(squashed_comp));

    if (!szUserSid)
    {
        if (!(usersid = get_user_sid()))
        {
            ERR("Failed to retrieve user SID\n");
            return ERROR_FUNCTION_FAILED;
        }
        sprintfW(keypath, szUserDataComponents_fmt, usersid);
        LocalFree(usersid);
    }
    else
        sprintfW(keypath, szUserDataComponents_fmt, szUserSid);

    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, keypath, 0, access, &hkey)) return ERROR_SUCCESS;
    r = RegDeleteTreeW( hkey, squashed_comp );
    RegCloseKey(hkey);
    return r;
}