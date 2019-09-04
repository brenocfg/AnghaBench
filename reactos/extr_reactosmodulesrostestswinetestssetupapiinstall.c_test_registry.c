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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 char* CURR_DIR ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmdline_inf_reg ; 
 int /*<<< orphan*/  create_inf_file (char*,int /*<<< orphan*/ ) ; 
 char* inffile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  run_cmdline (char*,int,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static void test_registry(void)
{
    HKEY key;
    LONG res;
    char path[MAX_PATH];
    BOOL ret;

    /* First create a registry structure we would like to be deleted */
    ok(!RegCreateKeyA(HKEY_CURRENT_USER, "Software\\Wine\\setupapitest\\setupapitest", &key),
        "Expected RegCreateKeyA to succeed\n");

    /* Doublecheck if the registry key is present */
    ok(!RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Wine\\setupapitest\\setupapitest", &key),
        "Expected registry key to exist\n");

    create_inf_file(inffile, cmdline_inf_reg);
    sprintf(path, "%s\\%s", CURR_DIR, inffile);
    run_cmdline("DefaultInstall", 128, path);

    /* Check if the registry key is recursively deleted */
    res = RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Wine\\setupapitest", &key);
    ok(res == ERROR_FILE_NOT_FOUND, "Didn't expect the registry key to exist\n");
    /* Just in case */
    if (res == ERROR_SUCCESS)
    {
        RegDeleteKeyA(HKEY_CURRENT_USER, "Software\\Wine\\setupapitest\\setupapitest");
        RegDeleteKeyA(HKEY_CURRENT_USER, "Software\\Wine\\setupapitest");
    }
    ret = DeleteFileA(inffile);
    ok(ret, "Expected source inf to exist, last error was %d\n", GetLastError());
}