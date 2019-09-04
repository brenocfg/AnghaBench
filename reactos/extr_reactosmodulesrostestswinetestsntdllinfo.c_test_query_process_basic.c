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
typedef  int /*<<< orphan*/  pbi ;
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PPEB ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/ * GetCurrentProcess () ; 
 int ProcessBasicInformation ; 
 int /*<<< orphan*/  STATUS_ACCESS_VIOLATION ; 
 int /*<<< orphan*/  STATUS_INFO_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  STATUS_INVALID_HANDLE ; 
 int /*<<< orphan*/  STATUS_INVALID_INFO_CLASS ; 
 int /*<<< orphan*/  STATUS_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pNtQueryInformationProcess (int /*<<< orphan*/ *,int,struct _PROCESS_BASIC_INFORMATION_PRIVATE*,int,int*) ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void test_query_process_basic(void)
{
    NTSTATUS status;
    ULONG ReturnLength;

    typedef struct _PROCESS_BASIC_INFORMATION_PRIVATE {
        DWORD_PTR ExitStatus;
        PPEB      PebBaseAddress;
        DWORD_PTR AffinityMask;
        DWORD_PTR BasePriority;
        ULONG_PTR UniqueProcessId;
        ULONG_PTR InheritedFromUniqueProcessId;
    } PROCESS_BASIC_INFORMATION_PRIVATE;

    PROCESS_BASIC_INFORMATION_PRIVATE pbi;

    /* This test also covers some basic parameter testing that should be the same for
     * every information class
    */

    /* Use a nonexistent info class */
    trace("Check nonexistent info class\n");
    status = pNtQueryInformationProcess(NULL, -1, NULL, 0, NULL);
    ok( status == STATUS_INVALID_INFO_CLASS || status == STATUS_NOT_IMPLEMENTED /* vista */,
        "Expected STATUS_INVALID_INFO_CLASS or STATUS_NOT_IMPLEMENTED, got %08x\n", status);

    /* Do not give a handle and buffer */
    trace("Check NULL handle and buffer and zero-length buffersize\n");
    status = pNtQueryInformationProcess(NULL, ProcessBasicInformation, NULL, 0, NULL);
    ok( status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got %08x\n", status);

    /* Use a correct info class and buffer size, but still no handle and buffer */
    trace("Check NULL handle and buffer\n");
    status = pNtQueryInformationProcess(NULL, ProcessBasicInformation, NULL, sizeof(pbi), NULL);
    ok( status == STATUS_ACCESS_VIOLATION || status == STATUS_INVALID_HANDLE,
        "Expected STATUS_ACCESS_VIOLATION or STATUS_INVALID_HANDLE(W2K3), got %08x\n", status);

    /* Use a correct info class and buffer size, but still no handle */
    trace("Check NULL handle\n");
    status = pNtQueryInformationProcess(NULL, ProcessBasicInformation, &pbi, sizeof(pbi), NULL);
    ok( status == STATUS_INVALID_HANDLE, "Expected STATUS_INVALID_HANDLE, got %08x\n", status);

    /* Use a greater buffer size */
    trace("Check NULL handle and too large buffersize\n");
    status = pNtQueryInformationProcess(NULL, ProcessBasicInformation, &pbi, sizeof(pbi) * 2, NULL);
    ok( status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got %08x\n", status);

    /* Use no ReturnLength */
    trace("Check NULL ReturnLength\n");
    status = pNtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, &pbi, sizeof(pbi), NULL);
    ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);

    /* Finally some correct calls */
    trace("Check with correct parameters\n");
    status = pNtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, &pbi, sizeof(pbi), &ReturnLength);
    ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);
    ok( sizeof(pbi) == ReturnLength, "Inconsistent length %d\n", ReturnLength);

    /* Everything is correct except a too large buffersize */
    trace("Too large buffersize\n");
    status = pNtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, &pbi, sizeof(pbi) * 2, &ReturnLength);
    ok( status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got %08x\n", status);
    ok( sizeof(pbi) == ReturnLength, "Inconsistent length %d\n", ReturnLength);
                                                                                                                                               
    /* Check if we have some return values */
    trace("ProcessID : %lx\n", pbi.UniqueProcessId);
    ok( pbi.UniqueProcessId > 0, "Expected a ProcessID > 0, got 0\n");
}