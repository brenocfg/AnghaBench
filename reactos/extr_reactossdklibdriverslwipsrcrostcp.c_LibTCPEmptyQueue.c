#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  PacketQueue; } ;
struct TYPE_8__ {int /*<<< orphan*/  p; } ;
typedef  TYPE_1__* PQUEUE_ENTRY ;
typedef  int /*<<< orphan*/  PLIST_ENTRY ;
typedef  TYPE_2__* PCONNECTION_ENDPOINT ;

/* Variables and functions */
 TYPE_1__* CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DereferenceObject (TYPE_2__*) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IsListEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  QUEUE_ENTRY ; 
 int /*<<< orphan*/  QueueEntryLookasideList ; 
 int /*<<< orphan*/  ReferenceObject (TYPE_2__*) ; 
 int /*<<< orphan*/  RemoveHeadList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pbuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
LibTCPEmptyQueue(PCONNECTION_ENDPOINT Connection)
{
    PLIST_ENTRY Entry;
    PQUEUE_ENTRY qp = NULL;

    ReferenceObject(Connection);

    while (!IsListEmpty(&Connection->PacketQueue))
    {
        Entry = RemoveHeadList(&Connection->PacketQueue);
        qp = CONTAINING_RECORD(Entry, QUEUE_ENTRY, ListEntry);

        /* We're in the tcpip thread here so this is safe */
        pbuf_free(qp->p);

        ExFreeToNPagedLookasideList(&QueueEntryLookasideList, qp);
    }

    DereferenceObject(Connection);
}