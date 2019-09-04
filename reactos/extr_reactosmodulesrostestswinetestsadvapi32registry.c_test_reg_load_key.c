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

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegLoadKeyA (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SE_BACKUP_NAME ; 
 int /*<<< orphan*/  SE_RESTORE_NAME ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  set_privileges (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_reg_load_key(void)
{
    DWORD ret;
    HKEY hkHandle;

    if (!set_privileges(SE_RESTORE_NAME, TRUE) ||
        !set_privileges(SE_BACKUP_NAME, FALSE))
    {
        win_skip("Failed to set SE_RESTORE_NAME privileges, skipping tests\n");
        return;
    }

    ret = RegLoadKeyA(HKEY_LOCAL_MACHINE, "Test", "saved_key");
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);

    set_privileges(SE_RESTORE_NAME, FALSE);

    ret = RegOpenKeyA(HKEY_LOCAL_MACHINE, "Test", &hkHandle);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);

    RegCloseKey(hkHandle);
}