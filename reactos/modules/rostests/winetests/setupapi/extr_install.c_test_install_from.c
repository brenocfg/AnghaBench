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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  HINF ;
typedef  int BOOL ;

/* Variables and functions */
 char* CURR_DIR ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  INF_STYLE_WIN4 ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPINST_REGISTRY ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SetupCloseInfFile (int /*<<< orphan*/ ) ; 
 int SetupInstallFromInfSectionA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupOpenInfFileA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmdline_inf_reg ; 
 int /*<<< orphan*/  create_inf_file (char*,int /*<<< orphan*/ ) ; 
 char* inffile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static void test_install_from(void)
{
    char path[MAX_PATH];
    HINF infhandle;
    HKEY key;
    LONG res;
    BOOL ret;

    /* First create a registry structure we would like to be deleted */
    ok(!RegCreateKeyA(HKEY_CURRENT_USER, "Software\\Wine\\setupapitest\\setupapitest", &key),
        "Expected RegCreateKeyA to succeed\n");

    /* Doublecheck if the registry key is present */
    ok(!RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Wine\\setupapitest\\setupapitest", &key),
        "Expected registry key to exist\n");

    create_inf_file(inffile, cmdline_inf_reg);
    sprintf(path, "%s\\%s", CURR_DIR, inffile);
    infhandle = SetupOpenInfFileA(path, NULL, INF_STYLE_WIN4, NULL);
    SetLastError(0xdeadbeef);
    ret = SetupInstallFromInfSectionA(NULL, infhandle, "DefaultInstall", SPINST_REGISTRY, key,
        "A:\\", 0, NULL, NULL, NULL, NULL);
    ok(ret, "Unexpected failure\n");
    ok(GetLastError() == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %08x\n", GetLastError());

    /* Check if the registry key is recursively deleted */
    res = RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Wine\\setupapitest", &key);
    ok(res == ERROR_FILE_NOT_FOUND, "Didn't expect the registry key to exist\n");
    /* Just in case */
    if (res == ERROR_SUCCESS)
    {
        RegDeleteKeyA(HKEY_CURRENT_USER, "Software\\Wine\\setupapitest\\setupapitest");
        RegDeleteKeyA(HKEY_CURRENT_USER, "Software\\Wine\\setupapitest");
    }

    SetupCloseInfFile(infhandle);
    DeleteFileA(inffile);
}