#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lpStruct ;
typedef  int /*<<< orphan*/  attributes ;
struct TYPE_3__ {int nLength; int /*<<< orphan*/  lpSecurityDescriptor; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SECURITY_ATTRIBUTES ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ConvertStringSecurityDescriptorToSecurityDescriptorA (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateDirectoryA (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetTempPathA (int,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 scalar_t__ RemoveDirectoryA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDDL_REVISION_1 ; 
 scalar_t__ TRUE ; 
 scalar_t__ WritePrivateProfileSectionA (char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ WritePrivateProfileStringA (char*,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ WritePrivateProfileStructA (char*,char*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcatA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_profile_directory_readonly(void)
{
    BOOL ret;
    CHAR path_folder[MAX_PATH];
    CHAR path_file[MAX_PATH];
    const char *sddl_string_everyone_readonly = "D:PAI(A;;0x1200a9;;;WD)";
    SECURITY_ATTRIBUTES attributes = {0};
    char lpStruct[] = { 's', 't', 'r', 'i', 'n', 'g' };

    attributes.nLength = sizeof(attributes);
    ret = ConvertStringSecurityDescriptorToSecurityDescriptorA(sddl_string_everyone_readonly, SDDL_REVISION_1, &attributes.lpSecurityDescriptor, NULL);
    ok(ret == TRUE, "ConvertStringSecurityDescriptorToSecurityDescriptor failed: %d\n", GetLastError());

    GetTempPathA(MAX_PATH, path_folder);
    lstrcatA(path_folder, "wine-test");

    strcpy(path_file, path_folder);
    lstrcatA(path_file, "\\tmp.ini");

    ret = CreateDirectoryA(path_folder, &attributes);
    ok(ret == TRUE, "CreateDirectoryA failed: %d\n", GetLastError());

    ret = WritePrivateProfileStringA("App", "key", "string", path_file);
    ok(ret == FALSE, "Expected FALSE, got %d\n", ret);

    ret = WritePrivateProfileSectionA("App", "key=string", path_file);
    ok(ret == FALSE, "Expected FALSE, got %d\n", ret);

    ret = WritePrivateProfileStructA("App", "key", lpStruct, sizeof(lpStruct), path_file);
    ok(ret == FALSE, "Expected FALSE, got %d\n", ret);

    ret = RemoveDirectoryA(path_folder);
    ok(ret == TRUE, "RemoveDirectoryA failed: %d\n", GetLastError());
}