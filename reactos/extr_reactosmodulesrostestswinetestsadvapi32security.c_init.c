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
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hmod ; 
 int /*<<< orphan*/  myARGC ; 
 int /*<<< orphan*/  myARGV ; 
 void* pAddAccessAllowedAceEx ; 
 void* pAddAccessDeniedAceEx ; 
 void* pAddAuditAccessAceEx ; 
 void* pAddMandatoryAce ; 
 void* pCheckTokenMembership ; 
 void* pConvertSecurityDescriptorToStringSecurityDescriptorA ; 
 void* pConvertStringSecurityDescriptorToSecurityDescriptorA ; 
 void* pConvertStringSecurityDescriptorToSecurityDescriptorW ; 
 void* pConvertStringSidToSidA ; 
 void* pCreateRestrictedToken ; 
 void* pCreateWellKnownSid ; 
 void* pDuplicateTokenEx ; 
 void* pGetAce ; 
 void* pGetAclInformation ; 
 void* pGetExplicitEntriesFromAclW ; 
 void* pGetFileSecurityA ; 
 void* pGetNamedSecurityInfoA ; 
 void* pGetSecurityInfo ; 
 void* pGetSidIdentifierAuthority ; 
 void* pGetSidSubAuthority ; 
 void* pGetSidSubAuthorityCount ; 
 void* pGetWindowsAccountDomainSid ; 
 void* pIsValidSid ; 
 void* pMakeSelfRelativeSD ; 
 void* pNtAccessCheck ; 
 void* pNtCreateFile ; 
 void* pNtQueryObject ; 
 void* pNtSetSecurityObject ; 
 void* pRtlAnsiStringToUnicodeString ; 
 void* pRtlDosPathNameToNtPathName_U ; 
 void* pRtlFreeUnicodeString ; 
 void* pRtlInitAnsiString ; 
 void* pSetEntriesInAclA ; 
 void* pSetEntriesInAclW ; 
 void* pSetFileSecurityA ; 
 void* pSetNamedSecurityInfoA ; 
 void* pSetSecurityDescriptorControl ; 
 void* pSetSecurityInfo ; 
 int /*<<< orphan*/  winetest_get_mainargs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init(void)
{
    HMODULE hntdll;

    hntdll = GetModuleHandleA("ntdll.dll");
    pNtQueryObject = (void *)GetProcAddress( hntdll, "NtQueryObject" );
    pNtAccessCheck = (void *)GetProcAddress( hntdll, "NtAccessCheck" );
    pNtSetSecurityObject = (void *)GetProcAddress(hntdll, "NtSetSecurityObject");
    pNtCreateFile = (void *)GetProcAddress(hntdll, "NtCreateFile");
    pRtlDosPathNameToNtPathName_U = (void *)GetProcAddress(hntdll, "RtlDosPathNameToNtPathName_U");
    pRtlAnsiStringToUnicodeString = (void *)GetProcAddress(hntdll, "RtlAnsiStringToUnicodeString");
    pRtlInitAnsiString = (void *)GetProcAddress(hntdll, "RtlInitAnsiString");
    pRtlFreeUnicodeString = (void *)GetProcAddress(hntdll, "RtlFreeUnicodeString");

    hmod = GetModuleHandleA("advapi32.dll");
    pAddAccessAllowedAceEx = (void *)GetProcAddress(hmod, "AddAccessAllowedAceEx");
    pAddAccessDeniedAceEx = (void *)GetProcAddress(hmod, "AddAccessDeniedAceEx");
    pAddAuditAccessAceEx = (void *)GetProcAddress(hmod, "AddAuditAccessAceEx");
    pAddMandatoryAce = (void *)GetProcAddress(hmod, "AddMandatoryAce");
    pCheckTokenMembership = (void *)GetProcAddress(hmod, "CheckTokenMembership");
    pConvertStringSecurityDescriptorToSecurityDescriptorA =
        (void *)GetProcAddress(hmod, "ConvertStringSecurityDescriptorToSecurityDescriptorA" );
    pConvertStringSecurityDescriptorToSecurityDescriptorW =
        (void *)GetProcAddress(hmod, "ConvertStringSecurityDescriptorToSecurityDescriptorW" );
    pConvertSecurityDescriptorToStringSecurityDescriptorA =
        (void *)GetProcAddress(hmod, "ConvertSecurityDescriptorToStringSecurityDescriptorA" );
    pGetFileSecurityA = (void *)GetProcAddress(hmod, "GetFileSecurityA" );
    pSetFileSecurityA = (void *)GetProcAddress(hmod, "SetFileSecurityA" );
    pCreateWellKnownSid = (void *)GetProcAddress( hmod, "CreateWellKnownSid" );
    pGetNamedSecurityInfoA = (void *)GetProcAddress(hmod, "GetNamedSecurityInfoA");
    pSetNamedSecurityInfoA = (void *)GetProcAddress(hmod, "SetNamedSecurityInfoA");
    pGetSidSubAuthority = (void *)GetProcAddress(hmod, "GetSidSubAuthority");
    pGetSidSubAuthorityCount = (void *)GetProcAddress(hmod, "GetSidSubAuthorityCount");
    pIsValidSid = (void *)GetProcAddress(hmod, "IsValidSid");
    pMakeSelfRelativeSD = (void *)GetProcAddress(hmod, "MakeSelfRelativeSD");
    pSetEntriesInAclW = (void *)GetProcAddress(hmod, "SetEntriesInAclW");
    pSetEntriesInAclA = (void *)GetProcAddress(hmod, "SetEntriesInAclA");
    pSetSecurityDescriptorControl = (void *)GetProcAddress(hmod, "SetSecurityDescriptorControl");
    pGetSecurityInfo = (void *)GetProcAddress(hmod, "GetSecurityInfo");
    pSetSecurityInfo = (void *)GetProcAddress(hmod, "SetSecurityInfo");
    pCreateRestrictedToken = (void *)GetProcAddress(hmod, "CreateRestrictedToken");
    pConvertStringSidToSidA = (void *)GetProcAddress(hmod, "ConvertStringSidToSidA");
    pGetAclInformation = (void *)GetProcAddress(hmod, "GetAclInformation");
    pGetAce = (void *)GetProcAddress(hmod, "GetAce");
    pGetWindowsAccountDomainSid = (void *)GetProcAddress(hmod, "GetWindowsAccountDomainSid");
    pGetSidIdentifierAuthority = (void *)GetProcAddress(hmod, "GetSidIdentifierAuthority");
    pDuplicateTokenEx = (void *)GetProcAddress(hmod, "DuplicateTokenEx");
    pGetExplicitEntriesFromAclW = (void *)GetProcAddress(hmod, "GetExplicitEntriesFromAclW");

    myARGC = winetest_get_mainargs( &myARGV );
}