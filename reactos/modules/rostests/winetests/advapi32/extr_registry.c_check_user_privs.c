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
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  limited_user ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void check_user_privs(void)
{
    DWORD ret;
    HKEY hkey = (HKEY)0xdeadbeef;

    ret = RegOpenKeyExA( HKEY_LOCAL_MACHINE, "Software", 0, KEY_READ|KEY_WRITE, &hkey);
    ok(ret == ERROR_SUCCESS || ret == ERROR_ACCESS_DENIED, "expected success or access denied, got %i\n", ret);
    if (ret == ERROR_SUCCESS)
    {
        ok(hkey != NULL, "RegOpenKeyExA succeeded but returned NULL hkey\n");
        RegCloseKey(hkey);
    }
    else
    {
        ok(hkey == NULL, "RegOpenKeyExA failed but returned hkey %p\n", hkey);
        limited_user = TRUE;
        trace("running as limited user\n");
    }
}