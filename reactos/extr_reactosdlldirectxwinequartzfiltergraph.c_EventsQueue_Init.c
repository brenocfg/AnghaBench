#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* DebugInfo; } ;
struct TYPE_6__ {int ring_buffer_size; TYPE_3__ msg_crst; int /*<<< orphan*/  messages; int /*<<< orphan*/  msg_event; scalar_t__ msg_tosave; scalar_t__ msg_toget; } ;
struct TYPE_5__ {scalar_t__* Spare; } ;
typedef  TYPE_2__ EventsQueue ;
typedef  int /*<<< orphan*/  Event ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CreateEventW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EVENTS_RING_BUFFER_INCREMENT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_3__*) ; 
 int TRUE ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int EventsQueue_Init(EventsQueue* omr)
{
    omr->msg_toget = 0;
    omr->msg_tosave = 0;
    omr->msg_event = CreateEventW(NULL, TRUE, FALSE, NULL);
    omr->ring_buffer_size = EVENTS_RING_BUFFER_INCREMENT;
    omr->messages = CoTaskMemAlloc(omr->ring_buffer_size * sizeof(Event));
    ZeroMemory(omr->messages, omr->ring_buffer_size * sizeof(Event));

    InitializeCriticalSection(&omr->msg_crst);
    omr->msg_crst.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": EventsQueue.msg_crst");
    return TRUE;
}