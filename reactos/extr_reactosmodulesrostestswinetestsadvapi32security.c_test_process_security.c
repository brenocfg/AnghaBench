#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsa ;
typedef  int /*<<< orphan*/  startup ;
typedef  int /*<<< orphan*/  psa ;
typedef  int /*<<< orphan*/  domain ;
typedef  int /*<<< orphan*/  account ;
struct TYPE_33__ {int /*<<< orphan*/ * hThread; int /*<<< orphan*/ * hProcess; } ;
struct TYPE_32__ {int nLength; void* bInheritHandle; TYPE_4__* lpSecurityDescriptor; } ;
struct TYPE_28__ {int /*<<< orphan*/ * Sid; } ;
struct TYPE_31__ {int /*<<< orphan*/  Control; scalar_t__ Revision; TYPE_1__ User; int /*<<< orphan*/ * PrimaryGroup; int /*<<< orphan*/ * Owner; } ;
struct TYPE_30__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_29__ {int cb; int /*<<< orphan*/  wShowWindow; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_2__ STARTUPINFOA ;
typedef  int SID_NAME_USE ;
typedef  TYPE_3__ SID_IDENTIFIER_AUTHORITY ;
typedef  TYPE_4__ SECURITY_DESCRIPTOR ;
typedef  TYPE_5__ SECURITY_ATTRIBUTES ;
typedef  TYPE_4__* PTOKEN_USER ;
typedef  TYPE_4__* PTOKEN_PRIMARY_GROUP ;
typedef  TYPE_4__* PTOKEN_OWNER ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  TYPE_9__ PROCESS_INFORMATION ;
typedef  TYPE_4__* PACL ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_REVISION ; 
 int AddAccessAllowedAce (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int AddAccessDeniedAce (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int AllocateAndInitializeSid (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CHECK_SET_SECURITY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateEventA (int /*<<< orphan*/ *,void*,void*,char*) ; 
 int CreateProcessA (int /*<<< orphan*/ *,char*,TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_9__*) ; 
 int /*<<< orphan*/  DACL_SECURITY_INFORMATION ; 
 int /*<<< orphan*/  ERROR_ACCESS_DENIED ; 
 int ERROR_CALL_NOT_IMPLEMENTED ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_INVALID_SECURITY_DESCR ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  ERROR_UNKNOWN_REVISION ; 
 int /*<<< orphan*/  EqualPrefixSid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeSid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GROUP_SECURITY_INFORMATION ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetTokenInformation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int,int*) ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int InitializeAcl (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int InitializeSecurityDescriptor (TYPE_4__*,scalar_t__) ; 
 int LookupAccountSidA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int*,char*,int*,int*) ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OWNER_SECURITY_INFORMATION ; 
 int OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PROCESS_ALL_ACCESS ; 
 int /*<<< orphan*/  PROCESS_ALL_ACCESS_NT4 ; 
 int /*<<< orphan*/  PROCESS_VM_READ ; 
 int /*<<< orphan*/  SACL_SECURITY_INFORMATION ; 
 int SECURITY_DESCRIPTOR_MIN_LENGTH ; 
 scalar_t__ SECURITY_DESCRIPTOR_REVISION ; 
 int /*<<< orphan*/  SECURITY_WORLD_RID ; 
 int /*<<< orphan*/  SECURITY_WORLD_SID_AUTHORITY ; 
 int /*<<< orphan*/  SE_DACL_PRESENT ; 
 int SPECIFIC_RIGHTS_ALL ; 
 int STANDARD_RIGHTS_ALL ; 
 int /*<<< orphan*/  STARTF_USESHOWWINDOW ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int SetSecurityDescriptorDacl (TYPE_4__*,void*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int SetSecurityDescriptorGroup (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SetSecurityDescriptorOwner (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SidTypeGroup ; 
 int /*<<< orphan*/  TEST_GRANTED_ACCESS2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  THREAD_ALL_ACCESS ; 
 int /*<<< orphan*/  THREAD_ALL_ACCESS_NT4 ; 
 int /*<<< orphan*/  THREAD_SET_THREAD_TOKEN ; 
 void* TRUE ; 
 int /*<<< orphan*/  TokenOwner ; 
 int /*<<< orphan*/  TokenPrimaryGroup ; 
 int /*<<< orphan*/  TokenUser ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 char** myARGV ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_group_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_owner_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_sid_str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  winetest_wait_child_process (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_process_security(void)
{
    BOOL res;
    PTOKEN_USER user;
    PTOKEN_OWNER owner;
    PTOKEN_PRIMARY_GROUP group;
    PSID AdminSid = NULL, UsersSid = NULL, UserSid = NULL;
    PACL Acl = NULL, ThreadAcl = NULL;
    SECURITY_DESCRIPTOR *SecurityDescriptor = NULL, *ThreadSecurityDescriptor = NULL;
    char buffer[MAX_PATH], account[MAX_PATH], domain[MAX_PATH];
    PROCESS_INFORMATION info;
    STARTUPINFOA startup;
    SECURITY_ATTRIBUTES psa, tsa;
    HANDLE token, event;
    DWORD size, acc_size, dom_size, ret;
    SID_IDENTIFIER_AUTHORITY SIDAuthWorld = { SECURITY_WORLD_SID_AUTHORITY };
    PSID EveryoneSid = NULL;
    SID_NAME_USE use;

    Acl = HeapAlloc(GetProcessHeap(), 0, 256);
    res = InitializeAcl(Acl, 256, ACL_REVISION);
    if (!res && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("ACLs not implemented - skipping tests\n");
        HeapFree(GetProcessHeap(), 0, Acl);
        return;
    }
    ok(res, "InitializeAcl failed with error %d\n", GetLastError());

    res = AllocateAndInitializeSid( &SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &EveryoneSid);
    ok(res, "AllocateAndInitializeSid failed with error %d\n", GetLastError());

    /* get owner from the token we might be running as a user not admin */
    res = OpenProcessToken( GetCurrentProcess(), MAXIMUM_ALLOWED, &token );
    ok(res, "OpenProcessToken failed with error %d\n", GetLastError());
    if (!res)
    {
        HeapFree(GetProcessHeap(), 0, Acl);
        return;
    }

    res = GetTokenInformation( token, TokenOwner, NULL, 0, &size );
    ok(!res, "Expected failure, got %d\n", res);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "Expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());

    owner = HeapAlloc(GetProcessHeap(), 0, size);
    res = GetTokenInformation( token, TokenOwner, owner, size, &size );
    ok(res, "GetTokenInformation failed with error %d\n", GetLastError());
    AdminSid = owner->Owner;
    test_sid_str(AdminSid);

    res = GetTokenInformation( token, TokenPrimaryGroup, NULL, 0, &size );
    ok(!res, "Expected failure, got %d\n", res);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "Expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());

    group = HeapAlloc(GetProcessHeap(), 0, size);
    res = GetTokenInformation( token, TokenPrimaryGroup, group, size, &size );
    ok(res, "GetTokenInformation failed with error %d\n", GetLastError());
    UsersSid = group->PrimaryGroup;
    test_sid_str(UsersSid);

    acc_size = sizeof(account);
    dom_size = sizeof(domain);
    ret = LookupAccountSidA( NULL, UsersSid, account, &acc_size, domain, &dom_size, &use );
    ok(ret, "LookupAccountSid failed with %d\n", ret);
    ok(use == SidTypeGroup, "expect SidTypeGroup, got %d\n", use);
    ok(!strcmp(account, "None"), "expect None, got %s\n", account);

    res = GetTokenInformation( token, TokenUser, NULL, 0, &size );
    ok(!res, "Expected failure, got %d\n", res);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "Expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());

    user = HeapAlloc(GetProcessHeap(), 0, size);
    res = GetTokenInformation( token, TokenUser, user, size, &size );
    ok(res, "GetTokenInformation failed with error %d\n", GetLastError());
    UserSid = user->User.Sid;
    test_sid_str(UserSid);
    ok(EqualPrefixSid(UsersSid, UserSid), "TokenPrimaryGroup Sid and TokenUser Sid don't match.\n");

    CloseHandle( token );
    if (!res)
    {
        HeapFree(GetProcessHeap(), 0, group);
        HeapFree(GetProcessHeap(), 0, owner);
        HeapFree(GetProcessHeap(), 0, user);
        HeapFree(GetProcessHeap(), 0, Acl);
        return;
    }

    res = AddAccessDeniedAce(Acl, ACL_REVISION, PROCESS_VM_READ, AdminSid);
    ok(res, "AddAccessDeniedAce failed with error %d\n", GetLastError());
    res = AddAccessAllowedAce(Acl, ACL_REVISION, PROCESS_ALL_ACCESS, AdminSid);
    ok(res, "AddAccessAllowedAce failed with error %d\n", GetLastError());

    SecurityDescriptor = HeapAlloc(GetProcessHeap(), 0, SECURITY_DESCRIPTOR_MIN_LENGTH);
    res = InitializeSecurityDescriptor(SecurityDescriptor, SECURITY_DESCRIPTOR_REVISION);
    ok(res, "InitializeSecurityDescriptor failed with error %d\n", GetLastError());

    event = CreateEventA( NULL, TRUE, TRUE, "test_event" );
    ok(event != NULL, "CreateEvent %d\n", GetLastError());

    SecurityDescriptor->Revision = 0;
    CHECK_SET_SECURITY( event, OWNER_SECURITY_INFORMATION, ERROR_UNKNOWN_REVISION );
    SecurityDescriptor->Revision = SECURITY_DESCRIPTOR_REVISION;

    CHECK_SET_SECURITY( event, OWNER_SECURITY_INFORMATION, ERROR_INVALID_SECURITY_DESCR );
    CHECK_SET_SECURITY( event, GROUP_SECURITY_INFORMATION, ERROR_INVALID_SECURITY_DESCR );
    CHECK_SET_SECURITY( event, SACL_SECURITY_INFORMATION, ERROR_ACCESS_DENIED );
    CHECK_SET_SECURITY( event, DACL_SECURITY_INFORMATION, ERROR_SUCCESS );
    /* NULL DACL is valid and means that everyone has access */
    SecurityDescriptor->Control |= SE_DACL_PRESENT;
    CHECK_SET_SECURITY( event, DACL_SECURITY_INFORMATION, ERROR_SUCCESS );

    /* Set owner and group and dacl */
    res = SetSecurityDescriptorOwner(SecurityDescriptor, AdminSid, FALSE);
    ok(res, "SetSecurityDescriptorOwner failed with error %d\n", GetLastError());
    CHECK_SET_SECURITY( event, OWNER_SECURITY_INFORMATION, ERROR_SUCCESS );
    test_owner_equal( event, AdminSid, __LINE__ );

    res = SetSecurityDescriptorGroup(SecurityDescriptor, EveryoneSid, FALSE);
    ok(res, "SetSecurityDescriptorGroup failed with error %d\n", GetLastError());
    CHECK_SET_SECURITY( event, GROUP_SECURITY_INFORMATION, ERROR_SUCCESS );
    test_group_equal( event, EveryoneSid, __LINE__ );

    res = SetSecurityDescriptorDacl(SecurityDescriptor, TRUE, Acl, FALSE);
    ok(res, "SetSecurityDescriptorDacl failed with error %d\n", GetLastError());
    CHECK_SET_SECURITY( event, DACL_SECURITY_INFORMATION, ERROR_SUCCESS );
    /* setting a dacl should not change the owner or group */
    test_owner_equal( event, AdminSid, __LINE__ );
    test_group_equal( event, EveryoneSid, __LINE__ );

    /* Test again with a different SID in case the previous SID also happens to
     * be the one that is incorrectly replacing the group. */
    res = SetSecurityDescriptorGroup(SecurityDescriptor, UsersSid, FALSE);
    ok(res, "SetSecurityDescriptorGroup failed with error %d\n", GetLastError());
    CHECK_SET_SECURITY( event, GROUP_SECURITY_INFORMATION, ERROR_SUCCESS );
    test_group_equal( event, UsersSid, __LINE__ );

    res = SetSecurityDescriptorDacl(SecurityDescriptor, TRUE, Acl, FALSE);
    ok(res, "SetSecurityDescriptorDacl failed with error %d\n", GetLastError());
    CHECK_SET_SECURITY( event, DACL_SECURITY_INFORMATION, ERROR_SUCCESS );
    test_group_equal( event, UsersSid, __LINE__ );

    sprintf(buffer, "%s tests/security.c test", myARGV[0]);
    memset(&startup, 0, sizeof(startup));
    startup.cb = sizeof(startup);
    startup.dwFlags = STARTF_USESHOWWINDOW;
    startup.wShowWindow = SW_SHOWNORMAL;

    psa.nLength = sizeof(psa);
    psa.lpSecurityDescriptor = SecurityDescriptor;
    psa.bInheritHandle = TRUE;

    ThreadSecurityDescriptor = HeapAlloc( GetProcessHeap(), 0, SECURITY_DESCRIPTOR_MIN_LENGTH );
    res = InitializeSecurityDescriptor( ThreadSecurityDescriptor, SECURITY_DESCRIPTOR_REVISION );
    ok(res, "InitializeSecurityDescriptor failed with error %d\n", GetLastError());

    ThreadAcl = HeapAlloc( GetProcessHeap(), 0, 256 );
    res = InitializeAcl( ThreadAcl, 256, ACL_REVISION );
    ok(res, "InitializeAcl failed with error %d\n", GetLastError());
    res = AddAccessDeniedAce( ThreadAcl, ACL_REVISION, THREAD_SET_THREAD_TOKEN, AdminSid );
    ok(res, "AddAccessDeniedAce failed with error %d\n", GetLastError() );
    res = AddAccessAllowedAce( ThreadAcl, ACL_REVISION, THREAD_ALL_ACCESS, AdminSid );
    ok(res, "AddAccessAllowedAce failed with error %d\n", GetLastError());

    res = SetSecurityDescriptorOwner( ThreadSecurityDescriptor, AdminSid, FALSE );
    ok(res, "SetSecurityDescriptorOwner failed with error %d\n", GetLastError());
    res = SetSecurityDescriptorGroup( ThreadSecurityDescriptor, UsersSid, FALSE );
    ok(res, "SetSecurityDescriptorGroup failed with error %d\n", GetLastError());
    res = SetSecurityDescriptorDacl( ThreadSecurityDescriptor, TRUE, ThreadAcl, FALSE );
    ok(res, "SetSecurityDescriptorDacl failed with error %d\n", GetLastError());

    tsa.nLength = sizeof(tsa);
    tsa.lpSecurityDescriptor = ThreadSecurityDescriptor;
    tsa.bInheritHandle = TRUE;

    /* Doesn't matter what ACL say we should get full access for ourselves */
    res = CreateProcessA( NULL, buffer, &psa, &tsa, FALSE, 0, NULL, NULL, &startup, &info );
    ok(res, "CreateProcess with err:%d\n", GetLastError());
    TEST_GRANTED_ACCESS2( info.hProcess, PROCESS_ALL_ACCESS_NT4,
                          STANDARD_RIGHTS_ALL | SPECIFIC_RIGHTS_ALL );
    TEST_GRANTED_ACCESS2( info.hThread, THREAD_ALL_ACCESS_NT4,
                          STANDARD_RIGHTS_ALL | SPECIFIC_RIGHTS_ALL );
    winetest_wait_child_process( info.hProcess );

    FreeSid(EveryoneSid);
    CloseHandle( info.hProcess );
    CloseHandle( info.hThread );
    CloseHandle( event );
    HeapFree(GetProcessHeap(), 0, group);
    HeapFree(GetProcessHeap(), 0, owner);
    HeapFree(GetProcessHeap(), 0, user);
    HeapFree(GetProcessHeap(), 0, Acl);
    HeapFree(GetProcessHeap(), 0, SecurityDescriptor);
    HeapFree(GetProcessHeap(), 0, ThreadAcl);
    HeapFree(GetProcessHeap(), 0, ThreadSecurityDescriptor);
}