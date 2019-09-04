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
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static BOOL register_testentry(void)
{
	HKEY hkey = 0, hkey2 = 0;
        DWORD ret;

        ret = RegCreateKeyA(HKEY_CLASSES_ROOT,"CLSID\\{deadcafe-beed-bead-dead-cafebeaddead}", &hkey);
        if (!ret) ret =	RegSetValueA(hkey,NULL,REG_SZ,"ComCat Test key",16);
	if (!ret) ret = RegCreateKeyA(hkey,
                                      "Implemented Categories\\{deadcafe-0000-0000-0000-000000000000}",
                                      &hkey2);
	RegCloseKey(hkey);
	RegCloseKey(hkey2);
        return !ret;
}