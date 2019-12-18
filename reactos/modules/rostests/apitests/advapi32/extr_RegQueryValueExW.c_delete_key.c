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
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 int /*<<< orphan*/  KEY_ENUMERATE_SUB_KEYS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegDeleteKeyW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegEnumKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _countof (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD delete_key(HKEY hkey)
{
    WCHAR name[MAX_PATH];
    DWORD ret;

    while (!(ret = RegEnumKeyW(hkey, 0, name, _countof(name))))
    {
        HKEY tmp;
        if (!(ret = RegOpenKeyExW(hkey, name, 0, KEY_ENUMERATE_SUB_KEYS, &tmp)))
        {
            ret = delete_key(tmp);
        }
        if (ret)
            break;
    }
    if (ret == ERROR_NO_MORE_ITEMS)
    {
        RegDeleteKeyW(hkey, L"");
        ret = 0;
    }
    RegCloseKey(hkey);
    return ret;
}