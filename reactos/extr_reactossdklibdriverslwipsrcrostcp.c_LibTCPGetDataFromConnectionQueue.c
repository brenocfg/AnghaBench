#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pbuf {scalar_t__ tot_len; } ;
typedef  scalar_t__ UINT ;
struct TYPE_10__ {int /*<<< orphan*/  ReceiveShutdownStatus; scalar_t__ ReceiveShutdown; int /*<<< orphan*/  PacketQueue; } ;
struct TYPE_9__ {scalar_t__ Offset; struct pbuf* p; int /*<<< orphan*/  ListEntry; } ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  TYPE_1__* PQUEUE_ENTRY ;
typedef  TYPE_2__* PCONNECTION_ENDPOINT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  InsertHeadList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsListEmpty (int /*<<< orphan*/ *) ; 
 TYPE_1__* LibTCPDequeuePacket (TYPE_2__*) ; 
 int /*<<< orphan*/  LockObject (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  QueueEntryLookasideList ; 
 int /*<<< orphan*/  STATUS_PENDING ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  UnlockObject (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pbuf_copy_partial (struct pbuf*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pbuf_free_callback (struct pbuf*) ; 

NTSTATUS LibTCPGetDataFromConnectionQueue(PCONNECTION_ENDPOINT Connection, PUCHAR RecvBuffer, UINT RecvLen, UINT *Received)
{
    PQUEUE_ENTRY qp;
    struct pbuf* p;
    NTSTATUS Status;
    UINT ReadLength, PayloadLength, Offset, Copied;
    KIRQL OldIrql;

    (*Received) = 0;

    LockObject(Connection, &OldIrql);

    if (!IsListEmpty(&Connection->PacketQueue))
    {
        while ((qp = LibTCPDequeuePacket(Connection)) != NULL)
        {
            p = qp->p;

            /* Calculate the payload length first */
            PayloadLength = p->tot_len;
            PayloadLength -= qp->Offset;
            Offset = qp->Offset;

            /* Check if we're reading the whole buffer */
            ReadLength = MIN(PayloadLength, RecvLen);
            ASSERT(ReadLength != 0);
            if (ReadLength != PayloadLength)
            {
                /* Save this one for later */
                qp->Offset += ReadLength;
                InsertHeadList(&Connection->PacketQueue, &qp->ListEntry);
                qp = NULL;
            }

            UnlockObject(Connection, OldIrql);

            Copied = pbuf_copy_partial(p, RecvBuffer, ReadLength, Offset);
            ASSERT(Copied == ReadLength);

            LockObject(Connection, &OldIrql);

            /* Update trackers */
            RecvLen -= ReadLength;
            RecvBuffer += ReadLength;
            (*Received) += ReadLength;

            if (qp != NULL)
            {
                /* Use this special pbuf free callback function because we're outside tcpip thread */
                pbuf_free_callback(qp->p);

                ExFreeToNPagedLookasideList(&QueueEntryLookasideList, qp);
            }
            else
            {
                /* If we get here, it means we've filled the buffer */
                ASSERT(RecvLen == 0);
            }

            ASSERT((*Received) != 0);
            Status = STATUS_SUCCESS;

            if (!RecvLen)
                break;
        }
    }
    else
    {
        if (Connection->ReceiveShutdown)
            Status = Connection->ReceiveShutdownStatus;
        else
            Status = STATUS_PENDING;
    }

    UnlockObject(Connection, OldIrql);

    return Status;
}