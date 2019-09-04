#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pbuf {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/  PacketQueue; } ;
struct TYPE_4__ {int /*<<< orphan*/  ListEntry; scalar_t__ Offset; struct pbuf* p; } ;
typedef  TYPE_1__* PQUEUE_ENTRY ;
typedef  TYPE_2__* PCONNECTION_ENDPOINT ;

/* Variables and functions */
 scalar_t__ ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExInterlockedInsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QueueEntryLookasideList ; 

void LibTCPEnqueuePacket(PCONNECTION_ENDPOINT Connection, struct pbuf *p)
{
    PQUEUE_ENTRY qp;

    qp = (PQUEUE_ENTRY)ExAllocateFromNPagedLookasideList(&QueueEntryLookasideList);
    qp->p = p;
    qp->Offset = 0;

    ExInterlockedInsertTailList(&Connection->PacketQueue, &qp->ListEntry, &Connection->Lock);
}