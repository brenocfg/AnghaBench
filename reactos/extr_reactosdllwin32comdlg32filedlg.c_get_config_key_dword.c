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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ REG_DWORD ; 
 int /*<<< orphan*/  RegQueryValueExW (scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL get_config_key_dword(HKEY hkey, const WCHAR *name, DWORD *value)
{
    DWORD type, data, size;

    size = sizeof(data);
    if (hkey && !RegQueryValueExW(hkey, name, 0, &type, (BYTE *)&data, &size) && type == REG_DWORD)
    {
        *value = data;
        return TRUE;
    }

    return FALSE;
}