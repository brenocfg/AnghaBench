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
typedef  int /*<<< orphan*/  sid_buf ;
typedef  int /*<<< orphan*/  acl_buf ;
typedef  scalar_t__ ULONG ;
typedef  int SECURITY_INFORMATION ;
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  scalar_t__ PSID ;
typedef  int /*<<< orphan*/ * PACL ;
typedef  scalar_t__ LPSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_REVISION ; 
 int CONTAINER_INHERIT_ACE ; 
 int DACL_SECURITY_INFORMATION ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_GENERIC_READ ; 
 int FILE_GENERIC_WRITE ; 
 int GROUP_SECURITY_INFORMATION ; 
 int INHERITED_ACE ; 
 int INHERIT_ONLY_ACE ; 
 int /*<<< orphan*/  InitializeAcl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int NO_PROPAGATE_INHERIT_ACE ; 
 int OBJECT_INHERIT_ACE ; 
 int OWNER_SECURITY_INFORMATION ; 
 int SACL_SECURITY_INFORMATION ; 
 int /*<<< orphan*/  SDDL_REVISION_1 ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_REVISION ; 
 int /*<<< orphan*/  SetSecurityDescriptorDacl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSecurityDescriptorGroup (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSecurityDescriptorOwner (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSecurityDescriptorSacl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int VALID_INHERIT_FLAGS ; 
 int /*<<< orphan*/  WinLocalSid ; 
 int /*<<< orphan*/  WinLocalSystemSid ; 
 char* lstrlenA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pAddAccessAllowedAceEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  pAddAccessDeniedAceEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  pAddAuditAccessAceEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pConvertSecurityDescriptorToStringSecurityDescriptorA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  pConvertStringSidToSidA (char*,scalar_t__*) ; 
 int /*<<< orphan*/  pCreateWellKnownSid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_ConvertSecurityDescriptorToString(void)
{
    SECURITY_DESCRIPTOR desc;
    SECURITY_INFORMATION sec_info = OWNER_SECURITY_INFORMATION|GROUP_SECURITY_INFORMATION|DACL_SECURITY_INFORMATION|SACL_SECURITY_INFORMATION;
    LPSTR string;
    DWORD size;
    PSID psid, psid2;
    PACL pacl;
    char sid_buf[256];
    char acl_buf[8192];
    ULONG len;

    if (!pConvertSecurityDescriptorToStringSecurityDescriptorA)
    {
        win_skip("ConvertSecurityDescriptorToStringSecurityDescriptor is not available\n");
        return;
    }
    if (!pCreateWellKnownSid)
    {
        win_skip("CreateWellKnownSid is not available\n");
        return;
    }

/* It seems Windows XP adds an extra character to the length of the string for each ACE in an ACL. We
 * don't replicate this feature so we only test len >= strlen+1. */
#define CHECK_RESULT_AND_FREE(exp_str) \
    ok(strcmp(string, (exp_str)) == 0, "String mismatch (expected \"%s\", got \"%s\")\n", (exp_str), string); \
    ok(len >= (strlen(exp_str) + 1), "Length mismatch (expected %d, got %d)\n", lstrlenA(exp_str) + 1, len); \
    LocalFree(string);

#define CHECK_ONE_OF_AND_FREE(exp_str1, exp_str2) \
    ok(strcmp(string, (exp_str1)) == 0 || strcmp(string, (exp_str2)) == 0, "String mismatch (expected\n\"%s\" or\n\"%s\", got\n\"%s\")\n", (exp_str1), (exp_str2), string); \
    ok(len >= (strlen(exp_str1) + 1) || len >= (strlen(exp_str2) + 1), "Length mismatch (expected %d or %d, got %d)\n", lstrlenA(exp_str1) + 1, lstrlenA(exp_str2) + 1, len); \
    LocalFree(string);

    InitializeSecurityDescriptor(&desc, SECURITY_DESCRIPTOR_REVISION);
    ok(pConvertSecurityDescriptorToStringSecurityDescriptorA(&desc, SDDL_REVISION_1, sec_info, &string, &len), "Conversion failed\n");
    CHECK_RESULT_AND_FREE("");

    size = 4096;
    pCreateWellKnownSid(WinLocalSid, NULL, sid_buf, &size);
    SetSecurityDescriptorOwner(&desc, sid_buf, FALSE);
    ok(pConvertSecurityDescriptorToStringSecurityDescriptorA(&desc, SDDL_REVISION_1, sec_info, &string, &len), "Conversion failed\n");
    CHECK_RESULT_AND_FREE("O:S-1-2-0");

    SetSecurityDescriptorOwner(&desc, sid_buf, TRUE);
    ok(pConvertSecurityDescriptorToStringSecurityDescriptorA(&desc, SDDL_REVISION_1, sec_info, &string, &len), "Conversion failed\n");
    CHECK_RESULT_AND_FREE("O:S-1-2-0");

    size = sizeof(sid_buf);
    pCreateWellKnownSid(WinLocalSystemSid, NULL, sid_buf, &size);
    SetSecurityDescriptorOwner(&desc, sid_buf, TRUE);
    ok(pConvertSecurityDescriptorToStringSecurityDescriptorA(&desc, SDDL_REVISION_1, sec_info, &string, &len), "Conversion failed\n");
    CHECK_RESULT_AND_FREE("O:SY");

    pConvertStringSidToSidA("S-1-5-21-93476-23408-4576", &psid);
    SetSecurityDescriptorGroup(&desc, psid, TRUE);
    ok(pConvertSecurityDescriptorToStringSecurityDescriptorA(&desc, SDDL_REVISION_1, sec_info, &string, &len), "Conversion failed\n");
    CHECK_RESULT_AND_FREE("O:SYG:S-1-5-21-93476-23408-4576");

    ok(pConvertSecurityDescriptorToStringSecurityDescriptorA(&desc, SDDL_REVISION_1, GROUP_SECURITY_INFORMATION, &string, &len), "Conversion failed\n");
    CHECK_RESULT_AND_FREE("G:S-1-5-21-93476-23408-4576");

    pacl = (PACL)acl_buf;
    InitializeAcl(pacl, sizeof(acl_buf), ACL_REVISION);
    SetSecurityDescriptorDacl(&desc, TRUE, pacl, TRUE);
    ok(pConvertSecurityDescriptorToStringSecurityDescriptorA(&desc, SDDL_REVISION_1, sec_info, &string, &len), "Conversion failed\n");
    CHECK_RESULT_AND_FREE("O:SYG:S-1-5-21-93476-23408-4576D:");

    SetSecurityDescriptorDacl(&desc, TRUE, pacl, FALSE);
    ok(pConvertSecurityDescriptorToStringSecurityDescriptorA(&desc, SDDL_REVISION_1, sec_info, &string, &len), "Conversion failed\n");
    CHECK_RESULT_AND_FREE("O:SYG:S-1-5-21-93476-23408-4576D:");

    pConvertStringSidToSidA("S-1-5-6", &psid2);
    pAddAccessAllowedAceEx(pacl, ACL_REVISION, NO_PROPAGATE_INHERIT_ACE, 0xf0000000, psid2);
    ok(pConvertSecurityDescriptorToStringSecurityDescriptorA(&desc, SDDL_REVISION_1, sec_info, &string, &len), "Conversion failed\n");
    CHECK_RESULT_AND_FREE("O:SYG:S-1-5-21-93476-23408-4576D:(A;NP;GAGXGWGR;;;SU)");

    pAddAccessAllowedAceEx(pacl, ACL_REVISION, INHERIT_ONLY_ACE|INHERITED_ACE, 0x00000003, psid2);
    ok(pConvertSecurityDescriptorToStringSecurityDescriptorA(&desc, SDDL_REVISION_1, sec_info, &string, &len), "Conversion failed\n");
    CHECK_RESULT_AND_FREE("O:SYG:S-1-5-21-93476-23408-4576D:(A;NP;GAGXGWGR;;;SU)(A;IOID;CCDC;;;SU)");

    pAddAccessDeniedAceEx(pacl, ACL_REVISION, OBJECT_INHERIT_ACE|CONTAINER_INHERIT_ACE, 0xffffffff, psid);
    ok(pConvertSecurityDescriptorToStringSecurityDescriptorA(&desc, SDDL_REVISION_1, sec_info, &string, &len), "Conversion failed\n");
    CHECK_RESULT_AND_FREE("O:SYG:S-1-5-21-93476-23408-4576D:(A;NP;GAGXGWGR;;;SU)(A;IOID;CCDC;;;SU)(D;OICI;0xffffffff;;;S-1-5-21-93476-23408-4576)");


    pacl = (PACL)acl_buf;
    InitializeAcl(pacl, sizeof(acl_buf), ACL_REVISION);
    SetSecurityDescriptorSacl(&desc, TRUE, pacl, FALSE);
    ok(pConvertSecurityDescriptorToStringSecurityDescriptorA(&desc, SDDL_REVISION_1, sec_info, &string, &len), "Conversion failed\n");
    CHECK_RESULT_AND_FREE("O:SYG:S-1-5-21-93476-23408-4576D:S:");

    /* fails in win2k */
    SetSecurityDescriptorDacl(&desc, TRUE, NULL, FALSE);
    pAddAuditAccessAceEx(pacl, ACL_REVISION, VALID_INHERIT_FLAGS, KEY_READ|KEY_WRITE, psid2, TRUE, TRUE);
    if (pConvertSecurityDescriptorToStringSecurityDescriptorA(&desc, SDDL_REVISION_1, sec_info, &string, &len))
    {
        CHECK_ONE_OF_AND_FREE("O:SYG:S-1-5-21-93476-23408-4576D:S:(AU;OICINPIOIDSAFA;CCDCLCSWRPRC;;;SU)", /* XP */
            "O:SYG:S-1-5-21-93476-23408-4576D:NO_ACCESS_CONTROLS:(AU;OICINPIOIDSAFA;CCDCLCSWRPRC;;;SU)" /* Vista */);
    }

    /* fails in win2k */
    pAddAuditAccessAceEx(pacl, ACL_REVISION, NO_PROPAGATE_INHERIT_ACE, FILE_GENERIC_READ|FILE_GENERIC_WRITE, psid2, TRUE, FALSE);
    if (pConvertSecurityDescriptorToStringSecurityDescriptorA(&desc, SDDL_REVISION_1, sec_info, &string, &len))
    {
        CHECK_ONE_OF_AND_FREE("O:SYG:S-1-5-21-93476-23408-4576D:S:(AU;OICINPIOIDSAFA;CCDCLCSWRPRC;;;SU)(AU;NPSA;0x12019f;;;SU)", /* XP */
            "O:SYG:S-1-5-21-93476-23408-4576D:NO_ACCESS_CONTROLS:(AU;OICINPIOIDSAFA;CCDCLCSWRPRC;;;SU)(AU;NPSA;0x12019f;;;SU)" /* Vista */);
    }

    LocalFree(psid2);
    LocalFree(psid);
}