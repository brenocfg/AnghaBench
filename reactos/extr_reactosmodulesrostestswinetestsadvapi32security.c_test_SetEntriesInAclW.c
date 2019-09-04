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
typedef  char WCHAR ;
struct TYPE_6__ {int MultipleTrusteeOperation; void* ptstrName; void* TrusteeForm; int /*<<< orphan*/ * pMultipleTrustee; int /*<<< orphan*/  TrusteeType; } ;
struct TYPE_8__ {TYPE_1__ Trustee; int /*<<< orphan*/  grfAccessMode; int /*<<< orphan*/  grfInheritance; int /*<<< orphan*/  grfAccessPermissions; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ SID_IDENTIFIER_AUTHORITY ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  void* PSID ;
typedef  int /*<<< orphan*/ * PACL ;
typedef  void* LPWSTR ;
typedef  TYPE_3__ EXPLICIT_ACCESSW ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_REVISION ; 
 int /*<<< orphan*/  AddAccessAllowedAce (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  AllocateAndInitializeSid (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  DOMAIN_ALIAS_RID_USERS ; 
 int /*<<< orphan*/  ERROR_CALL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FreeSid (void*) ; 
 int /*<<< orphan*/  GRANT_ACCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetSystemDefaultLangID () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitializeAcl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 scalar_t__ LANG_ENGLISH ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NO_INHERITANCE ; 
 void* NO_MULTIPLE_TRUSTEE ; 
 scalar_t__ PRIMARYLANGID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REVOKE_ACCESS ; 
 int /*<<< orphan*/  SECURITY_BUILTIN_DOMAIN_RID ; 
 int /*<<< orphan*/  SECURITY_NT_AUTHORITY ; 
 int /*<<< orphan*/  SECURITY_WORLD_RID ; 
 int /*<<< orphan*/  SECURITY_WORLD_SID_AUTHORITY ; 
 int /*<<< orphan*/  SET_ACCESS ; 
 void* TRUSTEE_BAD_FORM ; 
 int TRUSTEE_IS_IMPERSONATE ; 
 void* TRUSTEE_IS_NAME ; 
 void* TRUSTEE_IS_SID ; 
 int /*<<< orphan*/  TRUSTEE_IS_UNKNOWN ; 
 int /*<<< orphan*/  TRUSTEE_IS_WELL_KNOWN_GROUP ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pSetEntriesInAclW (int,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SetEntriesInAclW(void)
{
    DWORD res;
    PSID EveryoneSid = NULL, UsersSid = NULL;
    PACL OldAcl = NULL, NewAcl;
    SID_IDENTIFIER_AUTHORITY SIDAuthWorld = { SECURITY_WORLD_SID_AUTHORITY };
    SID_IDENTIFIER_AUTHORITY SIDAuthNT = { SECURITY_NT_AUTHORITY };
    EXPLICIT_ACCESSW ExplicitAccess;
    static const WCHAR wszEveryone[] = {'E','v','e','r','y','o','n','e',0};
    static const WCHAR wszCurrentUser[] = { 'C','U','R','R','E','N','T','_','U','S','E','R','\0'};

    if (!pSetEntriesInAclW)
    {
        win_skip("SetEntriesInAclW is not available\n");
        return;
    }

    NewAcl = (PACL)0xdeadbeef;
    res = pSetEntriesInAclW(0, NULL, NULL, &NewAcl);
    if(res == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("SetEntriesInAclW is not implemented\n");
        return;
    }
    ok(res == ERROR_SUCCESS, "SetEntriesInAclW failed: %u\n", res);
    ok(NewAcl == NULL ||
        broken(NewAcl != NULL), /* NT4 */
        "NewAcl=%p, expected NULL\n", NewAcl);
    LocalFree(NewAcl);

    OldAcl = HeapAlloc(GetProcessHeap(), 0, 256);
    res = InitializeAcl(OldAcl, 256, ACL_REVISION);
    if(!res && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("ACLs not implemented - skipping tests\n");
        HeapFree(GetProcessHeap(), 0, OldAcl);
        return;
    }
    ok(res, "InitializeAcl failed with error %d\n", GetLastError());

    res = AllocateAndInitializeSid( &SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &EveryoneSid);
    ok(res, "AllocateAndInitializeSid failed with error %d\n", GetLastError());

    res = AllocateAndInitializeSid( &SIDAuthNT, 2, SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_USERS, 0, 0, 0, 0, 0, 0, &UsersSid);
    ok(res, "AllocateAndInitializeSid failed with error %d\n", GetLastError());

    res = AddAccessAllowedAce(OldAcl, ACL_REVISION, KEY_READ, UsersSid);
    ok(res, "AddAccessAllowedAce failed with error %d\n", GetLastError());

    ExplicitAccess.grfAccessPermissions = KEY_WRITE;
    ExplicitAccess.grfAccessMode = GRANT_ACCESS;
    ExplicitAccess.grfInheritance = NO_INHERITANCE;
    ExplicitAccess.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
    ExplicitAccess.Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ExplicitAccess.Trustee.ptstrName = EveryoneSid;
    ExplicitAccess.Trustee.MultipleTrusteeOperation = 0xDEADBEEF;
    ExplicitAccess.Trustee.pMultipleTrustee = (PVOID)0xDEADBEEF;
    res = pSetEntriesInAclW(1, &ExplicitAccess, OldAcl, &NewAcl);
    ok(res == ERROR_SUCCESS, "SetEntriesInAclW failed: %u\n", res);
    ok(NewAcl != NULL, "returned acl was NULL\n");
    LocalFree(NewAcl);

    ExplicitAccess.Trustee.TrusteeType = TRUSTEE_IS_UNKNOWN;
    ExplicitAccess.Trustee.pMultipleTrustee = NULL;
    ExplicitAccess.Trustee.MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE;
    res = pSetEntriesInAclW(1, &ExplicitAccess, OldAcl, &NewAcl);
    ok(res == ERROR_SUCCESS, "SetEntriesInAclW failed: %u\n", res);
    ok(NewAcl != NULL, "returned acl was NULL\n");
    LocalFree(NewAcl);

    if (PRIMARYLANGID(GetSystemDefaultLangID()) != LANG_ENGLISH)
    {
        skip("Non-English locale (test with hardcoded 'Everyone')\n");
    }
    else
    {
        ExplicitAccess.Trustee.TrusteeForm = TRUSTEE_IS_NAME;
        ExplicitAccess.Trustee.ptstrName = (LPWSTR)wszEveryone;
        res = pSetEntriesInAclW(1, &ExplicitAccess, OldAcl, &NewAcl);
        ok(res == ERROR_SUCCESS, "SetEntriesInAclW failed: %u\n", res);
        ok(NewAcl != NULL, "returned acl was NULL\n");
        LocalFree(NewAcl);

        ExplicitAccess.Trustee.TrusteeForm = TRUSTEE_BAD_FORM;
        res = pSetEntriesInAclW(1, &ExplicitAccess, OldAcl, &NewAcl);
        ok(res == ERROR_INVALID_PARAMETER ||
            broken(res == ERROR_NOT_SUPPORTED), /* NT4 */
            "SetEntriesInAclW failed: %u\n", res);
        ok(NewAcl == NULL ||
            broken(NewAcl != NULL), /* NT4 */
            "returned acl wasn't NULL: %p\n", NewAcl);

        ExplicitAccess.Trustee.TrusteeForm = TRUSTEE_IS_NAME;
        ExplicitAccess.Trustee.MultipleTrusteeOperation = TRUSTEE_IS_IMPERSONATE;
        res = pSetEntriesInAclW(1, &ExplicitAccess, OldAcl, &NewAcl);
        ok(res == ERROR_INVALID_PARAMETER ||
            broken(res == ERROR_NOT_SUPPORTED), /* NT4 */
            "SetEntriesInAclW failed: %u\n", res);
        ok(NewAcl == NULL ||
            broken(NewAcl != NULL), /* NT4 */
            "returned acl wasn't NULL: %p\n", NewAcl);

        ExplicitAccess.Trustee.MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE;
        ExplicitAccess.grfAccessMode = SET_ACCESS;
        res = pSetEntriesInAclW(1, &ExplicitAccess, OldAcl, &NewAcl);
        ok(res == ERROR_SUCCESS, "SetEntriesInAclW failed: %u\n", res);
        ok(NewAcl != NULL, "returned acl was NULL\n");
        LocalFree(NewAcl);
    }

    ExplicitAccess.Trustee.TrusteeForm = TRUSTEE_IS_NAME;
    ExplicitAccess.Trustee.ptstrName = (LPWSTR)wszCurrentUser;
    res = pSetEntriesInAclW(1, &ExplicitAccess, OldAcl, &NewAcl);
    ok(res == ERROR_SUCCESS, "SetEntriesInAclW failed: %u\n", res);
    ok(NewAcl != NULL, "returned acl was NULL\n");
    LocalFree(NewAcl);

    ExplicitAccess.grfAccessMode = REVOKE_ACCESS;
    ExplicitAccess.Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ExplicitAccess.Trustee.ptstrName = UsersSid;
    res = pSetEntriesInAclW(1, &ExplicitAccess, OldAcl, &NewAcl);
    ok(res == ERROR_SUCCESS, "SetEntriesInAclW failed: %u\n", res);
    ok(NewAcl != NULL, "returned acl was NULL\n");
    LocalFree(NewAcl);

    FreeSid(UsersSid);
    FreeSid(EveryoneSid);
    HeapFree(GetProcessHeap(), 0, OldAcl);
}