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
typedef  int ULONG64 ;
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
 scalar_t__ ERROR_BADKEY ; 
 scalar_t__ ERROR_BAD_PATHNAME ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeSid (scalar_t__) ; 
 int GENERIC_ALL ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/ * HKEY_CURRENT_USER ; 
 int /*<<< orphan*/ * HKEY_LOCAL_MACHINE ; 
 int HandleToUlong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ InitializeSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int KEY_ALL_ACCESS ; 
 int KEY_QUERY_VALUE ; 
 int KEY_READ ; 
 int KEY_WOW64_32KEY ; 
 int KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_MULTIPLE_TRUSTEE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
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
 int /*<<< orphan*/ * UlongToHandle (int) ; 
 scalar_t__ broken (int) ; 
 scalar_t__ limited_user ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pIsWow64Process ; 
 int ptr_size ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_reg_open_key(void)
{
    DWORD ret = 0;
    HKEY hkResult = NULL;
    HKEY hkPreserve = NULL;
    HKEY hkRoot64 = NULL;
    HKEY hkRoot32 = NULL;
    BOOL bRet;
    SID_IDENTIFIER_AUTHORITY sid_authority = {SECURITY_WORLD_SID_AUTHORITY};
    PSID world_sid;
    EXPLICIT_ACCESSA access;
    PACL key_acl;
    SECURITY_DESCRIPTOR *sd;

    /* successful open */
    ret = RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Wine\\Test", &hkResult);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
    ok(hkResult != NULL, "expected hkResult != NULL\n");
    hkPreserve = hkResult;

    /* open same key twice */
    ret = RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Wine\\Test", &hkResult);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
    ok(hkResult != hkPreserve, "expected hkResult != hkPreserve\n");
    ok(hkResult != NULL, "hkResult != NULL\n");
    RegCloseKey(hkResult);

    /* trailing slashes */
    ret = RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Wine\\Test\\\\", &hkResult);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
    RegCloseKey(hkResult);

    /* open nonexistent key
    * check that hkResult is set to NULL
    */
    hkResult = hkPreserve;
    ret = RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Wine\\Nonexistent", &hkResult);
    ok(ret == ERROR_FILE_NOT_FOUND, "expected ERROR_FILE_NOT_FOUND, got %d\n", ret);
    ok(hkResult == NULL, "expected hkResult == NULL\n");

    /* open the same nonexistent key again to make sure the key wasn't created */
    hkResult = hkPreserve;
    ret = RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Wine\\Nonexistent", &hkResult);
    ok(ret == ERROR_FILE_NOT_FOUND, "expected ERROR_FILE_NOT_FOUND, got %d\n", ret);
    ok(hkResult == NULL, "expected hkResult == NULL\n");

    /* send in NULL lpSubKey
    * check that hkResult receives the value of hKey
    */
    hkResult = hkPreserve;
    ret = RegOpenKeyA(HKEY_CURRENT_USER, NULL, &hkResult);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
    ok(hkResult == HKEY_CURRENT_USER, "expected hkResult == HKEY_CURRENT_USER\n");

    /* send empty-string in lpSubKey */
    hkResult = hkPreserve;
    ret = RegOpenKeyA(HKEY_CURRENT_USER, "", &hkResult);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
    ok(hkResult == HKEY_CURRENT_USER, "expected hkResult == HKEY_CURRENT_USER\n");

    /* send in NULL lpSubKey and NULL hKey
    * hkResult is set to NULL
    */
    hkResult = hkPreserve;
    ret = RegOpenKeyA(NULL, NULL, &hkResult);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
    ok(hkResult == NULL, "expected hkResult == NULL\n");

    /* only send NULL hKey
     * the value of hkResult remains unchanged
     */
    hkResult = hkPreserve;
    ret = RegOpenKeyA(NULL, "Software\\Wine\\Test", &hkResult);
    ok(ret == ERROR_INVALID_HANDLE || ret == ERROR_BADKEY, /* Windows 95 returns BADKEY */
       "expected ERROR_INVALID_HANDLE or ERROR_BADKEY, got %d\n", ret);
    ok(hkResult == hkPreserve, "expected hkResult == hkPreserve\n");

    /* send in NULL hkResult */
    ret = RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Wine\\Test", NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", ret);

    ret = RegOpenKeyA(HKEY_CURRENT_USER, NULL, NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", ret);

    ret = RegOpenKeyA(NULL, NULL, NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", ret);

    /*  beginning backslash character */
    ret = RegOpenKeyA(HKEY_CURRENT_USER, "\\Software\\Wine\\Test", &hkResult);
    ok(ret == ERROR_BAD_PATHNAME || /* NT/2k/XP */
       broken(ret == ERROR_SUCCESS),  /* wow64 */
       "expected ERROR_BAD_PATHNAME or ERROR_FILE_NOT_FOUND, got %d\n", ret);
    if (!ret) RegCloseKey(hkResult);

    hkResult = NULL;
    ret = RegOpenKeyExA(HKEY_CLASSES_ROOT, "\\clsid", 0, KEY_QUERY_VALUE, &hkResult);
    ok(ret == ERROR_SUCCESS || /* 2k/XP */
       ret == ERROR_BAD_PATHNAME, /* NT */
       "expected ERROR_SUCCESS, ERROR_BAD_PATHNAME or ERROR_FILE_NOT_FOUND, got %d\n", ret);
    RegCloseKey(hkResult);

    /* NULL or empty subkey of special root */
    hkResult = NULL;
    ret = RegOpenKeyExA(HKEY_CLASSES_ROOT, NULL, 0, KEY_QUERY_VALUE, &hkResult);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
    ok(hkResult == HKEY_CLASSES_ROOT, "expected hkResult == HKEY_CLASSES_ROOT\n");

    hkResult = NULL;
    ret = RegOpenKeyExA(HKEY_CLASSES_ROOT, "", 0, KEY_QUERY_VALUE, &hkResult);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
    ok(hkResult == HKEY_CLASSES_ROOT, "expected hkResult == HKEY_CLASSES_ROOT\n");

    hkResult = NULL;
    ret = RegOpenKeyExA(HKEY_CLASSES_ROOT, "\\", 0, KEY_QUERY_VALUE, &hkResult);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
    ok(hkResult != HKEY_CLASSES_ROOT, "expected hkResult to be a new key\n");
    ok(!RegCloseKey(hkResult), "got invalid hkey\n");

    /* empty subkey of existing handle */
    hkResult = hkPreserve;
    ret = RegOpenKeyExA(hkPreserve, "", 0, KEY_QUERY_VALUE, &hkResult);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
    ok(hkResult != hkPreserve, "expected hkResult != hkPreserve\n");
    ok(!RegCloseKey(hkResult), "got invalid hkey\n");

    /* NULL subkey of existing handle */
    hkResult = hkPreserve;
    ret = RegOpenKeyExA(hkPreserve, NULL, 0, KEY_QUERY_VALUE, &hkResult);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
    ok(hkResult != hkPreserve, "expected hkResult != hkPreserve\n");
    ok(!RegCloseKey(hkResult), "got invalid hkey\n");

    /* empty subkey of NULL */
    hkResult = hkPreserve;
    ret = RegOpenKeyExA(NULL, "", 0, KEY_QUERY_VALUE, &hkResult);
    ok(ret == ERROR_INVALID_HANDLE, "expected ERROR_INVALID_HANDLE, got %d\n", ret);
    ok(hkResult == hkPreserve, "expected hkResult == hkPreserve\n");

    RegCloseKey(hkPreserve);

    /* WOW64 flags */
    hkResult = NULL;
    ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software", 0, KEY_READ|KEY_WOW64_32KEY, &hkResult);
    ok((ret == ERROR_SUCCESS && hkResult != NULL) || broken(ret == ERROR_ACCESS_DENIED /* NT4, win2k */),
        "RegOpenKeyEx with KEY_WOW64_32KEY failed (err=%u)\n", ret);
    RegCloseKey(hkResult);

    hkResult = NULL;
    ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software", 0, KEY_READ|KEY_WOW64_64KEY, &hkResult);
    ok((ret == ERROR_SUCCESS && hkResult != NULL) || broken(ret == ERROR_ACCESS_DENIED /* NT4, win2k */),
        "RegOpenKeyEx with KEY_WOW64_64KEY failed (err=%u)\n", ret);
    RegCloseKey(hkResult);

    /* check special HKEYs on 64bit
     * only the lower 4 bytes of the supplied key are used
     */
    if (ptr_size == 64)
    {
        /* HKEY_CURRENT_USER */
        ret = RegOpenKeyA(UlongToHandle(HandleToUlong(HKEY_CURRENT_USER)), "Software", &hkResult);
        ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
        ok(hkResult != NULL, "expected hkResult != NULL\n");
        RegCloseKey(hkResult);

        ret = RegOpenKeyA((HKEY)(HandleToUlong(HKEY_CURRENT_USER) | (ULONG64)1 << 32), "Software", &hkResult);
        ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
        ok(hkResult != NULL, "expected hkResult != NULL\n");
        RegCloseKey(hkResult);

        ret = RegOpenKeyA((HKEY)(HandleToUlong(HKEY_CURRENT_USER) | (ULONG64)0xdeadbeef << 32), "Software", &hkResult);
        ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
        ok(hkResult != NULL, "expected hkResult != NULL\n");
        RegCloseKey(hkResult);

        ret = RegOpenKeyA((HKEY)(HandleToUlong(HKEY_CURRENT_USER) | (ULONG64)0xffffffff << 32), "Software", &hkResult);
        ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
        ok(hkResult != NULL, "expected hkResult != NULL\n");
        RegCloseKey(hkResult);

        /* HKEY_LOCAL_MACHINE */
        ret = RegOpenKeyA((HKEY)(HandleToUlong(HKEY_LOCAL_MACHINE) | (ULONG64)0xdeadbeef << 32), "Software", &hkResult);
        ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
        ok(hkResult != NULL, "expected hkResult != NULL\n");
        RegCloseKey(hkResult);
    }

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
           "RegCreateKeyEx with KEY_WOW64_32KEY failed (err=%u)\n", ret);
    else
        ok(ret == ERROR_SUCCESS && hkRoot32 != NULL,
           "RegCreateKeyEx with KEY_WOW64_32KEY failed (err=%u)\n", ret);

    ret = RegCreateKeyExA(HKEY_LOCAL_MACHINE, "Software\\Wine", 0, NULL, 0,
                          KEY_WOW64_64KEY | KEY_ALL_ACCESS, NULL, &hkRoot64, NULL);
    if (limited_user)
        ok(ret == ERROR_ACCESS_DENIED && hkRoot64 == NULL,
           "RegCreateKeyEx with KEY_WOW64_64KEY failed (err=%u)\n", ret);
    else
        ok(ret == ERROR_SUCCESS && hkRoot64 != NULL,
           "RegCreateKeyEx with KEY_WOW64_64KEY failed (err=%u)\n", ret);

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

    ret = SetEntriesInAclA(1, &access, NULL, &key_acl);
    ok(ret == ERROR_SUCCESS,
       "Expected SetEntriesInAclA to return ERROR_SUCCESS, got %u, last error %u\n", ret, GetLastError());

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
        LONG error;

        error = RegSetKeySecurity(hkRoot64, DACL_SECURITY_INFORMATION, sd);
        ok(error == ERROR_SUCCESS,
           "Expected RegSetKeySecurity to return success, got error %u\n", error);

        error = RegSetKeySecurity(hkRoot32, DACL_SECURITY_INFORMATION, sd);
        ok(error == ERROR_SUCCESS,
           "Expected RegSetKeySecurity to return success, got error %u\n", error);

        hkResult = NULL;
        ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\Wine", 0, KEY_WOW64_64KEY | KEY_READ, &hkResult);
        ok(ret == ERROR_SUCCESS && hkResult != NULL,
           "RegOpenKeyEx with KEY_WOW64_64KEY failed (err=%u)\n", ret);
        RegCloseKey(hkResult);

        hkResult = NULL;
        ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\Wine", 0, KEY_WOW64_32KEY | KEY_READ, &hkResult);
        ok(ret == ERROR_SUCCESS && hkResult != NULL,
           "RegOpenKeyEx with KEY_WOW64_32KEY failed (err=%u)\n", ret);
        RegCloseKey(hkResult);
    }

    HeapFree(GetProcessHeap(), 0, sd);
    LocalFree(key_acl);
    FreeSid(world_sid);
    RegDeleteKeyA(hkRoot64, "");
    RegCloseKey(hkRoot64);
    RegDeleteKeyA(hkRoot32, "");
    RegCloseKey(hkRoot32);
}