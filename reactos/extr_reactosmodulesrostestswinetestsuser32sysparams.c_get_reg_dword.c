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
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int REG_DWORD ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int*,void*,int*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL get_reg_dword(HKEY base, const char *key_name, const char *value_name, DWORD *value)
{
    HKEY key;
    DWORD type, data, size = sizeof(data);
    BOOL ret = FALSE;

    if (RegOpenKeyA(base, key_name, &key) == ERROR_SUCCESS)
    {
        if (RegQueryValueExA(key, value_name, NULL, &type, (void *)&data, &size) == ERROR_SUCCESS &&
            type == REG_DWORD)
        {
            *value = data;
            ret = TRUE;
        }
        RegCloseKey(key);
    }
    return ret;
}