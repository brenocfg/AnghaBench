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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 int /*<<< orphan*/  KEY_ENUMERATE_SUB_KEYS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegEnumKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD delete_key(HKEY hkey)
{
    char name[MAX_PATH];
    DWORD ret;

    while (!(ret = RegEnumKeyA(hkey, 0, name, sizeof(name)))) {
        HKEY tmp;
        if (!(ret = RegOpenKeyExA(hkey, name, 0, KEY_ENUMERATE_SUB_KEYS, &tmp))) {
            ret = delete_key(tmp);
            RegCloseKey(tmp);
        }
        if (ret) break;
    }
    if (ret != ERROR_NO_MORE_ITEMS) return ret;
    RegDeleteKeyA(hkey, "");
    return 0;
}