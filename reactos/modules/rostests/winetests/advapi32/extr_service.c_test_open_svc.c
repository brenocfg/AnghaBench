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
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_INVALID_ADDRESS ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SERVICE_DOES_NOT_EXIST ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetServiceDisplayNameA (int /*<<< orphan*/ *,char*,char*,scalar_t__*) ; 
 int /*<<< orphan*/ * OpenSCManagerA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenServiceA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcmpiA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 char* spooler ; 

__attribute__((used)) static void test_open_svc(void)
{
    SC_HANDLE scm_handle, svc_handle;
    CHAR displayname[4096];
    DWORD displaysize;

    /* All NULL (invalid access rights) */
    SetLastError(0xdeadbeef);
    svc_handle = OpenServiceA(NULL, NULL, 0);
    ok(!svc_handle, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE, "Expected ERROR_INVALID_HANDLE, got %d\n", GetLastError());

    /* TODO: Add some tests with invalid handles. These produce errors on Windows but crash on Wine */

    /* NULL service */
    scm_handle = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT);
    SetLastError(0xdeadbeef);
    svc_handle = OpenServiceA(scm_handle, NULL, GENERIC_READ);
    ok(!svc_handle, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_ADDRESS   /* W2K, XP, W2K3, Vista */ ||
       GetLastError() == ERROR_INVALID_PARAMETER /* NT4 */,
       "Expected ERROR_INVALID_ADDRESS or ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    CloseServiceHandle(scm_handle);

    /* Nonexistent service */
    scm_handle = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT);
    SetLastError(0xdeadbeef);
    svc_handle = OpenServiceA(scm_handle, "deadbeef", GENERIC_READ);
    ok(!svc_handle, "Expected failure\n");
    ok(GetLastError() == ERROR_SERVICE_DOES_NOT_EXIST, "Expected ERROR_SERVICE_DOES_NOT_EXIST, got %d\n", GetLastError());
    CloseServiceHandle(scm_handle);

    /* Proper SCM handle but different access rights */
    scm_handle = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT);
    SetLastError(0xdeadbeef);
    svc_handle = OpenServiceA(scm_handle, spooler, GENERIC_WRITE);
    if (!svc_handle && (GetLastError() == ERROR_ACCESS_DENIED))
        skip("Not enough rights to get a handle to the service\n");
    else
    {
        ok(svc_handle != NULL, "Expected success, got error %u\n", GetLastError());
        CloseServiceHandle(svc_handle);
    }

    /* Test to show we can't open a service with the displayname */

    /* Retrieve the needed size for the buffer */
    displaysize = 0;
    GetServiceDisplayNameA(scm_handle, spooler, NULL, &displaysize);
    /* Get the displayname */
    GetServiceDisplayNameA(scm_handle, spooler, displayname, &displaysize);
    /* Try to open the service with this displayname, unless the displayname equals
     * the servicename as that would defeat the purpose of this test.
     */
    if (!lstrcmpiA(spooler, displayname))
    {
        skip("displayname equals servicename\n");
        CloseServiceHandle(scm_handle);
        return;
    }

    SetLastError(0xdeadbeef);
    svc_handle = OpenServiceA(scm_handle, displayname, GENERIC_READ);
    ok(!svc_handle, "Expected failure\n");
    ok(GetLastError() == ERROR_SERVICE_DOES_NOT_EXIST, "Expected ERROR_SERVICE_DOES_NOT_EXIST, got %d\n", GetLastError());
    /* Just in case */
    CloseServiceHandle(svc_handle);

    CloseServiceHandle(scm_handle);
}