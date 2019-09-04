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
struct TYPE_4__ {scalar_t__ threadId; int /*<<< orphan*/  cs; scalar_t__ uTimer; int /*<<< orphan*/  hwndSelf; scalar_t__ hStopEvent; scalar_t__ hThread; } ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ BOOL ;
typedef  TYPE_1__ ANIMATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACN_STOP ; 
 int /*<<< orphan*/  ANIMATE_Notify (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetCurrentThreadId () ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetEvent (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WaitForSingleObject (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL ANIMATE_DoStop(ANIMATE_INFO *infoPtr)
{
    BOOL stopped = FALSE;

    EnterCriticalSection(&infoPtr->cs);

    /* should stop playing */
    if (infoPtr->hThread)
    {
        HANDLE handle = infoPtr->hThread;

        TRACE("stopping animation thread\n");
        infoPtr->hThread = 0;
        SetEvent( infoPtr->hStopEvent );

        if (infoPtr->threadId != GetCurrentThreadId())
        {
            LeaveCriticalSection(&infoPtr->cs);  /* leave it a chance to run */
            WaitForSingleObject( handle, INFINITE );
            TRACE("animation thread stopped\n");
            EnterCriticalSection(&infoPtr->cs);
        }

        CloseHandle( handle );
        CloseHandle( infoPtr->hStopEvent );
        infoPtr->hStopEvent = 0;
        stopped = TRUE;
    }
    if (infoPtr->uTimer) {
	KillTimer(infoPtr->hwndSelf, infoPtr->uTimer);
	infoPtr->uTimer = 0;
	stopped = TRUE;
    }

    LeaveCriticalSection(&infoPtr->cs);

    if (stopped)
        ANIMATE_Notify(infoPtr, ACN_STOP);

    return TRUE;
}