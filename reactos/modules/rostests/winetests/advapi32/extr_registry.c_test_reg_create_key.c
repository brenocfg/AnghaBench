#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* ptstrName; int /*<<< orphan*/  TrusteeType; int /*<<< orphan*/  TrusteeForm; int /*<<< orphan*/  MultipleTrusteeOperation; int /*<<< orphan*/ * pMultipleTrustee; } ;
struct TYPE_8__ {int grfAccessPermissions; TYPE_1__ Trustee; int /*<<< orphan*/  grfInheritance; int /*<<< orphan*/  grfAccessMode; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ SID_IDENTIFIER_AUTHORITY ;
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  scalar_t__ PSID ;
typedef  int /*<<< orphan*/  PACL ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  TYPE_3__ EXPLICIT_ACCESSA ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ AllocateAndInitializeSid (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  DACL_SECURITY_INFORMATION ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_BAD_PATHNAME ; 
 scalar_t__ ERROR_CHILD_MUST_BE_VOLATILE ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeSid (scalar_t__) ; 
 int GENERIC_ALL ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetVersion () ; 
 int /*<<< orphan*/ * HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ InitializeSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int KEY_ALL_ACCESS ; 
 int KEY_NOTIFY ; 
 int KEY_READ ; 
 int KEY_SET_VALUE ; 
 int KEY_WOW64_32KEY ; 
 int KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_MULTIPLE_TRUSTEE ; 
 int /*<<< orphan*/  REG_OPTION_VOLATILE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ RegSetKeySecurity (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_MIN_LENGTH ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_REVISION ; 
 int /*<<< orphan*/  SECURITY_WORLD_RID ; 
 int /*<<< orphan*/  SECURITY_WORLD_SID_AUTHORITY ; 
 int /*<<< orphan*/  SET_ACCESS ; 
 int STANDARD_RIGHTS_ALL ; 
 int /*<<< orphan*/  SUB_CONTAINERS_AND_OBJECTS_INHERIT ; 
 scalar_t__ SetEntriesInAclA (int,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetSecurityDescriptorDacl (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TRUSTEE_IS_SID ; 
 int /*<<< orphan*/  TRUSTEE_IS_WELL_KNOWN_GROUP ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/ * hkey_main ; 
 scalar_t__ limited_user ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  pIsWow64Process ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_reg_create_key(void)
{
    LONG ret;
    HKEY hkey1, hkey2;
    HKEY hkRoot64 = NULL;
    HKEY hkRoot32 = NULL;
    DWORD dwRet;
    BOOL bRet;
    SID_IDENTIFIER_AUTHORITY sid_authority = {SECURITY_WORLD_SID_AUTHORITY};
    PSID world_sid;
    EXPLICIT_ACCESSA access;
    PACL key_acl;
    SECURITY_DESCRIPTOR *sd;

    ret = RegCreateKeyExA(hkey_main, "Subkey1", 0, NULL, 0, KEY_NOTIFY, NULL, &hkey1, NULL);
    ok(!ret, "RegCreateKeyExA failed with error %d\n", ret);
    /* should succeed: all versions of Windows ignore the access rights
     * to the parent handle */
    ret = RegCreateKeyExA(hkey1, "Subkey2", 0, NULL, 0, KEY_SET_VALUE, NULL, &hkey2, NULL);
    ok(!ret, "RegCreateKeyExA failed with error %d\n", ret);

    /* clean up */
    RegDeleteKeyA(hkey2, "");
    RegDeleteKeyA(hkey1, "");
    RegCloseKey(hkey2);
    RegCloseKey(hkey1);

    /* test creation of volatile keys */
    ret = RegCreateKeyExA(hkey_main, "Volatile", 0, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey1, NULL);
    ok(!ret, "RegCreateKeyExA failed with error %d\n", ret);
    ret = RegCreateKeyExA(hkey1, "Subkey2", 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hkey2, NULL);
    ok(ret == ERROR_CHILD_MUST_BE_VOLATILE, "RegCreateKeyExA failed with error %d\n", ret);
    if (!ret) RegCloseKey( hkey2 );
    ret = RegCreateKeyExA(hkey1, "Subkey2", 0, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey2, NULL);
    ok(!ret, "RegCreateKeyExA failed with error %d\n", ret);
    RegCloseKey(hkey2);
    /* should succeed if the key already exists */
    ret = RegCreateKeyExA(hkey1, "Subkey2", 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hkey2, NULL);
    ok(!ret, "RegCreateKeyExA failed with error %d\n", ret);

    /* clean up */
    RegDeleteKeyA(hkey2, "");
    RegDeleteKeyA(hkey1, "");
    RegCloseKey(hkey2);
    RegCloseKey(hkey1);

    /*  beginning backslash character */
    ret = RegCreateKeyExA(hkey_main, "\\Subkey3", 0, NULL, 0, KEY_NOTIFY, NULL, &hkey1, NULL);
    if (!(GetVersion() & 0x80000000))
        ok(ret == ERROR_BAD_PATHNAME, "expected ERROR_BAD_PATHNAME, got %d\n", ret);
    else {
        ok(!ret, "RegCreateKeyExA failed with error %d\n", ret);
        RegDeleteKeyA(hkey1, "");
        RegCloseKey(hkey1);
    }

    /* trailing backslash characters */
    ret = RegCreateKeyExA(hkey_main, "Subkey4\\\\", 0, NULL, 0, KEY_NOTIFY, NULL, &hkey1, NULL);
    ok(ret == ERROR_SUCCESS, "RegCreateKeyExA failed with error %d\n", ret);
    RegDeleteKeyA(hkey1, "");
    RegCloseKey(hkey1);

    /* System\CurrentControlSet\Control\Video should be non-volatile */
    ret = RegCreateKeyExA(HKEY_LOCAL_MACHINE, "System\\CurrentControlSet\\Control\\Video\\Wine",
                          0, NULL, 0, KEY_NOTIFY, NULL, &hkey1, NULL);
    ok(ret == ERROR_SUCCESS, "RegCreateKeyExA failed with error %d\n", ret);
    RegDeleteKeyA(hkey1, "");
    RegCloseKey(hkey1);

    /* WOW64 flags - open an existing key */
    hkey1 = NULL;
    ret = RegCreateKeyExA(HKEY_LOCAL_MACHINE, "Software", 0, NULL, 0, KEY_READ|KEY_WOW64_32KEY, NULL, &hkey1, NULL);
    ok((ret == ERROR_SUCCESS && hkey1 != NULL) || broken(ret == ERROR_ACCESS_DENIED /* NT4, win2k */),
        "RegOpenKeyEx with KEY_WOW64_32KEY failed (err=%u)\n", ret);
    RegCloseKey(hkey1);

    hkey1 = NULL;
    ret = RegCreateKeyExA(HKEY_LOCAL_MACHINE, "Software", 0, NULL, 0, KEY_READ|KEY_WOW64_64KEY, NULL, &hkey1, NULL);
    ok((ret == ERROR_SUCCESS && hkey1 != NULL) || broken(ret == ERROR_ACCESS_DENIED /* NT4, win2k */),
        "RegOpenKeyEx with KEY_WOW64_64KEY failed (err=%u)\n", ret);
    RegCloseKey(hkey1);

    /* Try using WOW64 flags when opening a key with a DACL set to verify that
     * the registry access check is performed correctly. Redirection isn't
     * being tested, so the tests don't care about whether the process is
     * running under WOW64. */
    if (!pIsWow64Process)
    {
        win_skip("WOW64 flags are not recognized\n");
        return;
    }

    ret = RegCreateKeyExA(HKEY_LOCAL_MACHINE, "Software\\Wine", 0, NULL, 0,
                          KEY_WOW64_32KEY | KEY_ALL_ACCESS, NULL, &hkRoot32, NULL);
    if (limited_user)
        ok(ret == ERROR_ACCESS_DENIED && hkRoot32 == NULL,
           "RegCreateKeyEx with KEY_WOW64_32KEY failed (err=%d)\n", ret);
    else
        ok(ret == ERROR_SUCCESS && hkRoot32 != NULL,
           "RegCreateKeyEx with KEY_WOW64_32KEY failed (err=%d)\n", ret);

    ret = RegCreateKeyExA(HKEY_LOCAL_MACHINE, "Software\\Wine", 0, NULL, 0,
                          KEY_WOW64_64KEY | KEY_ALL_ACCESS, NULL, &hkRoot64, NULL);
    if (limited_user)
        ok(ret == ERROR_ACCESS_DENIED && hkRoot64 == NULL,
           "RegCreateKeyEx with KEY_WOW64_64KEY failed (err=%d)\n", ret);
    else
        ok(ret == ERROR_SUCCESS && hkRoot64 != NULL,
           "RegCreateKeyEx with KEY_WOW64_64KEY failed (err=%d)\n", ret);

    bRet = AllocateAndInitializeSid(&sid_authority, 1, SECURITY_WORLD_RID,
                                    0, 0, 0, 0, 0, 0, 0, &world_sid);
    ok(bRet == TRUE,
       "Expected AllocateAndInitializeSid to return TRUE, got %d, last error %u\n", bRet, GetLastError());

    access.grfAccessPermissions = GENERIC_ALL | STANDARD_RIGHTS_ALL;
    access.grfAccessMode = SET_ACCESS;
    access.grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
    access.Trustee.pMultipleTrustee = NULL;
    access.Trustee.MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE;
    access.Trustee.TrusteeForm = TRUSTEE_IS_SID;
    access.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
    access.Trustee.ptstrName = (char *)world_sid;

    dwRet = SetEntriesInAclA(1, &access, NULL, &key_acl);
    ok(dwRet == ERROR_SUCCESS,
       "Expected SetEntriesInAclA to return ERROR_SUCCESS, got %u, last error %u\n", dwRet, GetLastError());

    sd = HeapAlloc(GetProcessHeap(), 0, SECURITY_DESCRIPTOR_MIN_LENGTH);
    bRet = InitializeSecurityDescriptor(sd, SECURITY_DESCRIPTOR_REVISION);
    ok(bRet == TRUE,
       "Expected InitializeSecurityDescriptor to return TRUE, got %d, last error %u\n", bRet, GetLastError());

    bRet = SetSecurityDescriptorDacl(sd, TRUE, key_acl, FALSE);
    ok(bRet == TRUE,
       "Expected SetSecurityDescriptorDacl to return TRUE, got %d, last error %u\n", bRet, GetLastError());

    if (limited_user)
    {
        skip("not enough privileges to modify HKLM\n");
    }
    else
    {
        ret = RegSetKeySecurity(hkRoot64, DACL_SECURITY_INFORMATION, sd);
        ok(ret == ERROR_SUCCESS,
           "Expected RegSetKeySecurity to return success, got error %u\n", ret);

        ret = RegSetKeySecurity(hkRoot32, DACL_SECURITY_INFORMATION, sd);
        ok(ret == ERROR_SUCCESS,
           "Expected RegSetKeySecurity to return success, got error %u\n", ret);

        hkey1 = NULL;
        ret = RegCreateKeyExA(HKEY_LOCAL_MACHINE, "Software\\Wine", 0, NULL, 0,
                              KEY_WOW64_64KEY | KEY_READ, NULL, &hkey1, NULL);
        ok(ret == ERROR_SUCCESS && hkey1 != NULL,
           "RegOpenKeyEx with KEY_WOW64_64KEY failed (err=%u)\n", ret);
        RegCloseKey(hkey1);

        hkey1 = NULL;
        ret = RegCreateKeyExA(HKEY_LOCAL_MACHINE, "Software\\Wine", 0, NULL, 0,
                              KEY_WOW64_32KEY | KEY_READ, NULL, &hkey1, NULL);
        ok(ret == ERROR_SUCCESS && hkey1 != NULL,
           "RegOpenKeyEx with KEY_WOW64_32KEY failed (err=%u)\n", ret);
        RegCloseKey(hkey1);
    }

    HeapFree(GetProcessHeap(), 0, sd);
    LocalFree(key_acl);
    FreeSid(world_sid);
    RegDeleteKeyA(hkRoot64, "");
    RegCloseKey(hkRoot64);
    RegDeleteKeyA(hkRoot32, "");
    RegCloseKey(hkRoot32);
}