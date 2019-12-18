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
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ DeleteSubKey (scalar_t__,char*,char*) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKCU_ClassesPath ; 
 scalar_t__ HKEY_CLASSES_ROOT ; 
 scalar_t__ HKEY_CURRENT_USER ; 
 scalar_t__ HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  HKLM_ClassesPath ; 
 int IS_HKCR (scalar_t__) ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 int /*<<< orphan*/  REG_OPENED_EXISTING_KEY ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegCreateKeyExW (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ RegDeleteKeyW (scalar_t__,char*) ; 
 scalar_t__ RegOpenKeyExW (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_dec (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_hdl (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok_hex (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_key_deleted (scalar_t__) ; 
 int /*<<< orphan*/  ok_key_name (scalar_t__,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ok_key_not_deleted (scalar_t__) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static
void
Test_CreateOpenKey(void)
{
    HKEY MachineKey, MachineSubKey;
    HKEY UserKey, UserSubKey;
    HKEY ClassesRootKey, ClassesRootSubKey;
    DWORD ErrorCode;
    DWORD Disposition;

    /* First create a subkey in HKLM */
    ErrorCode = RegCreateKeyExW(
        HKEY_LOCAL_MACHINE,
        L"Software\\Classes\\Apitest_HKLM",
        0,
        NULL,
        0,
        MAXIMUM_ALLOWED,
        NULL,
        &MachineKey,
        NULL);

    if (ErrorCode == ERROR_ACCESS_DENIED)
    {
        win_skip("Please run those tests with Administrator rights\n");
        return;
    }

    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(!IS_HKCR(MachineKey), "\n");

    /* Open it in HKCR */
    ErrorCode = RegOpenKeyExW(
        HKEY_CLASSES_ROOT,
        L"Apitest_HKLM",
        0,
        MAXIMUM_ALLOWED,
        &ClassesRootKey);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(IS_HKCR(ClassesRootKey), "\n");
    ok_key_name(ClassesRootKey, &HKLM_ClassesPath, L"Apitest_HKLM");

    /* Try opening it in HKCU */
    UserKey = (HKEY)(ULONG_PTR)0xCAFEF00DCAFEF00DULL;
    ErrorCode = RegOpenKeyExW(
        HKEY_CURRENT_USER,
        L"Software\\Classes\\Apitest_HKLM",
        0,
        MAXIMUM_ALLOWED,
        &UserKey);
    ok_dec(ErrorCode, ERROR_FILE_NOT_FOUND);
    ok_hdl(UserKey, NULL);

    /* Cleanup */
    RegCloseKey(ClassesRootKey);
    RegCloseKey(MachineKey);
    ErrorCode = DeleteSubKey(HKEY_LOCAL_MACHINE, L"Software\\Classes", L"Apitest_HKLM");
    ok_dec(ErrorCode, ERROR_SUCCESS);

    /* Try creating in HKCR */
    ErrorCode = RegCreateKeyExW(
        HKEY_CLASSES_ROOT,
        L"Apitest_HKCR",
        0,
        NULL,
        0,
        MAXIMUM_ALLOWED,
        NULL,
        &ClassesRootKey,
        NULL);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(IS_HKCR(ClassesRootKey), "\n");
    ok_key_name(ClassesRootKey, &HKLM_ClassesPath, L"Apitest_HKCR");

    /* It should be present in HKLM */
    ErrorCode = RegOpenKeyExW(
        HKEY_LOCAL_MACHINE,
        L"Software\\Classes\\Apitest_HKCR",
        0,
        MAXIMUM_ALLOWED,
        &MachineKey);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(!IS_HKCR(MachineKey), "\n");

    /* But not in HKCU */
    UserKey = (HKEY)(ULONG_PTR)0xCAFEF00DCAFEF00DULL;
    ErrorCode = RegOpenKeyExW(
        HKEY_CURRENT_USER,
        L"Software\\Classes\\Apitest_HKCR",
        0,
        MAXIMUM_ALLOWED,
        &UserKey);
    ok_dec(ErrorCode, ERROR_FILE_NOT_FOUND);
    ok_hdl(UserKey, NULL);

    /* This must delete the one in HKLM */
    ErrorCode = RegDeleteKeyW(HKEY_CLASSES_ROOT, L"Apitest_HKCR");
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok_key_deleted(ClassesRootKey);
    ok_key_deleted(MachineKey);
    RegCloseKey(ClassesRootKey);
    RegCloseKey(MachineKey);

    /* Test that it is really not present anymore */
    MachineKey = (HKEY)(ULONG_PTR)0xCAFEF00DCAFEF00DULL;
    ErrorCode = RegOpenKeyExW(
        HKEY_LOCAL_MACHINE,
        L"Software\\Classes\\Apitest_HKCR",
        0,
        MAXIMUM_ALLOWED,
        &MachineKey);
    ok_dec(ErrorCode, ERROR_FILE_NOT_FOUND);
    ok_hdl(MachineKey, NULL);

    /* Try creating in HKCU */
    ErrorCode = RegCreateKeyExW(
        HKEY_CURRENT_USER,
        L"Software\\Classes\\Apitest_HKCU",
        0,
        NULL,
        0,
        MAXIMUM_ALLOWED,
        NULL,
        &UserKey,
        NULL);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(!IS_HKCR(UserKey), "\n");

    /* Try opening it in HKCR */
    ErrorCode = RegOpenKeyExW(
        HKEY_CLASSES_ROOT,
        L"Apitest_HKCU",
        0,
        MAXIMUM_ALLOWED,
        &ClassesRootKey);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(IS_HKCR(ClassesRootKey), "\n");
    ok_key_name(ClassesRootKey, &HKCU_ClassesPath, L"Apitest_HKCU");

    /* And in HKLM */
    ErrorCode = RegOpenKeyExW(
        HKEY_LOCAL_MACHINE,
        L"Software\\Classes\\Apitest_HKCU",
        0,
        MAXIMUM_ALLOWED,
        &MachineKey);
    ok_dec(ErrorCode, ERROR_FILE_NOT_FOUND);
    ok_hdl(MachineKey, NULL);

    ErrorCode = RegDeleteKeyW(HKEY_CLASSES_ROOT, L"Apitest_HKCU");
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok_key_deleted(ClassesRootKey);
    ok_key_deleted(UserKey);
    RegCloseKey(ClassesRootKey);
    RegCloseKey(UserKey);

    /* Test that it is really not present anymore */
    UserKey = (HKEY)(ULONG_PTR)0xCAFEF00DCAFEF00DULL;
    ErrorCode = RegOpenKeyExW(
        HKEY_CURRENT_USER,
        L"Software\\Classes\\Apitest_HKCU",
        0,
        MAXIMUM_ALLOWED,
        &UserKey);
    ok_dec(ErrorCode, ERROR_FILE_NOT_FOUND);
    ok_hdl(UserKey, NULL);

    /* Try creating in both HKLM and HKCU */
    ErrorCode = RegCreateKeyExW(
        HKEY_CURRENT_USER,
        L"Software\\Classes\\Apitest_HKLM_HKCU",
        0,
        NULL,
        0,
        MAXIMUM_ALLOWED,
        NULL,
        &UserKey,
        NULL);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(!IS_HKCR(UserKey), "\n");

    ErrorCode = RegCreateKeyExW(
        HKEY_LOCAL_MACHINE,
        L"Software\\Classes\\Apitest_HKLM_HKCU",
        0,
        NULL,
        0,
        MAXIMUM_ALLOWED,
        NULL,
        &MachineKey,
        NULL);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(!IS_HKCR(MachineKey), "\n");

    /* Open it in HKCR */
    ErrorCode = RegOpenKeyExW(
        HKEY_CLASSES_ROOT,
        L"Apitest_HKLM_HKCU",
        0,
        MAXIMUM_ALLOWED,
        &ClassesRootKey);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(IS_HKCR(ClassesRootKey), "\n");
    /* Verify it has opened the HKCU one */
    ok_key_name(ClassesRootKey, &HKCU_ClassesPath, L"Apitest_HKLM_HKCU");

    /* Try the same thing, but this time with RegCreateKeyEx API */
    RegCloseKey(ClassesRootKey);
    ErrorCode = RegCreateKeyExW(
        HKEY_CLASSES_ROOT,
        L"Apitest_HKLM_HKCU",
        0,
        NULL,
        0,
        MAXIMUM_ALLOWED,
        NULL,
        &ClassesRootKey,
        &Disposition);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(IS_HKCR(ClassesRootKey), "\n");
    /* Verify it has opened the HKCU one */
    ok_key_name(ClassesRootKey, &HKCU_ClassesPath, L"Apitest_HKLM_HKCU");
    ok_hex(Disposition, REG_OPENED_EXISTING_KEY);

    /* Deleting it from HKCR first deletes the one in HKCU */
    ErrorCode = RegDeleteKeyW(HKEY_CLASSES_ROOT, L"Apitest_HKLM_HKCU");
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok_key_deleted(UserKey);
    ok_key_deleted(ClassesRootKey);
    ok_key_not_deleted(MachineKey);

    RegCloseKey(UserKey);
    RegCloseKey(ClassesRootKey);

    /* This deletes it from HKLM this time */
    ErrorCode = RegDeleteKeyW(HKEY_CLASSES_ROOT, L"Apitest_HKLM_HKCU");
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok_key_deleted(MachineKey);
    RegCloseKey(MachineKey);

    /* See what happens with subkeys */
    ErrorCode = RegCreateKeyExW(
        HKEY_LOCAL_MACHINE,
        L"Software\\Classes\\Apitest_HKLM",
        0,
        NULL,
        0,
        MAXIMUM_ALLOWED,
        NULL,
        &MachineKey,
        NULL);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(!IS_HKCR(MachineKey), "\n");

    /* Open it in HKCR */
    ErrorCode = RegOpenKeyExW(
        HKEY_CLASSES_ROOT,
        L"Apitest_HKLM",
        0,
        MAXIMUM_ALLOWED,
        &ClassesRootKey);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(IS_HKCR(ClassesRootKey), "\n");
    ok_key_name(ClassesRootKey, &HKLM_ClassesPath, L"Apitest_HKLM");

    /* Create a corresponding subkey in HKCU */
    ErrorCode = RegCreateKeyExW(
        HKEY_CURRENT_USER,
        L"Software\\Classes\\Apitest_HKLM\\HKCU_Subkey",
        0,
        NULL,
        0,
        MAXIMUM_ALLOWED,
        NULL,
        &UserSubKey,
        NULL);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(!IS_HKCR(UserSubKey), "\n");

    /* Open it as an HKCR subkey */
    ErrorCode = RegOpenKeyExW(
        ClassesRootKey,
        L"HKCU_Subkey",
        0,
        MAXIMUM_ALLOWED,
        &ClassesRootSubKey);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(IS_HKCR(ClassesRootSubKey), "\n");
    ok_key_name(ClassesRootSubKey, &HKCU_ClassesPath, L"Apitest_HKLM\\HKCU_Subkey");

    /* Try the same thing, but this time with RegCreateKeyEx API */
    RegCloseKey(ClassesRootSubKey);
    ErrorCode = RegCreateKeyExW(
        ClassesRootKey,
        L"HKCU_Subkey",
        0,
        NULL,
        0,
        MAXIMUM_ALLOWED,
        NULL,
        &ClassesRootSubKey,
        &Disposition);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(IS_HKCR(ClassesRootSubKey), "\n");
    /* Verify it has opened the HKCU one */
    ok_key_name(ClassesRootSubKey, &HKCU_ClassesPath, L"Apitest_HKLM\\HKCU_Subkey");
    ok_hex(Disposition, REG_OPENED_EXISTING_KEY);

    /* This one now exists */
    ErrorCode = RegOpenKeyExW(
        HKEY_CURRENT_USER,
        L"Software\\Classes\\Apitest_HKLM",
        0,
        MAXIMUM_ALLOWED,
        &UserKey);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(!IS_HKCR(UserKey), "\n");

    /* Delete */
    ErrorCode = RegDeleteKeyW(UserKey, L"HKCU_Subkey");
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok_key_deleted(UserSubKey);
    ok_key_deleted(ClassesRootSubKey);
    RegCloseKey(UserSubKey);
    RegCloseKey(ClassesRootSubKey);

    /* See what this deletes */
    RegDeleteKeyW(HKEY_CLASSES_ROOT, L"Apitest_HKLM");
    ok_key_deleted(UserKey);
    RegCloseKey(UserKey);
    ok_key_not_deleted(ClassesRootKey);
    ok_key_not_deleted(MachineKey);

    /* Once again */
    RegDeleteKeyW(HKEY_CLASSES_ROOT, L"Apitest_HKLM");
    ok_key_deleted(ClassesRootKey);
    ok_key_deleted(MachineKey);
    RegCloseKey(ClassesRootKey);
    RegCloseKey(MachineKey);

    /* Same, but with HKCU first */
    ErrorCode = RegCreateKeyExW(
        HKEY_CURRENT_USER,
        L"Software\\Classes\\Apitest_HKCU",
        0,
        NULL,
        0,
        MAXIMUM_ALLOWED,
        NULL,
        &UserKey,
        NULL);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(!IS_HKCR(UserKey), "\n");

    /* Open it in HKCR */
    ErrorCode = RegOpenKeyExW(
        HKEY_CLASSES_ROOT,
        L"Apitest_HKCU",
        0,
        MAXIMUM_ALLOWED,
        &ClassesRootKey);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(IS_HKCR(ClassesRootKey), "\n");
    ok_key_name(ClassesRootKey, &HKCU_ClassesPath, L"Apitest_HKCU");

    /* Try creating a subkey with this HKCR handle, which points to a subkey in HKCU. */
    ErrorCode = RegCreateKeyExW(
        ClassesRootKey,
        L"HKCR_Subkey",
        0,
        NULL,
        0,
        MAXIMUM_ALLOWED,
        NULL,
        &ClassesRootSubKey,
        NULL);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(IS_HKCR(ClassesRootSubKey), "\n");
    /* It is in fact created in HKLM */
    ok_key_name(ClassesRootSubKey, &HKLM_ClassesPath, L"Apitest_HKCU\\HKCR_Subkey");
    /* Let's see if we can delete it */
    RegDeleteKeyW(ClassesRootKey, L"HKCR_Subkey");
    ok_key_deleted(ClassesRootSubKey);
    RegCloseKey(ClassesRootSubKey);

    /* Create a corresponding subkey in HKLM */
    ErrorCode = RegCreateKeyExW(
        HKEY_LOCAL_MACHINE,
        L"Software\\Classes\\Apitest_HKCU\\HKLM_Subkey",
        0,
        NULL,
        0,
        MAXIMUM_ALLOWED,
        NULL,
        &MachineSubKey,
        NULL);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(!IS_HKCR(MachineSubKey), "\n");

    /* Open it from the HKCR handle (which is still pointing to HKCU) */
    ok_key_name(ClassesRootKey, &HKCU_ClassesPath, L"Apitest_HKCU");
    ErrorCode = RegOpenKeyExW(
        ClassesRootKey,
        L"HKLM_Subkey",
        0,
        MAXIMUM_ALLOWED,
        &ClassesRootSubKey);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(IS_HKCR(ClassesRootSubKey), "\n");
    ok_key_name(ClassesRootSubKey, &HKLM_ClassesPath, L"Apitest_HKCU\\HKLM_Subkey");

    /* This one now exists */
    ErrorCode = RegOpenKeyExW(
        HKEY_LOCAL_MACHINE,
        L"Software\\Classes\\Apitest_HKCU",
        0,
        MAXIMUM_ALLOWED,
        &MachineKey);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(!IS_HKCR(MachineKey), "\n");

    /* Delete this subkey */
    ErrorCode = RegDeleteKeyW(MachineKey, L"HKLM_Subkey");
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok_key_deleted(MachineSubKey);
    ok_key_deleted(ClassesRootSubKey);

    /* Create another subkey, this time from HKCU */
    ErrorCode = RegCreateKeyExW(
        HKEY_CURRENT_USER,
        L"Software\\Classes\\Apitest_HKCU\\HKCU_Subkey",
        0,
        NULL,
        0,
        MAXIMUM_ALLOWED,
        NULL,
        &UserSubKey,
        NULL);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(!IS_HKCR(UserSubKey), "\n");

    /* And try creating it again as a subkey of this HKCR handle (which points to HKCU). */
    ok_key_name(ClassesRootKey, &HKCU_ClassesPath, L"Apitest_HKCU");
    ErrorCode = RegCreateKeyExW(
        ClassesRootKey,
        L"HKCU_Subkey",
        0,
        NULL,
        0,
        MAXIMUM_ALLOWED,
        NULL,
        &ClassesRootSubKey,
        &Disposition);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(IS_HKCR(ClassesRootSubKey), "\n");
    /* This time the one in HKCU is opened */
    ok_key_name(ClassesRootSubKey, &HKCU_ClassesPath, L"Apitest_HKCU\\HKCU_Subkey");
    ok_hex(Disposition, REG_OPENED_EXISTING_KEY);
    /* Let's see if we can delete it */
    RegDeleteKeyW(ClassesRootKey, L"HKCU_Subkey");
    ok_key_deleted(ClassesRootSubKey);
    RegCloseKey(ClassesRootSubKey);
    ok_key_deleted(UserSubKey);
    RegCloseKey(UserSubKey);

    RegCloseKey(MachineSubKey);
    RegCloseKey(ClassesRootSubKey);

    /* See what this deletes */
    RegDeleteKeyW(HKEY_CLASSES_ROOT, L"Apitest_HKCU");
    ok_key_deleted(UserKey);
    RegCloseKey(UserKey);
    ok_key_deleted(ClassesRootKey);
    RegCloseKey(UserKey);
    ok_key_not_deleted(MachineKey);

    /* Once again */
    RegDeleteKeyW(HKEY_CLASSES_ROOT, L"Apitest_HKCU");
    ok_key_deleted(MachineKey);
    RegCloseKey(MachineKey);
}