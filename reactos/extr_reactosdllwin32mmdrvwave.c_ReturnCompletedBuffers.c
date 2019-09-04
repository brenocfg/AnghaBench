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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {int dwFlags; struct TYPE_7__* lpNext; } ;
struct TYPE_6__ {scalar_t__ device_type; TYPE_2__* wave_queue; } ;
typedef  TYPE_1__ SessionInfo ;
typedef  TYPE_2__* PWAVEHDR ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  NotifyClient (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WHDR_DONE ; 
 int WHDR_INQUEUE ; 
 int /*<<< orphan*/  WIM_DATA ; 
 int /*<<< orphan*/  WOM_DONE ; 
 scalar_t__ WaveOutDevice ; 

VOID
ReturnCompletedBuffers(SessionInfo* session_info)
{
    PWAVEHDR header = NULL;

    /* Set the current header and test to ensure it's not NULL */
    while ( ( header = session_info->wave_queue ) )
    {
        if ( header->dwFlags & WHDR_DONE )
        {
            DWORD message;

            /* Mark as done, and unqueued */
            header->dwFlags &= ~WHDR_INQUEUE;
            header->dwFlags |= WHDR_DONE;

            /* Trim it from the start of the queue */
            session_info->wave_queue = header->lpNext;

            /* Choose appropriate notification */
            message = (session_info->device_type == WaveOutDevice) ? WOM_DONE :
                                                                     WIM_DATA;

            DPRINT("Notifying client that buffer 0x%p is done\n", header);

            /* Notify the client */
            NotifyClient(session_info, message, (DWORD_PTR) header, 0);
        }
    }

    /* TODO: Perform I/O as a new buffer may have arrived */
}