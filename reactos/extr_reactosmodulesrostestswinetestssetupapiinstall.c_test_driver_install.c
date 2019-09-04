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
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 char* CURR_DIR ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DELETE ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  DeleteService (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_ALL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ GetFileAttributesA (char*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetWindowsDirectoryA (char*,int) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * OpenSCManagerA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenServiceA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  create_inf_file (char*,char const*) ; 
 char* inffile ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  run_cmdline (char*,int,char*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static void test_driver_install(void)
{
    HANDLE handle;
    SC_HANDLE scm_handle, svc_handle;
    BOOL ret;
    char path[MAX_PATH], windir[MAX_PATH], driver[MAX_PATH];
    DWORD attrs;
    /* Minimal stuff needed */
    static const char *inf =
        "[Version]\n"
        "Signature=\"$Chicago$\"\n"
        "[DestinationDirs]\n"
        "Winetest.DriverFiles=12\n"
        "[DefaultInstall]\n"
        "CopyFiles=Winetest.DriverFiles\n"
        "[DefaultInstall.Services]\n"
        "AddService=Winetest,,Winetest.Service\n"
        "[Winetest.Service]\n"
        "ServiceBinary=%12%\\winetest.sys\n"
        "ServiceType=1\n"
        "StartType=4\n"
        "ErrorControl=1\n"
        "[Winetest.DriverFiles]\n"
        "winetest.sys";

    /* Bail out if we don't have enough rights */
    SetLastError(0xdeadbeef);
    scm_handle = OpenSCManagerA(NULL, NULL, GENERIC_ALL);
    if (!scm_handle && (GetLastError() == ERROR_ACCESS_DENIED))
    {
        skip("Not enough rights to install the service\n");
        return;
    }
    CloseServiceHandle(scm_handle);

    /* Place where we expect the driver to be installed */
    GetWindowsDirectoryA(windir, MAX_PATH);
    lstrcpyA(driver, windir);
    lstrcatA(driver, "\\system32\\drivers\\winetest.sys");

    /* Create a dummy driver file */
    handle = CreateFileA("winetest.sys", GENERIC_WRITE, 0, NULL,
                           CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    CloseHandle(handle);

    create_inf_file(inffile, inf);
    sprintf(path, "%s\\%s", CURR_DIR, inffile);
    run_cmdline("DefaultInstall", 128, path);

    /* Driver should have been installed */
    attrs = GetFileAttributesA(driver);
    ok(attrs != INVALID_FILE_ATTRIBUTES, "Expected driver to exist\n");

    scm_handle = OpenSCManagerA(NULL, NULL, GENERIC_ALL);

    /* Open the service to see if it's really there */
    svc_handle = OpenServiceA(scm_handle, "Winetest", DELETE);
    ok(svc_handle != NULL, "Service was not created\n");

    SetLastError(0xdeadbeef);
    ret = DeleteService(svc_handle);
    ok(ret, "Service could not be deleted : %d\n", GetLastError());

    CloseServiceHandle(svc_handle);
    CloseServiceHandle(scm_handle);

    /* File cleanup */
    DeleteFileA(inffile);
    DeleteFileA("winetest.sys");
    DeleteFileA(driver);
}