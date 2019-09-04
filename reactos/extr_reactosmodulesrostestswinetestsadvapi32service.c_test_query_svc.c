#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dwCurrentState; scalar_t__ dwProcessId; } ;
typedef  TYPE_1__ SERVICE_STATUS_PROCESS ;
typedef  int /*<<< orphan*/  SERVICE_STATUS ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int ERROR_ACCESS_DENIED ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_ADDRESS ; 
 int ERROR_INVALID_HANDLE ; 
 int ERROR_INVALID_LEVEL ; 
 int ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * OpenSCManagerA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenServiceA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int QueryServiceStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int SC_STATUS_PROCESS_INFO ; 
 int /*<<< orphan*/  SERVICE_QUERY_STATUS ; 
 scalar_t__ SERVICE_RUNNING ; 
 int /*<<< orphan*/  STANDARD_RIGHTS_READ ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pQueryServiceStatusEx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  spooler ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_query_svc(void)
{
    SC_HANDLE scm_handle, svc_handle;
    BOOL ret;
    SERVICE_STATUS status;
    SERVICE_STATUS_PROCESS *statusproc;
    DWORD bufsize, needed;

    /* All NULL or wrong  */
    SetLastError(0xdeadbeef);
    ret = QueryServiceStatus(NULL, NULL);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE,
       "Expected ERROR_INVALID_HANDLE, got %d\n", GetLastError());

    scm_handle = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT);

    /* Check if 'Spooler' exists.
     * Open with not enough rights to query the status.
     */
    svc_handle = OpenServiceA(scm_handle, spooler, STANDARD_RIGHTS_READ);
    if (!svc_handle)
    {
        skip("Spooler service doesn't exist\n");
        CloseServiceHandle(scm_handle);
        return;
    }

    SetLastError(0xdeadbeef);
    ret = QueryServiceStatus(svc_handle, NULL);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_ADDRESS ||
       GetLastError() == ERROR_INVALID_PARAMETER /* NT4 */,
       "Unexpected last error %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = QueryServiceStatus(svc_handle, &status);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_ACCESS_DENIED,
       "Expected ERROR_ACCESS_DENIED, got %d\n", GetLastError());

    /* Open the service with just enough rights.
     * (Verified with 'SERVICE_ALL_ACCESS &~ SERVICE_QUERY_STATUS')
     */
    CloseServiceHandle(svc_handle);
    svc_handle = OpenServiceA(scm_handle, spooler, SERVICE_QUERY_STATUS);

    SetLastError(0xdeadbeef);
    ret = QueryServiceStatus(svc_handle, &status);
    ok(ret, "Expected success, got error %u\n", GetLastError());

    CloseServiceHandle(svc_handle);

    /* More or less the same tests for QueryServiceStatusEx */
    if (!pQueryServiceStatusEx)
    {
        win_skip( "QueryServiceStatusEx not available\n" );
        CloseServiceHandle(scm_handle);
        return;
    }

    /* Open service with not enough rights to query the status */
    svc_handle = OpenServiceA(scm_handle, spooler, STANDARD_RIGHTS_READ);

    /* All NULL or wrong, this proves that info level is checked first */
    SetLastError(0xdeadbeef);
    ret = pQueryServiceStatusEx(NULL, 1, NULL, 0, NULL);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_LEVEL,
       "Expected ERROR_INVALID_LEVEL, got %d\n", GetLastError());

    /* Passing a NULL parameter for the needed buffer size
     * will crash on anything but NT4.
     */

    /* Only info level is correct. It looks like the buffer/size is checked second */
    SetLastError(0xdeadbeef);
    ret = pQueryServiceStatusEx(NULL, SC_STATUS_PROCESS_INFO, NULL, 0, &needed);
    /* NT4 checks the handle first */
    if (GetLastError() != ERROR_INVALID_HANDLE)
    {
        ok(!ret, "Expected failure\n");
        ok(needed == sizeof(SERVICE_STATUS_PROCESS),
           "Needed buffersize is wrong : %d\n", needed);
        ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
           "Expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());
    }

    /* Pass a correct buffer and buffersize but a NULL handle */
    statusproc = HeapAlloc(GetProcessHeap(), 0, sizeof(SERVICE_STATUS_PROCESS));
    bufsize = needed;
    SetLastError(0xdeadbeef);
    ret = pQueryServiceStatusEx(NULL, SC_STATUS_PROCESS_INFO, (BYTE*)statusproc, bufsize, &needed);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE,
       "Expected ERROR_INVALID_HANDLE, got %d\n", GetLastError());
    HeapFree(GetProcessHeap(), 0, statusproc);

    /* Correct handle and info level */
    SetLastError(0xdeadbeef);
    ret = pQueryServiceStatusEx(svc_handle, SC_STATUS_PROCESS_INFO, NULL, 0, &needed);
    /* NT4 doesn't return the needed size */
    if (GetLastError() != ERROR_INVALID_PARAMETER)
    {
        ok(!ret, "Expected failure\n");
        ok(needed == sizeof(SERVICE_STATUS_PROCESS),
           "Needed buffersize is wrong : %d\n", needed);
        ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
           "Expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());
    }

    /* All parameters are OK but we don't have enough rights */
    statusproc = HeapAlloc(GetProcessHeap(), 0, sizeof(SERVICE_STATUS_PROCESS));
    bufsize = sizeof(SERVICE_STATUS_PROCESS);
    SetLastError(0xdeadbeef);
    ret = pQueryServiceStatusEx(svc_handle, SC_STATUS_PROCESS_INFO, (BYTE*)statusproc, bufsize, &needed);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_ACCESS_DENIED,
       "Expected ERROR_ACCESS_DENIED, got %d\n", GetLastError());
    HeapFree(GetProcessHeap(), 0, statusproc);

    /* Open the service with just enough rights. */
    CloseServiceHandle(svc_handle);
    svc_handle = OpenServiceA(scm_handle, spooler, SERVICE_QUERY_STATUS);

    /* Everything should be fine now. */
    statusproc = HeapAlloc(GetProcessHeap(), 0, sizeof(SERVICE_STATUS_PROCESS));
    bufsize = sizeof(SERVICE_STATUS_PROCESS);
    SetLastError(0xdeadbeef);
    ret = pQueryServiceStatusEx(svc_handle, SC_STATUS_PROCESS_INFO, (BYTE*)statusproc, bufsize, &needed);
    ok(ret, "Expected success, got error %u\n", GetLastError());
    if (statusproc->dwCurrentState == SERVICE_RUNNING)
        ok(statusproc->dwProcessId != 0,
           "Expect a process id for this running service\n");
    else
        ok(statusproc->dwProcessId == 0,
           "Expect no process id for this stopped service\n");

    /* same call with null needed pointer */
    SetLastError(0xdeadbeef);
    ret = pQueryServiceStatusEx(svc_handle, SC_STATUS_PROCESS_INFO, (BYTE*)statusproc, bufsize, NULL);
    ok(!ret, "Expected failure\n");
    ok(broken(GetLastError() == ERROR_INVALID_PARAMETER) /* NT4 */ ||
       GetLastError() == ERROR_INVALID_ADDRESS, "got %d\n", GetLastError());

    HeapFree(GetProcessHeap(), 0, statusproc);

    CloseServiceHandle(svc_handle);
    CloseServiceHandle(scm_handle);
}