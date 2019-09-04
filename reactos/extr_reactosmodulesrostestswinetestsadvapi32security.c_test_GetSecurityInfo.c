#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  domain_users_ptr ;
typedef  int /*<<< orphan*/  dacl ;
typedef  int /*<<< orphan*/  b ;
typedef  int /*<<< orphan*/  admin_ptr ;
typedef  int /*<<< orphan*/  acl_size ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_14__ {int Mask; int /*<<< orphan*/  SidStart; } ;
struct TYPE_13__ {int AceFlags; } ;
struct TYPE_12__ {int AceCount; } ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/ * Sid; } ;
struct TYPE_10__ {TYPE_1__ User; } ;
typedef  TYPE_2__ TOKEN_USER ;
typedef  TYPE_3__ SID_IDENTIFIER_AUTHORITY ;
typedef  int /*<<< orphan*/  SID ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  char** PSECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/ * PACL ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int BOOL ;
typedef  TYPE_4__ ACL_SIZE_INFORMATION ;
typedef  TYPE_5__ ACE_HEADER ;
typedef  TYPE_6__ ACCESS_ALLOWED_ACE ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_REVISION ; 
 int /*<<< orphan*/  AclSizeInformation ; 
 int /*<<< orphan*/  AllocateAndInitializeSid (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int CONTAINER_INHERIT_ACE ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DACL_SECURITY_INFORMATION ; 
 int ERROR_CALL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  ERROR_NO_TOKEN ; 
 int ERROR_SUCCESS ; 
 int EqualSid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  FreeSid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GENERIC_ALL ; 
 int GENERIC_READ ; 
 int GROUP_SECURITY_INFORMATION ; 
 scalar_t__ GetCurrentProcess () ; 
 int /*<<< orphan*/  GetCurrentThread () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetSecurityDescriptorDacl (char**,int*,int /*<<< orphan*/ **,int*) ; 
 int GetSecurityDescriptorGroup (char**,int /*<<< orphan*/ **,int*) ; 
 int GetSecurityDescriptorOwner (char**,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/ * GetSidSubAuthority (int /*<<< orphan*/ *,int) ; 
 int GetTokenInformation (scalar_t__,int /*<<< orphan*/ ,char*,int,int*) ; 
 int INHERIT_ONLY_ACE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int InitializeAcl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeSecurityDescriptor (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsValidAcl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (char**) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int OWNER_SECURITY_INFORMATION ; 
 int /*<<< orphan*/  OpenProcessToken (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  OpenThreadToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int PROCESS_ALL_ACCESS ; 
 int SECURITY_DESCRIPTOR_MIN_LENGTH ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_REVISION ; 
 int /*<<< orphan*/  SECURITY_NT_AUTHORITY ; 
 int /*<<< orphan*/  SE_FILE_OBJECT ; 
 int /*<<< orphan*/  SE_KERNEL_OBJECT ; 
 int SID_MAX_SUB_AUTHORITIES ; 
 int SetSecurityDescriptorDacl (char**,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TOKEN_READ ; 
 int TRUE ; 
 int /*<<< orphan*/  TokenUser ; 
 int WRITE_DAC ; 
 int /*<<< orphan*/  WinAccountDomainUsersSid ; 
 int /*<<< orphan*/  WinBuiltinAdministratorsSid ; 
 scalar_t__ broken (int) ; 
 int debugstr_sid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * myARGV ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pAddAccessAllowedAceEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pCreateWellKnownSid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int pGetAce (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int pGetAclInformation (int /*<<< orphan*/ *,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int pGetSecurityInfo (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char***) ; 
 int pSetSecurityInfo (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetSecurityInfo(void)
{
    char domain_users_ptr[sizeof(TOKEN_USER) + sizeof(SID) + sizeof(DWORD)*SID_MAX_SUB_AUTHORITIES];
    char b[sizeof(TOKEN_USER) + sizeof(SID) + sizeof(DWORD)*SID_MAX_SUB_AUTHORITIES];
    char admin_ptr[sizeof(SID)+sizeof(ULONG)*SID_MAX_SUB_AUTHORITIES], dacl[100];
    PSID domain_users_sid = (PSID) domain_users_ptr, domain_sid;
    SID_IDENTIFIER_AUTHORITY sia = { SECURITY_NT_AUTHORITY };
    int domain_users_ace_id = -1, admins_ace_id = -1, i;
    DWORD sid_size = sizeof(admin_ptr), l = sizeof(b);
    PSID admin_sid = (PSID) admin_ptr, user_sid;
    char sd[SECURITY_DESCRIPTOR_MIN_LENGTH];
    BOOL owner_defaulted, group_defaulted;
    BOOL dacl_defaulted, dacl_present;
    ACL_SIZE_INFORMATION acl_size;
    PSECURITY_DESCRIPTOR pSD;
    ACCESS_ALLOWED_ACE *ace;
    HANDLE token, obj;
    PSID owner, group;
    BOOL bret = TRUE;
    PACL pDacl;
    BYTE flags;
    DWORD ret;

    if (!pGetSecurityInfo || !pSetSecurityInfo)
    {
        win_skip("[Get|Set]SecurityInfo is not available\n");
        return;
    }

    if (!OpenThreadToken(GetCurrentThread(), TOKEN_READ, TRUE, &token))
    {
        if (GetLastError() != ERROR_NO_TOKEN) bret = FALSE;
        else if (!OpenProcessToken(GetCurrentProcess(), TOKEN_READ, &token)) bret = FALSE;
    }
    if (!bret)
    {
        win_skip("Failed to get current user token\n");
        return;
    }
    bret = GetTokenInformation(token, TokenUser, b, l, &l);
    ok(bret, "GetTokenInformation(TokenUser) failed with error %d\n", GetLastError());
    CloseHandle( token );
    user_sid = ((TOKEN_USER *)b)->User.Sid;

    /* Create something.  Files have lots of associated security info.  */
    obj = CreateFileA(myARGV[0], GENERIC_READ|WRITE_DAC, FILE_SHARE_READ, NULL,
                      OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (obj == INVALID_HANDLE_VALUE)
    {
        skip("Couldn't create an object for GetSecurityInfo test\n");
        return;
    }

    ret = pGetSecurityInfo(obj, SE_FILE_OBJECT,
                          OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION,
                          &owner, &group, &pDacl, NULL, &pSD);
    if (ret == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("GetSecurityInfo is not implemented\n");
        CloseHandle(obj);
        return;
    }
    ok(ret == ERROR_SUCCESS, "GetSecurityInfo returned %d\n", ret);
    ok(pSD != NULL, "GetSecurityInfo\n");
    ok(owner != NULL, "GetSecurityInfo\n");
    ok(group != NULL, "GetSecurityInfo\n");
    if (pDacl != NULL)
        ok(IsValidAcl(pDacl), "GetSecurityInfo\n");
    else
        win_skip("No ACL information returned\n");

    LocalFree(pSD);

    if (!pCreateWellKnownSid)
    {
        win_skip("NULL parameter test would crash on NT4\n");
        CloseHandle(obj);
        return;
    }

    /* If we don't ask for the security descriptor, Windows will still give us
       the other stuff, leaving us no way to free it.  */
    ret = pGetSecurityInfo(obj, SE_FILE_OBJECT,
                          OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION,
                          &owner, &group, &pDacl, NULL, NULL);
    ok(ret == ERROR_SUCCESS, "GetSecurityInfo returned %d\n", ret);
    ok(owner != NULL, "GetSecurityInfo\n");
    ok(group != NULL, "GetSecurityInfo\n");
    if (pDacl != NULL)
        ok(IsValidAcl(pDacl), "GetSecurityInfo\n");
    else
        win_skip("No ACL information returned\n");

    /* Create security descriptor information and test that it comes back the same */
    pSD = &sd;
    pDacl = (PACL)&dacl;
    InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION);
    pCreateWellKnownSid(WinBuiltinAdministratorsSid, NULL, admin_sid, &sid_size);
    bret = InitializeAcl(pDacl, sizeof(dacl), ACL_REVISION);
    ok(bret, "Failed to initialize ACL.\n");
    bret = pAddAccessAllowedAceEx(pDacl, ACL_REVISION, 0, GENERIC_ALL, user_sid);
    ok(bret, "Failed to add Current User to ACL.\n");
    bret = pAddAccessAllowedAceEx(pDacl, ACL_REVISION, 0, GENERIC_ALL, admin_sid);
    ok(bret, "Failed to add Administrator Group to ACL.\n");
    bret = SetSecurityDescriptorDacl(pSD, TRUE, pDacl, FALSE);
    ok(bret, "Failed to add ACL to security descriptor.\n");
    ret = pSetSecurityInfo(obj, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION,
                          NULL, NULL, pDacl, NULL);
    ok(ret == ERROR_SUCCESS, "SetSecurityInfo returned %d\n", ret);
    ret = pGetSecurityInfo(obj, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION,
                          NULL, NULL, &pDacl, NULL, &pSD);
    ok(ret == ERROR_SUCCESS, "GetSecurityInfo returned %d\n", ret);
    ok(pDacl && IsValidAcl(pDacl), "GetSecurityInfo returned invalid DACL.\n");
    bret = pGetAclInformation(pDacl, &acl_size, sizeof(acl_size), AclSizeInformation);
    ok(bret, "GetAclInformation failed\n");
    if (acl_size.AceCount > 0)
    {
        bret = pGetAce(pDacl, 0, (VOID **)&ace);
        ok(bret, "Failed to get Current User ACE.\n");
        bret = EqualSid(&ace->SidStart, user_sid);
        ok(bret, "Current User ACE (%s) != Current User SID (%s).\n", debugstr_sid(&ace->SidStart), debugstr_sid(user_sid));
        ok(((ACE_HEADER *)ace)->AceFlags == 0,
           "Current User ACE has unexpected flags (0x%x != 0x0)\n", ((ACE_HEADER *)ace)->AceFlags);
        ok(ace->Mask == 0x1f01ff, "Current User ACE has unexpected mask (0x%x != 0x1f01ff)\n",
                                  ace->Mask);
    }
    if (acl_size.AceCount > 1)
    {
        bret = pGetAce(pDacl, 1, (VOID **)&ace);
        ok(bret, "Failed to get Administators Group ACE.\n");
        bret = EqualSid(&ace->SidStart, admin_sid);
        ok(bret, "Administators Group ACE (%s) != Administators Group SID (%s).\n", debugstr_sid(&ace->SidStart), debugstr_sid(admin_sid));
        ok(((ACE_HEADER *)ace)->AceFlags == 0,
           "Administators Group ACE has unexpected flags (0x%x != 0x0)\n", ((ACE_HEADER *)ace)->AceFlags);
        ok(ace->Mask == 0x1f01ff,
                     "Administators Group ACE has unexpected mask (0x%x != 0x1f01ff)\n", ace->Mask);
    }
    LocalFree(pSD);
    CloseHandle(obj);

    /* Obtain the "domain users" SID from the user SID */
    if (!AllocateAndInitializeSid(&sia, 4, *GetSidSubAuthority(user_sid, 0),
                                  *GetSidSubAuthority(user_sid, 1),
                                  *GetSidSubAuthority(user_sid, 2),
                                  *GetSidSubAuthority(user_sid, 3), 0, 0, 0, 0, &domain_sid))
    {
        win_skip("Failed to get current domain SID\n");
        return;
    }
    sid_size = sizeof(domain_users_ptr);
    pCreateWellKnownSid(WinAccountDomainUsersSid, domain_sid, domain_users_sid, &sid_size);
    FreeSid(domain_sid);

    /* Test querying the ownership of a process */
    ret = pGetSecurityInfo(GetCurrentProcess(), SE_KERNEL_OBJECT,
                           OWNER_SECURITY_INFORMATION|GROUP_SECURITY_INFORMATION,
                           NULL, NULL, NULL, NULL, &pSD);
    ok(!ret, "GetNamedSecurityInfo failed with error %d\n", ret);

    bret = GetSecurityDescriptorOwner(pSD, &owner, &owner_defaulted);
    ok(bret, "GetSecurityDescriptorOwner failed with error %d\n", GetLastError());
    ok(owner != NULL, "owner should not be NULL\n");
    ok(EqualSid(owner, admin_sid) || EqualSid(owner, user_sid),
       "Process owner SID != Administrators SID.\n");

    bret = GetSecurityDescriptorGroup(pSD, &group, &group_defaulted);
    ok(bret, "GetSecurityDescriptorGroup failed with error %d\n", GetLastError());
    ok(group != NULL, "group should not be NULL\n");
    ok(EqualSid(group, domain_users_sid), "Process group SID != Domain Users SID.\n");
    LocalFree(pSD);

    /* Test querying the DACL of a process */
    ret = pGetSecurityInfo(GetCurrentProcess(), SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION,
                                   NULL, NULL, NULL, NULL, &pSD);
    ok(!ret, "GetSecurityInfo failed with error %d\n", ret);

    bret = GetSecurityDescriptorDacl(pSD, &dacl_present, &pDacl, &dacl_defaulted);
    ok(bret, "GetSecurityDescriptorDacl failed with error %d\n", GetLastError());
    ok(dacl_present, "DACL should be present\n");
    ok(pDacl && IsValidAcl(pDacl), "GetSecurityDescriptorDacl returned invalid DACL.\n");
    bret = pGetAclInformation(pDacl, &acl_size, sizeof(acl_size), AclSizeInformation);
    ok(bret, "GetAclInformation failed\n");
    ok(acl_size.AceCount != 0, "GetAclInformation returned no ACLs\n");
    for (i=0; i<acl_size.AceCount; i++)
    {
        bret = pGetAce(pDacl, i, (VOID **)&ace);
        ok(bret, "Failed to get ACE %d.\n", i);
        bret = EqualSid(&ace->SidStart, domain_users_sid);
        if (bret) domain_users_ace_id = i;
        bret = EqualSid(&ace->SidStart, admin_sid);
        if (bret) admins_ace_id = i;
    }
    ok(domain_users_ace_id != -1 || broken(domain_users_ace_id == -1) /* win2k */,
       "Domain Users ACE not found.\n");
    if (domain_users_ace_id != -1)
    {
        bret = pGetAce(pDacl, domain_users_ace_id, (VOID **)&ace);
        ok(bret, "Failed to get Domain Users ACE.\n");
        flags = ((ACE_HEADER *)ace)->AceFlags;
        ok(flags == (INHERIT_ONLY_ACE|CONTAINER_INHERIT_ACE),
           "Domain Users ACE has unexpected flags (0x%x != 0x%x)\n", flags,
           INHERIT_ONLY_ACE|CONTAINER_INHERIT_ACE);
        ok(ace->Mask == GENERIC_READ, "Domain Users ACE has unexpected mask (0x%x != 0x%x)\n",
                                      ace->Mask, GENERIC_READ);
    }
    ok(admins_ace_id != -1 || broken(admins_ace_id == -1) /* xp */,
       "Builtin Admins ACE not found.\n");
    if (admins_ace_id != -1)
    {
        bret = pGetAce(pDacl, admins_ace_id, (VOID **)&ace);
        ok(bret, "Failed to get Builtin Admins ACE.\n");
        flags = ((ACE_HEADER *)ace)->AceFlags;
        ok(flags == 0x0, "Builtin Admins ACE has unexpected flags (0x%x != 0x0)\n", flags);
        ok(ace->Mask == PROCESS_ALL_ACCESS || broken(ace->Mask == 0x1f0fff) /* win2k */,
           "Builtin Admins ACE has unexpected mask (0x%x != 0x%x)\n", ace->Mask, PROCESS_ALL_ACCESS);
    }
    LocalFree(pSD);
}