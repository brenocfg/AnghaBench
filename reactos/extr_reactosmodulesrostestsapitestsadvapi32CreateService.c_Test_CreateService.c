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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateServiceW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DELETE ; 
 int /*<<< orphan*/  DNS_ERROR_RCODE_NXRRSET ; 
 int /*<<< orphan*/  DestroyService (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ MakeService (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/ * OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_CREATE_SERVICE ; 
 int /*<<< orphan*/  SERVICE_BOOT_START ; 
 int /*<<< orphan*/  SERVICE_ERROR_IGNORE ; 
 int /*<<< orphan*/  SERVICE_KERNEL_DRIVER ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  ok_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void Test_CreateService(void)
{
    SC_HANDLE hScm = NULL;
    SC_HANDLE hService1 = NULL, hService2 = NULL;
    SC_HANDLE hService3 = NULL;
    DWORD tag1 = 0, tag2 = 0;
    DWORD tag3 = 785;

    SetLastError(DNS_ERROR_RCODE_NXRRSET);
    hScm = OpenSCManagerW(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    ok(hScm != NULL, "Failed to open service manager, error=0x%08lx\n", GetLastError());
    if (!hScm)
    {
        skip("No service control manager; cannot proceed with CreateService test\n");
        goto cleanup;
    }

    ok_err(ERROR_SUCCESS);

    if (MakeService(hScm, L"advapi32_apitest_CreateService_Test_Service1", &hService1, &tag1))
        goto cleanup;

    if (MakeService(hScm, L"advapi32_apitest_CreateService_Test_Service2", &hService2, &tag2))
        goto cleanup;

    ok(tag1 != tag2, "tag1=%lu, tag2=%lu\n", tag1, tag2);

    /* ask for a tag, but don't have a group */
    hService3 = CreateServiceW(
                    hScm,
                    L"advapi32_apitest_CreateService_Test_Service2",
                    NULL,
                    DELETE,
                    SERVICE_KERNEL_DRIVER,
                    SERVICE_BOOT_START,
                    SERVICE_ERROR_IGNORE,
                    L"%systemroot%\\drivers\\win32k.sys",
                    NULL,
                    &tag3,
                    NULL,
                    NULL,
                    NULL);
    ok(hService3 == NULL, "hService3=%p\n", hService3);
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "error=%lu\n", GetLastError());
    ok(tag3 == 785, "tag3=%lu\n", tag3);
    DestroyService(hService3);

    hService3 = CreateServiceW(
                    hScm,
                    L"advapi32_apitest_CreateService_Test_Service2",
                    NULL,
                    DELETE,
                    SERVICE_KERNEL_DRIVER,
                    SERVICE_BOOT_START,
                    SERVICE_ERROR_IGNORE,
                    L"%systemroot%\\drivers\\win32k.sys",
                    L"",
                    &tag3,
                    NULL,
                    NULL,
                    NULL);
    ok(hService3 == NULL, "hService3=%p\n", hService3);
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "error=%lu\n", GetLastError());
    ok(tag3 == 785, "tag3=%lu\n", tag3);
    DestroyService(hService3);

cleanup:

    DestroyService(hService2);
    DestroyService(hService1);

    if (hScm)
        CloseServiceHandle(hScm);
}