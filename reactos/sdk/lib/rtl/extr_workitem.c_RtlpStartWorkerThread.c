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
struct TYPE_3__ {long long QuadPart; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PTHREAD_START_ROUTINE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ LONG ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtDelayExecution (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  NtResumeThread (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlpStartThreadFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static NTSTATUS
RtlpStartWorkerThread(PTHREAD_START_ROUTINE StartRoutine)
{
    NTSTATUS Status;
    HANDLE ThreadHandle;
    LARGE_INTEGER Timeout;
    volatile LONG WorkerInitialized = 0;

    Timeout.QuadPart = -10000LL; /* Wait for 100ms */

    /* Start the thread */
    Status = RtlpStartThreadFunc(StartRoutine, (PVOID)&WorkerInitialized, &ThreadHandle);
    if (NT_SUCCESS(Status))
    {
        NtResumeThread(ThreadHandle, NULL);

        /* Poll until the thread got a chance to initialize */
        while (WorkerInitialized == 0)
        {
            NtDelayExecution(FALSE,
                             &Timeout);
        }

        NtClose(ThreadHandle);
    }

    return Status;
}