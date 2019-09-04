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
struct TYPE_3__ {size_t msg_toget; size_t msg_tosave; int ring_buffer_size; int /*<<< orphan*/  msg_crst; int /*<<< orphan*/  msg_event; int /*<<< orphan*/ * messages; } ;
typedef  int /*<<< orphan*/  LONG ;
typedef  TYPE_1__ EventsQueue ;
typedef  int /*<<< orphan*/  Event ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL EventsQueue_GetEvent(EventsQueue* omr, Event* evt, LONG msTimeOut)
{
    if (WaitForSingleObject(omr->msg_event, msTimeOut) != WAIT_OBJECT_0)
	return FALSE;
	
    EnterCriticalSection(&omr->msg_crst);

    if (omr->msg_toget == omr->msg_tosave) /* buffer empty ? */
    {
        LeaveCriticalSection(&omr->msg_crst);
	return FALSE;
    }

    *evt = omr->messages[omr->msg_toget];
    omr->msg_toget = (omr->msg_toget + 1) % omr->ring_buffer_size;

    /* Mark the buffer as empty if needed */
    if (omr->msg_toget == omr->msg_tosave) /* buffer empty ? */
	ResetEvent(omr->msg_event);

    LeaveCriticalSection(&omr->msg_crst);
    return TRUE;
}