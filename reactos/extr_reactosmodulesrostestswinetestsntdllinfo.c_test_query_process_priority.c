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
typedef  int /*<<< orphan*/  priority ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {scalar_t__ PriorityClass; } ;
typedef  TYPE_1__ PROCESS_PRIORITY_CLASS ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BELOW_NORMAL_PRIORITY_CLASS ; 
 int /*<<< orphan*/ * GetCurrentProcess () ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetPriorityClass (int /*<<< orphan*/ *) ; 
 scalar_t__ PROCESS_PRIOCLASS_BELOW_NORMAL ; 
 int /*<<< orphan*/  ProcessPriorityClass ; 
 scalar_t__ STATUS_ACCESS_VIOLATION ; 
 scalar_t__ STATUS_INFO_LENGTH_MISMATCH ; 
 scalar_t__ STATUS_INVALID_HANDLE ; 
 scalar_t__ STATUS_SUCCESS ; 
 int SetPriorityClass (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pNtQueryInformationProcess (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_query_process_priority(void)
{
    PROCESS_PRIORITY_CLASS priority[2];
    ULONG ReturnLength;
    DWORD orig_priority;
    NTSTATUS status;
    BOOL ret;

    status = pNtQueryInformationProcess(NULL, ProcessPriorityClass, NULL, sizeof(priority[0]), NULL);
    ok(status == STATUS_ACCESS_VIOLATION || broken(status == STATUS_INVALID_HANDLE) /* w2k3 */,
       "Expected STATUS_ACCESS_VIOLATION, got %08x\n", status);

    status = pNtQueryInformationProcess(NULL, ProcessPriorityClass, &priority, sizeof(priority[0]), NULL);
    ok(status == STATUS_INVALID_HANDLE, "Expected STATUS_INVALID_HANDLE, got %08x\n", status);

    status = pNtQueryInformationProcess(GetCurrentProcess(), ProcessPriorityClass, &priority, 1, &ReturnLength);
    ok(status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got %08x\n", status);

    status = pNtQueryInformationProcess(GetCurrentProcess(), ProcessPriorityClass, &priority, sizeof(priority), &ReturnLength);
    ok(status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got %08x\n", status);

    orig_priority = GetPriorityClass(GetCurrentProcess());
    ret = SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);
    ok(ret, "Failed to set priority class: %u\n", GetLastError());

    status = pNtQueryInformationProcess(GetCurrentProcess(), ProcessPriorityClass, &priority, sizeof(priority[0]), &ReturnLength);
    ok(status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);
    ok(priority[0].PriorityClass == PROCESS_PRIOCLASS_BELOW_NORMAL,
       "Expected PROCESS_PRIOCLASS_BELOW_NORMAL, got %u\n", priority[0].PriorityClass);

    ret = SetPriorityClass(GetCurrentProcess(), orig_priority);
    ok(ret, "Failed to reset priority class: %u\n", GetLastError());
}