#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct NBCmdQueue {int /*<<< orphan*/  cs; } ;
typedef  scalar_t__ UCHAR ;
struct TYPE_8__ {scalar_t__ ncb_retcode; } ;
typedef  TYPE_1__* PNCB ;

/* Variables and functions */
 int /*<<< orphan*/ * CANCEL_EVENT_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 TYPE_1__** NBCmdQueueFindNBC (struct NBCmdQueue*,TYPE_1__*) ; 
 TYPE_1__** NEXT_PTR (TYPE_1__*) ; 
 scalar_t__ NRC_BADDR ; 
 scalar_t__ NRC_CANOCCR ; 
 scalar_t__ NRC_CMDCAN ; 
 scalar_t__ NRC_INVADDRESS ; 
 int /*<<< orphan*/  TRACE (char*,struct NBCmdQueue*,...) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UCHAR NBCmdQueueCancel(struct NBCmdQueue *queue, PNCB ncb)
{
    UCHAR ret;
    PNCB *spot;

    TRACE(": queue %p, ncb %p\n", queue, ncb);

    if (!queue)
        return NRC_BADDR;
    if (!ncb)
        return NRC_INVADDRESS;

    EnterCriticalSection(&queue->cs);
    spot = NBCmdQueueFindNBC(queue, ncb);
    if (spot)
    {
        *CANCEL_EVENT_PTR(*spot) = CreateEventW(NULL, FALSE, FALSE, NULL);
        WaitForSingleObject(*CANCEL_EVENT_PTR(*spot), INFINITE);
        CloseHandle(*CANCEL_EVENT_PTR(*spot));
        *spot = *NEXT_PTR(*spot);
        if (ncb->ncb_retcode == NRC_CMDCAN)
            ret = NRC_CMDCAN;
        else
            ret = NRC_CANOCCR;
    }
    else
        ret = NRC_INVADDRESS;
    LeaveCriticalSection(&queue->cs);
    TRACE("returning 0x%02x\n", ret);
    return ret;
}