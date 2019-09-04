#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct NBCmdQueue {int /*<<< orphan*/  cs; scalar_t__ head; } ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  scalar_t__ PNCB ;

/* Variables and functions */
 int /*<<< orphan*/ ** CANCEL_EVENT_PTR (scalar_t__) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__* NEXT_PTR (scalar_t__) ; 
 int /*<<< orphan*/  NRC_BADDR ; 
 int /*<<< orphan*/  NRC_GOODRET ; 
 int /*<<< orphan*/  NRC_INVADDRESS ; 
 int /*<<< orphan*/  TRACE (char*,struct NBCmdQueue*,...) ; 

UCHAR NBCmdQueueAdd(struct NBCmdQueue *queue, PNCB ncb)
{
    UCHAR ret;

    TRACE(": queue %p, ncb %p\n", queue, ncb);

    if (!queue)
        return NRC_BADDR;
    if (!ncb)
        return NRC_INVADDRESS;

    *CANCEL_EVENT_PTR(ncb) = NULL;
    EnterCriticalSection(&queue->cs);
    *NEXT_PTR(ncb) = queue->head;
    queue->head = ncb;
    ret = NRC_GOODRET;
    LeaveCriticalSection(&queue->cs);
    TRACE("returning 0x%02x\n", ret);
    return ret;
}