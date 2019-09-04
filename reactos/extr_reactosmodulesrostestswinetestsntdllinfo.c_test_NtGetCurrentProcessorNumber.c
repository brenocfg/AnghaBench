#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tbi ;
typedef  int /*<<< orphan*/  pbi ;
typedef  int /*<<< orphan*/  old_thread_mask ;
typedef  int /*<<< orphan*/  old_process_mask ;
typedef  int /*<<< orphan*/  new_mask ;
typedef  int ULONG ;
struct TYPE_9__ {int AffinityMask; } ;
struct TYPE_8__ {int dwNumberOfProcessors; } ;
struct TYPE_7__ {int AffinityMask; } ;
typedef  TYPE_1__ THREAD_BASIC_INFORMATION ;
typedef  TYPE_2__ SYSTEM_INFO ;
typedef  TYPE_3__ PROCESS_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetCurrentThread () ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  ProcessAffinityMask ; 
 int /*<<< orphan*/  ProcessBasicInformation ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  ThreadAffinityMask ; 
 int /*<<< orphan*/  ThreadBasicInformation ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pNtGetCurrentProcessorNumber () ; 
 int /*<<< orphan*/  pNtQueryInformationProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pNtQueryInformationThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pNtSetInformationProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pNtSetInformationThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  trace (char*,int,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_NtGetCurrentProcessorNumber(void)
{
    NTSTATUS status;
    SYSTEM_INFO si;
    PROCESS_BASIC_INFORMATION pbi;
    THREAD_BASIC_INFORMATION tbi;
    DWORD_PTR old_process_mask;
    DWORD_PTR old_thread_mask;
    DWORD_PTR new_mask;
    ULONG current_cpu;
    ULONG i;

    if (!pNtGetCurrentProcessorNumber) {
        win_skip("NtGetCurrentProcessorNumber not available\n");
        return;
    }

    GetSystemInfo(&si);
    current_cpu = pNtGetCurrentProcessorNumber();
    trace("dwNumberOfProcessors: %d, current processor: %d\n", si.dwNumberOfProcessors, current_cpu);

    status = pNtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, &pbi, sizeof(pbi), NULL);
    old_process_mask = pbi.AffinityMask;
    ok(status == STATUS_SUCCESS, "got 0x%x (expected STATUS_SUCCESS)\n", status);

    status = pNtQueryInformationThread(GetCurrentThread(), ThreadBasicInformation, &tbi, sizeof(tbi), NULL);
    old_thread_mask = tbi.AffinityMask;
    ok(status == STATUS_SUCCESS, "got 0x%x (expected STATUS_SUCCESS)\n", status);

    /* allow the test to run on all processors */
    new_mask = (1 << si.dwNumberOfProcessors) - 1;
    status = pNtSetInformationProcess(GetCurrentProcess(), ProcessAffinityMask, &new_mask, sizeof(new_mask));
    ok(status == STATUS_SUCCESS, "got 0x%x (expected STATUS_SUCCESS)\n", status);

    for (i = 0; i < si.dwNumberOfProcessors; i++)
    {
        new_mask = 1 << i;
        status = pNtSetInformationThread(GetCurrentThread(), ThreadAffinityMask, &new_mask, sizeof(new_mask));
        ok(status == STATUS_SUCCESS, "%d: got 0x%x (expected STATUS_SUCCESS)\n", i, status);

        status = pNtQueryInformationThread(GetCurrentThread(), ThreadBasicInformation, &tbi, sizeof(tbi), NULL);
        ok(status == STATUS_SUCCESS, "%d: got 0x%x (expected STATUS_SUCCESS)\n", i, status);

        current_cpu = pNtGetCurrentProcessorNumber();
        ok((current_cpu == i), "%d (new_mask 0x%lx): running on processor %d (AffinityMask: 0x%lx)\n",
                                i, new_mask, current_cpu, tbi.AffinityMask);
    }

    /* restore old values */
    status = pNtSetInformationProcess(GetCurrentProcess(), ProcessAffinityMask, &old_process_mask, sizeof(old_process_mask));
    ok(status == STATUS_SUCCESS, "got 0x%x (expected STATUS_SUCCESS)\n", status);

    status = pNtSetInformationThread(GetCurrentThread(), ThreadAffinityMask, &old_thread_mask, sizeof(old_thread_mask));
    ok(status == STATUS_SUCCESS, "got 0x%x (expected STATUS_SUCCESS)\n", status);
}