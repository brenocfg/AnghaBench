#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* ready_event; void* go_event; int /*<<< orphan*/  handle; } ;
struct TYPE_8__ {scalar_t__ device_type; TYPE_1__ thread; } ;
typedef  TYPE_2__ SessionInfo ;
typedef  scalar_t__ MMRESULT ;
typedef  TYPE_2__* LPTASKCALLBACK ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_2__*) ; 
 int /*<<< orphan*/  CloseHandle (void*) ; 
 void* CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 scalar_t__ MMSYSERR_NOMEM ; 
 int /*<<< orphan*/  WaitForSingleObject (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ WaveOutDevice ; 
 scalar_t__ WaveThread ; 
 scalar_t__ mmTaskCreate (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

MMRESULT
StartSessionThread(SessionInfo* session_info)
{
    LPTASKCALLBACK task;
    MMRESULT result;

    ASSERT(session_info);

    /* This is our "ready" event, sent when the thread is idle */

    session_info->thread.ready_event = CreateEvent(NULL, FALSE, FALSE, NULL);

    if ( ! session_info->thread.ready_event )
    {
        DPRINT("Couldn't create thread_ready event\n");
        return MMSYSERR_NOMEM;
    }

    /* This is our "go" event, sent when we want the thread to do something */

    session_info->thread.go_event = CreateEvent(NULL, FALSE, FALSE, NULL);

    if ( ! session_info->thread.go_event )
    {
        DPRINT("Couldn't create thread_go event\n");
        CloseHandle(session_info->thread.ready_event);
        return MMSYSERR_NOMEM;
    }

    /* TODO - other kinds of devices need attention, too */
    task = ( session_info->device_type == WaveOutDevice )
           ? (LPTASKCALLBACK) WaveThread : NULL;

    ASSERT(task);

    /* Effectively, this is a beefed-up CreateThread */

    result = mmTaskCreate(task,
                          &session_info->thread.handle,
                          (DWORD_PTR)session_info);

    if ( result != MMSYSERR_NOERROR )
    {
        DPRINT("Task creation failed\n");
        CloseHandle(session_info->thread.ready_event);
        CloseHandle(session_info->thread.go_event);
        return result;
    }

    /* Wait for the thread to be ready before completing */

    WaitForSingleObject(session_info->thread.ready_event, INFINITE);

    return MMSYSERR_NOERROR;
}