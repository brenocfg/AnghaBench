#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int ULONG ;
struct TYPE_16__ {void* TrusteeForm; void* ptstrName; int /*<<< orphan*/  TrusteeType; int /*<<< orphan*/ * pMultipleTrustee; int /*<<< orphan*/  MultipleTrusteeOperation; } ;
struct TYPE_18__ {TYPE_1__ Trustee; scalar_t__ grfAccessMode; int /*<<< orphan*/  grfInheritance; int /*<<< orphan*/  grfAccessPermissions; } ;
struct TYPE_17__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ SID_IDENTIFIER_AUTHORITY ;
typedef  void* PSID ;
typedef  TYPE_3__* PACL ;
typedef  void* LPWSTR ;
typedef  TYPE_3__ EXPLICIT_ACCESSW ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_REVISION ; 
 int /*<<< orphan*/  AddAccessAllowedAce (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  AllocateAndInitializeSid (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  DOMAIN_ALIAS_RID_USERS ; 
 int /*<<< orphan*/  ERROR_CALL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  EqualSid (void*,void*) ; 
 int /*<<< orphan*/  FreeSid (void*) ; 
 scalar_t__ GRANT_ACCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  InitializeAcl (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  LocalFree (TYPE_3__*) ; 
 int /*<<< orphan*/  NO_INHERITANCE ; 
 int /*<<< orphan*/  NO_MULTIPLE_TRUSTEE ; 
 scalar_t__ REVOKE_ACCESS ; 
 int /*<<< orphan*/  SECURITY_BUILTIN_DOMAIN_RID ; 
 int /*<<< orphan*/  SECURITY_NT_AUTHORITY ; 
 int /*<<< orphan*/  SECURITY_WORLD_RID ; 
 int /*<<< orphan*/  SECURITY_WORLD_SID_AUTHORITY ; 
 void* TRUSTEE_IS_NAME ; 
 void* TRUSTEE_IS_SID ; 
 int /*<<< orphan*/  TRUSTEE_IS_UNKNOWN ; 
 int /*<<< orphan*/  TRUSTEE_IS_WELL_KNOWN_GROUP ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pGetExplicitEntriesFromAclW (TYPE_3__*,int*,TYPE_3__**) ; 
 int /*<<< orphan*/  pSetEntriesInAclW (int,TYPE_3__*,TYPE_3__*,TYPE_3__**) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetExplicitEntriesFromAclW(void)
{
    static const WCHAR wszCurrentUser[] = { 'C','U','R','R','E','N','T','_','U','S','E','R','\0'};
    SID_IDENTIFIER_AUTHORITY SIDAuthWorld = { SECURITY_WORLD_SID_AUTHORITY };
    SID_IDENTIFIER_AUTHORITY SIDAuthNT = { SECURITY_NT_AUTHORITY };
    PSID everyone_sid = NULL, users_sid = NULL;
    EXPLICIT_ACCESSW access;
    EXPLICIT_ACCESSW *access2;
    PACL new_acl, old_acl = NULL;
    ULONG count;
    DWORD res;

    if (!pGetExplicitEntriesFromAclW)
    {
        win_skip("GetExplicitEntriesFromAclW is not available\n");
        return;
    }

    if (!pSetEntriesInAclW)
    {
        win_skip("SetEntriesInAclW is not available\n");
        return;
    }

    old_acl = HeapAlloc(GetProcessHeap(), 0, 256);
    res = InitializeAcl(old_acl, 256, ACL_REVISION);
    if(!res && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("ACLs not implemented - skipping tests\n");
        HeapFree(GetProcessHeap(), 0, old_acl);
        return;
    }
    ok(res, "InitializeAcl failed with error %d\n", GetLastError());

    res = AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &everyone_sid);
    ok(res, "AllocateAndInitializeSid failed with error %d\n", GetLastError());

    res = AllocateAndInitializeSid(&SIDAuthNT, 2, SECURITY_BUILTIN_DOMAIN_RID,
                                   DOMAIN_ALIAS_RID_USERS, 0, 0, 0, 0, 0, 0, &users_sid);
    ok(res, "AllocateAndInitializeSid failed with error %d\n", GetLastError());

    res = AddAccessAllowedAce(old_acl, ACL_REVISION, KEY_READ, users_sid);
    ok(res, "AddAccessAllowedAce failed with error %d\n", GetLastError());

    access2 = NULL;
    res = pGetExplicitEntriesFromAclW(old_acl, &count, &access2);
    ok(res == ERROR_SUCCESS, "GetExplicitEntriesFromAclW failed with error %d\n", GetLastError());
    ok(count == 1, "Expected count == 1, got %d\n", count);
    ok(access2[0].grfAccessMode == GRANT_ACCESS, "Expected GRANT_ACCESS, got %d\n", access2[0].grfAccessMode);
    ok(access2[0].grfAccessPermissions == KEY_READ, "Expected KEY_READ, got %d\n", access2[0].grfAccessPermissions);
    ok(access2[0].Trustee.TrusteeForm == TRUSTEE_IS_SID, "Expected SID trustee, got %d\n", access2[0].Trustee.TrusteeForm);
    ok(access2[0].grfInheritance == NO_INHERITANCE, "Expected NO_INHERITANCE, got %x\n", access2[0].grfInheritance);
    ok(EqualSid(access2[0].Trustee.ptstrName, users_sid), "Expected equal SIDs\n");
    LocalFree(access2);

    access.Trustee.MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE;
    access.Trustee.pMultipleTrustee = NULL;

    access.grfAccessPermissions = KEY_WRITE;
    access.grfAccessMode = GRANT_ACCESS;
    access.grfInheritance = NO_INHERITANCE;
    access.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
    access.Trustee.TrusteeForm = TRUSTEE_IS_SID;
    access.Trustee.ptstrName = everyone_sid;
    res = pSetEntriesInAclW(1, &access, old_acl, &new_acl);
    ok(res == ERROR_SUCCESS, "SetEntriesInAclW failed: %u\n", res);
    ok(new_acl != NULL, "returned acl was NULL\n");

    access2 = NULL;
    res = pGetExplicitEntriesFromAclW(new_acl, &count, &access2);
    ok(res == ERROR_SUCCESS, "GetExplicitEntriesFromAclW failed with error %d\n", GetLastError());
    ok(count == 2, "Expected count == 2, got %d\n", count);
    ok(access2[0].grfAccessMode == GRANT_ACCESS, "Expected GRANT_ACCESS, got %d\n", access2[0].grfAccessMode);
    ok(access2[0].grfAccessPermissions == KEY_WRITE, "Expected KEY_WRITE, got %d\n", access2[0].grfAccessPermissions);
    ok(access2[0].Trustee.TrusteeType == TRUSTEE_IS_UNKNOWN,
       "Expected TRUSTEE_IS_UNKNOWN trustee type, got %d\n", access2[0].Trustee.TrusteeType);
    ok(access2[0].Trustee.TrusteeForm == TRUSTEE_IS_SID, "Expected SID trustee, got %d\n", access2[0].Trustee.TrusteeForm);
    ok(access2[0].grfInheritance == NO_INHERITANCE, "Expected NO_INHERITANCE, got %x\n", access2[0].grfInheritance);
    ok(EqualSid(access2[0].Trustee.ptstrName, everyone_sid), "Expected equal SIDs\n");
    LocalFree(access2);
    LocalFree(new_acl);

    access.Trustee.TrusteeType = TRUSTEE_IS_UNKNOWN;
    res = pSetEntriesInAclW(1, &access, old_acl, &new_acl);
    ok(res == ERROR_SUCCESS, "SetEntriesInAclW failed: %u\n", res);
    ok(new_acl != NULL, "returned acl was NULL\n");

    access2 = NULL;
    res = pGetExplicitEntriesFromAclW(new_acl, &count, &access2);
    ok(res == ERROR_SUCCESS, "GetExplicitEntriesFromAclW failed with error %d\n", GetLastError());
    ok(count == 2, "Expected count == 2, got %d\n", count);
    ok(access2[0].grfAccessMode == GRANT_ACCESS, "Expected GRANT_ACCESS, got %d\n", access2[0].grfAccessMode);
    ok(access2[0].grfAccessPermissions == KEY_WRITE, "Expected KEY_WRITE, got %d\n", access2[0].grfAccessPermissions);
    ok(access2[0].Trustee.TrusteeType == TRUSTEE_IS_UNKNOWN,
       "Expected TRUSTEE_IS_UNKNOWN trustee type, got %d\n", access2[0].Trustee.TrusteeType);
    ok(access2[0].Trustee.TrusteeForm == TRUSTEE_IS_SID, "Expected SID trustee, got %d\n", access2[0].Trustee.TrusteeForm);
    ok(access2[0].grfInheritance == NO_INHERITANCE, "Expected NO_INHERITANCE, got %x\n", access2[0].grfInheritance);
    ok(EqualSid(access2[0].Trustee.ptstrName, everyone_sid), "Expected equal SIDs\n");
    LocalFree(access2);
    LocalFree(new_acl);

    access.Trustee.TrusteeForm = TRUSTEE_IS_NAME;
    access.Trustee.ptstrName = (LPWSTR)wszCurrentUser;
    res = pSetEntriesInAclW(1, &access, old_acl, &new_acl);
    ok(res == ERROR_SUCCESS, "SetEntriesInAclW failed: %u\n", res);
    ok(new_acl != NULL, "returned acl was NULL\n");

    access2 = NULL;
    res = pGetExplicitEntriesFromAclW(new_acl, &count, &access2);
    ok(res == ERROR_SUCCESS, "GetExplicitEntriesFromAclW failed with error %d\n", GetLastError());
    ok(count == 2, "Expected count == 2, got %d\n", count);
    ok(access2[0].grfAccessMode == GRANT_ACCESS, "Expected GRANT_ACCESS, got %d\n", access2[0].grfAccessMode);
    ok(access2[0].grfAccessPermissions == KEY_WRITE, "Expected KEY_WRITE, got %d\n", access2[0].grfAccessPermissions);
    ok(access2[0].Trustee.TrusteeType == TRUSTEE_IS_UNKNOWN,
       "Expected TRUSTEE_IS_UNKNOWN trustee type, got %d\n", access2[0].Trustee.TrusteeType);
    ok(access2[0].Trustee.TrusteeForm == TRUSTEE_IS_SID, "Expected SID trustee, got %d\n", access2[0].Trustee.TrusteeForm);
    ok(access2[0].grfInheritance == NO_INHERITANCE, "Expected NO_INHERITANCE, got %x\n", access2[0].grfInheritance);
    LocalFree(access2);
    LocalFree(new_acl);

    access.grfAccessMode = REVOKE_ACCESS;
    access.Trustee.TrusteeForm = TRUSTEE_IS_SID;
    access.Trustee.ptstrName = users_sid;
    res = pSetEntriesInAclW(1, &access, old_acl, &new_acl);
    ok(res == ERROR_SUCCESS, "SetEntriesInAclW failed: %u\n", res);
    ok(new_acl != NULL, "returned acl was NULL\n");

    access2 = (void *)0xdeadbeef;
    res = pGetExplicitEntriesFromAclW(new_acl, &count, &access2);
    ok(res == ERROR_SUCCESS, "GetExplicitEntriesFromAclW failed with error %d\n", GetLastError());
    ok(count == 0, "Expected count == 0, got %d\n", count);
    ok(access2 == NULL, "access2 was not NULL\n");
    LocalFree(new_acl);

    FreeSid(users_sid);
    FreeSid(everyone_sid);
    HeapFree(GetProcessHeap(), 0, old_acl);
}