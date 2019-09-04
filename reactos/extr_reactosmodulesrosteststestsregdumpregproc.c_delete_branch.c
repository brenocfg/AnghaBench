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
typedef  char TCHAR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  REGPROC_print_error () ; 
 int /*<<< orphan*/  REGPROC_resize_char_buffer (char**,size_t*,size_t) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegDeleteKey (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegEnumKeyEx (int /*<<< orphan*/ ,long,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKey (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 size_t _tcslen (char*) ; 

BOOL delete_branch(HKEY key, TCHAR** reg_key_name_buf, DWORD* reg_key_name_len)
{
    HKEY branch_key;
    DWORD max_sub_key_len;
    DWORD subkeys;
    DWORD curr_len;
    LONG ret;
    long int i;

    if (RegOpenKey(key, *reg_key_name_buf, &branch_key) != ERROR_SUCCESS) {
        REGPROC_print_error();
        return FALSE;
    }

    /* get size information and resize the buffers if necessary */
    if (RegQueryInfoKey(branch_key, NULL, NULL, NULL, &subkeys, &max_sub_key_len,
                        NULL, NULL, NULL, NULL, NULL, NULL) != ERROR_SUCCESS) {
        REGPROC_print_error();
        RegCloseKey(branch_key);
        return FALSE;
    }
    curr_len = _tcslen(*reg_key_name_buf);
    REGPROC_resize_char_buffer(reg_key_name_buf, reg_key_name_len, max_sub_key_len + curr_len + 1);

    (*reg_key_name_buf)[curr_len] = '\\';
    for (i = subkeys - 1; i >= 0; i--) {
        DWORD buf_len = *reg_key_name_len - curr_len;
        ret = RegEnumKeyEx(branch_key, i, *reg_key_name_buf + curr_len + 1, &buf_len, NULL, NULL, NULL, NULL);
        if (ret != ERROR_SUCCESS && ret != ERROR_MORE_DATA && ret != ERROR_NO_MORE_ITEMS) {
            REGPROC_print_error();
            RegCloseKey(branch_key);
            return FALSE;
        } else {
            delete_branch(key, reg_key_name_buf, reg_key_name_len);
        }
    }
    (*reg_key_name_buf)[curr_len] = '\0';
    RegCloseKey(branch_key);
    RegDeleteKey(key, *reg_key_name_buf);
    return TRUE;
}