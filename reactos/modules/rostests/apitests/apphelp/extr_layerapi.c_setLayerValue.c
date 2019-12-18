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
typedef  scalar_t__ LSTATUS ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int KEY_SET_VALUE ; 
 int QueryFlag () ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ RegDeleteValueA (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ RegSetValueExA (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static BOOL setLayerValue(BOOL bMachine, const char* valueName, const char* value)
{
    HKEY key = NULL;
    LSTATUS lstatus = RegCreateKeyExA(bMachine ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER,
        "Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers", 0, NULL, 0, QueryFlag() | KEY_SET_VALUE, NULL, &key, NULL);
    if (lstatus == ERROR_SUCCESS)
    {
        if (value)
            lstatus = RegSetValueExA(key, valueName, 0, REG_SZ, (const BYTE*)value, (DWORD)strlen(value)+1);
        else
        {
            lstatus = RegDeleteValueA(key, valueName);
            lstatus = (lstatus == ERROR_FILE_NOT_FOUND ? ERROR_SUCCESS : lstatus);
        }
        RegCloseKey(key);
    }
    return lstatus == ERROR_SUCCESS;
}