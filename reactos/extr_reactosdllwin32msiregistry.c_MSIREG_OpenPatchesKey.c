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
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int KEY_ALL_ACCESS ; 
 int KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int SQUASHED_GUID_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintfW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  squash_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szInstaller_Patches ; 

UINT MSIREG_OpenPatchesKey(LPCWSTR szPatch, HKEY *key, BOOL create)
{
    REGSAM access = KEY_WOW64_64KEY | KEY_ALL_ACCESS;
    WCHAR squashed_pc[SQUASHED_GUID_SIZE], keypath[0x200];

    if (!squash_guid( szPatch, squashed_pc )) return ERROR_FUNCTION_FAILED;
    TRACE("%s squashed %s\n", debugstr_w(szPatch), debugstr_w(squashed_pc));

    sprintfW( keypath, szInstaller_Patches, squashed_pc );

    if (create) return RegCreateKeyExW(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, key, NULL);
    return RegOpenKeyExW(HKEY_LOCAL_MACHINE, keypath, 0, access, key);
}