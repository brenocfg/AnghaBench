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
typedef  scalar_t__ TCHAR ;
typedef  scalar_t__ HKEY ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int DWORD ;
typedef  scalar_t__ BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ENOUGH_MEMORY (scalar_t__*) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HKEY_CLASSES_ROOT ; 
 scalar_t__ HKEY_CURRENT_CONFIG ; 
 scalar_t__ HKEY_CURRENT_USER ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int KEY_MAX_LEN ; 
 int /*<<< orphan*/ * REGPROC_open_export_file (scalar_t__*) ; 
 int /*<<< orphan*/  REGPROC_print_error () ; 
 int /*<<< orphan*/  REGPROC_resize_char_buffer (scalar_t__**,int*,int /*<<< orphan*/ ) ; 
 int REG_CLASS_NUMBER ; 
 int REG_VAL_BUF_SIZE ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegOpenKey (scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcscpy (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  _tcslen (scalar_t__*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  export_hkey (int /*<<< orphan*/ *,scalar_t__,scalar_t__**,int*,scalar_t__**,int*,scalar_t__**,int*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ getRegClass (scalar_t__*) ; 
 scalar_t__* getRegKeyName (scalar_t__*) ; 
 scalar_t__* reg_class_keys ; 
 scalar_t__** reg_class_names ; 

BOOL export_registry_key(TCHAR* file_name, TCHAR* reg_key_name)
{
    HKEY reg_key_class;

    TCHAR *reg_key_name_buf;
    TCHAR *val_name_buf;
    BYTE *val_buf;
    DWORD reg_key_name_len = KEY_MAX_LEN;
    DWORD val_name_len = KEY_MAX_LEN;
    DWORD val_size = REG_VAL_BUF_SIZE;
    FILE *file = NULL;

    //_tprintf(_T("export_registry_key(%s, %s)\n"), reg_key_name, file_name);

    reg_key_name_buf = HeapAlloc(GetProcessHeap(), 0, reg_key_name_len * sizeof(*reg_key_name_buf));
    val_name_buf = HeapAlloc(GetProcessHeap(), 0, val_name_len * sizeof(*val_name_buf));
    val_buf = HeapAlloc(GetProcessHeap(), 0, val_size);
    CHECK_ENOUGH_MEMORY(reg_key_name_buf && val_name_buf && val_buf);

    if (reg_key_name && reg_key_name[0]) {
        TCHAR *branch_name;
        HKEY key;

        REGPROC_resize_char_buffer(&reg_key_name_buf, &reg_key_name_len,
                                   _tcslen(reg_key_name));
        _tcscpy(reg_key_name_buf, reg_key_name);

        /* open the specified key */
        reg_key_class = getRegClass(reg_key_name);
        if (reg_key_class == (HKEY)ERROR_INVALID_PARAMETER) {
            _tprintf(_T("Incorrect registry class specification in '%s\n"), reg_key_name);
            //exit(1);
            return FALSE;
        }
        branch_name = getRegKeyName(reg_key_name);
        CHECK_ENOUGH_MEMORY(branch_name);
        if (!branch_name[0]) {
            /* no branch - registry class is specified */
            file = REGPROC_open_export_file(file_name);
            export_hkey(file, reg_key_class,
                        &reg_key_name_buf, &reg_key_name_len,
                        &val_name_buf, &val_name_len,
                        &val_buf, &val_size);
        } else if (RegOpenKey(reg_key_class, branch_name, &key) == ERROR_SUCCESS) {
            file = REGPROC_open_export_file(file_name);
            export_hkey(file, key,
                        &reg_key_name_buf, &reg_key_name_len,
                        &val_name_buf, &val_name_len,
                        &val_buf, &val_size);
            RegCloseKey(key);
        } else {
            _tprintf(_T("Can't export. Registry key '%s does not exist!\n"), reg_key_name);
            REGPROC_print_error();
        }
        HeapFree(GetProcessHeap(), 0, branch_name);
    } else {
        int i;

        /* export all registry classes */
        file = REGPROC_open_export_file(file_name);
        for (i = 0; i < REG_CLASS_NUMBER; i++) {
            /* do not export HKEY_CLASSES_ROOT */
            if (reg_class_keys[i] != HKEY_CLASSES_ROOT &&
                reg_class_keys[i] != HKEY_CURRENT_USER &&
                reg_class_keys[i] != HKEY_CURRENT_CONFIG) {
                _tcscpy(reg_key_name_buf, reg_class_names[i]);
                export_hkey(file, reg_class_keys[i],
                            &reg_key_name_buf, &reg_key_name_len,
                            &val_name_buf, &val_name_len,
                            &val_buf, &val_size);
            }
        }
    }
    if (file) {
        fclose(file);
    }
//    HeapFree(GetProcessHeap(), 0, reg_key_name);
    HeapFree(GetProcessHeap(), 0, val_buf);
    HeapFree(GetProcessHeap(), 0, val_name_buf);
    HeapFree(GetProcessHeap(), 0, reg_key_name_buf);
    return TRUE;
}