#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ function; int /*<<< orphan*/  ready_event; int /*<<< orphan*/  result; int /*<<< orphan*/  go_event; } ;
struct TYPE_7__ {TYPE_1__ thread; } ;
typedef  TYPE_2__ SessionInfo ;
typedef  int /*<<< orphan*/  MMRESULT ;
typedef  scalar_t__ LPVOID ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 scalar_t__ DRVM_TERMINATE ; 
 int FALSE ; 
 int /*<<< orphan*/  GetCurrentThread () ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  MMSYSERR_ERROR ; 
 int /*<<< orphan*/  PerformWaveIO (TYPE_2__*) ; 
 int /*<<< orphan*/  ProcessSessionThreadRequest (TYPE_2__*) ; 
 int /*<<< orphan*/  ReturnCompletedBuffers (TYPE_2__*) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetThreadPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_PRIORITY_TIME_CRITICAL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WAIT_IO_COMPLETION ; 
 scalar_t__ WaitForSingleObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DWORD
WaveThread(LPVOID parameter)
{
    MMRESULT result = MMSYSERR_ERROR;
    SessionInfo* session_info = (SessionInfo*) parameter;
    BOOL terminate = FALSE;

    /* All your CPU time are belong to us */
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    DPRINT("Wave processing thread setting ready state\n");

    SetEvent(session_info->thread.ready_event);

    while ( ! terminate )
    {
        /* Wait for GO event, or IO completion notification */
        while ( WaitForSingleObjectEx(session_info->thread.go_event,
                                      INFINITE,
                                      TRUE) == WAIT_IO_COMPLETION )
        {
            /* A buffer has been finished with - pass back to the client */
            ReturnCompletedBuffers(session_info);
        }

        DPRINT("Wave processing thread woken up\n");

        /* Set the terminate flag if that's what the caller wants */
        terminate = (session_info->thread.function == DRVM_TERMINATE);

        /* Process the request */
        DPRINT("Processing thread request\n");
        result = ProcessSessionThreadRequest(session_info);

        /* Store the result code */
        session_info->thread.result = result;

        /* Submit new buffers and continue existing ones */
        DPRINT("Performing wave I/O\n");
        PerformWaveIO(session_info);

        /* Now we're ready for more action */
        DPRINT("Wave processing thread sleeping\n");
        SetEvent(session_info->thread.ready_event);
    }

    return 0;
}