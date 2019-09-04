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

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_COMMON_PROGRAMS ; 
 char* CURR_DIR ; 
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ GetFileAttributesA (char*) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 int /*<<< orphan*/  SHGFP_TYPE_CURRENT ; 
 scalar_t__ SHGetFolderPathA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  create_inf_file (char*,char const*) ; 
 char* inffile ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  run_cmdline (char*,int,char*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static void test_profile_items(void)
{
    char path[MAX_PATH], commonprogs[MAX_PATH];

    static const char *inf =
        "[Version]\n"
        "Signature=\"$Chicago$\"\n"
        "[DefaultInstall]\n"
        "ProfileItems=TestItem,TestItem2,TestGroup\n"
        "[TestItem]\n"
        "Name=TestItem\n"
        "CmdLine=11,,notepad.exe\n"
        "[TestItem2]\n"
        "Name=TestItem2\n"
        "CmdLine=11,,notepad.exe\n"
        "SubDir=TestDir\n"
        "[TestGroup]\n"
        "Name=TestGroup,4\n"
        ;

    if (S_OK != SHGetFolderPathA(NULL, CSIDL_COMMON_PROGRAMS, NULL, SHGFP_TYPE_CURRENT, commonprogs))
    {
        skip("No common program files directory exists\n");
        goto cleanup;
    }

    snprintf(path, MAX_PATH, "%s\\TestDir", commonprogs);
    if (!CreateDirectoryA(path, NULL) && GetLastError() == ERROR_ACCESS_DENIED)
    {
        skip("need admin rights\n");
        return;
    }
    RemoveDirectoryA(path);

    create_inf_file(inffile, inf);
    sprintf(path, "%s\\%s", CURR_DIR, inffile);
    run_cmdline("DefaultInstall", 128, path);

    snprintf(path, MAX_PATH, "%s\\TestItem.lnk", commonprogs);
    snprintf(path, MAX_PATH, "%s\\TestDir", commonprogs);
    ok(INVALID_FILE_ATTRIBUTES != GetFileAttributesA(path), "directory not created\n");
    snprintf(path, MAX_PATH, "%s\\TestDir\\TestItem2.lnk", commonprogs);
    ok(INVALID_FILE_ATTRIBUTES != GetFileAttributesA(path), "link not created\n");
    snprintf(path, MAX_PATH, "%s\\TestGroup", commonprogs);
    ok(INVALID_FILE_ATTRIBUTES != GetFileAttributesA(path), "group not created\n");

    snprintf(path, MAX_PATH, "%s\\TestItem.lnk", commonprogs);
    DeleteFileA(path);
    snprintf(path, MAX_PATH, "%s\\TestDir\\TestItem2.lnk", commonprogs);
    DeleteFileA(path);
    snprintf(path, MAX_PATH, "%s\\TestItem2.lnk", commonprogs);
    DeleteFileA(path);
    snprintf(path, MAX_PATH, "%s\\TestDir", commonprogs);
    RemoveDirectoryA(path);
    snprintf(path, MAX_PATH, "%s\\TestGroup", commonprogs);
    RemoveDirectoryA(path);

cleanup:
    DeleteFileA(inffile);
}