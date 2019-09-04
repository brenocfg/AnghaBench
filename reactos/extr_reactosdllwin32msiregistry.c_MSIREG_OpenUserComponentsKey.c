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
typedef  scalar_t__ UINT ;
typedef  int REGSAM ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int KEY_ALL_ACCESS ; 
 int KEY_WOW64_64KEY ; 
 scalar_t__ RegCreateKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SQUASHED_GUID_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  squash_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcatW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szInstaller_Components ; 
 int /*<<< orphan*/  szUserComponents ; 

UINT MSIREG_OpenUserComponentsKey(LPCWSTR szComponent, HKEY *key, BOOL create)
{
    WCHAR squashed_cc[SQUASHED_GUID_SIZE], keypath[0x200];
    REGSAM access = KEY_WOW64_64KEY | KEY_ALL_ACCESS;
    UINT ret;

    if (!squash_guid( szComponent, squashed_cc)) return ERROR_FUNCTION_FAILED;
    TRACE("%s squashed %s\n", debugstr_w(szComponent), debugstr_w(squashed_cc));

    strcpyW(keypath, szUserComponents);
    strcatW( keypath, squashed_cc );

    if (create) return RegCreateKeyW(HKEY_CURRENT_USER, keypath, key);
    ret = RegOpenKeyW(HKEY_CURRENT_USER, keypath, key);
    if (ret != ERROR_FILE_NOT_FOUND) return ret;

    strcpyW(keypath, szInstaller_Components);
    strcatW( keypath, squashed_cc );
    return RegOpenKeyExW( HKEY_LOCAL_MACHINE, keypath, 0, access, key );
}