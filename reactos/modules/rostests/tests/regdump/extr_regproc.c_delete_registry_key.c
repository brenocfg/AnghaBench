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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ HKEY ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ENOUGH_MEMORY (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegOpenKey (scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcslen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_branch (scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ getRegClass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getRegKeyName (int /*<<< orphan*/ *) ; 

void delete_registry_key(TCHAR* reg_key_name)
{
    TCHAR* branch_name;
    DWORD branch_name_len;
    HKEY reg_key_class;
    HKEY branch_key;

    if (!reg_key_name || !reg_key_name[0]) {
        return;
    }
    /* open the specified key */
    reg_key_class = getRegClass(reg_key_name);
    if (reg_key_class == (HKEY)ERROR_INVALID_PARAMETER) {
        _tprintf(_T("Incorrect registry class specification in '%s'\n"), reg_key_name);
        //exit(1);
        return;
    }
    branch_name = getRegKeyName(reg_key_name);
    CHECK_ENOUGH_MEMORY(branch_name);
    branch_name_len = _tcslen(branch_name);
    if (!branch_name[0]) {
        _tprintf(_T("Can't delete registry class '%s'\n"), reg_key_name);
        //exit(1);
        return;
    }
    if (RegOpenKey(reg_key_class, branch_name, &branch_key) == ERROR_SUCCESS) {
        /* check whether the key exists */
        RegCloseKey(branch_key);
        delete_branch(reg_key_class, &branch_name, &branch_name_len);
    }
    HeapFree(GetProcessHeap(), 0, branch_name);
}