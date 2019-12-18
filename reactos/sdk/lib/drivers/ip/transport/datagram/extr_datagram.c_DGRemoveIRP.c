#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* Flink; } ;
struct TYPE_13__ {TYPE_1__ ReceiveQueue; } ;
struct TYPE_12__ {scalar_t__ Irp; int /*<<< orphan*/  ListEntry; } ;
typedef  TYPE_1__* PLIST_ENTRY ;
typedef  scalar_t__ PIRP ;
typedef  TYPE_2__* PDATAGRAM_RECEIVE_REQUEST ;
typedef  TYPE_3__* PADDRESS_FILE ;
typedef  int /*<<< orphan*/  KIRQL ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 TYPE_2__* CONTAINING_RECORD (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  DATAGRAM_RECEIVE_REQUEST ; 
 int /*<<< orphan*/  DATAGRAM_RECV_TAG ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LockObject (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnlockObject (TYPE_3__*,int /*<<< orphan*/ ) ; 

BOOLEAN DGRemoveIRP(
    PADDRESS_FILE AddrFile,
    PIRP Irp)
{
    PLIST_ENTRY ListEntry;
    PDATAGRAM_RECEIVE_REQUEST ReceiveRequest;
    KIRQL OldIrql;
    BOOLEAN Found = FALSE;

    TI_DbgPrint(MAX_TRACE, ("Called (Cancel IRP %08x for file %08x).\n",
                            Irp, AddrFile));

    LockObject(AddrFile, &OldIrql);

    for( ListEntry = AddrFile->ReceiveQueue.Flink; 
         ListEntry != &AddrFile->ReceiveQueue;
         ListEntry = ListEntry->Flink )
    {
        ReceiveRequest = CONTAINING_RECORD
            (ListEntry, DATAGRAM_RECEIVE_REQUEST, ListEntry);

        TI_DbgPrint(MAX_TRACE, ("Request: %08x?\n", ReceiveRequest));

        if (ReceiveRequest->Irp == Irp)
        {
            RemoveEntryList(&ReceiveRequest->ListEntry);
            ExFreePoolWithTag(ReceiveRequest, DATAGRAM_RECV_TAG);
            Found = TRUE;
            break;
        }
    }

    UnlockObject(AddrFile, OldIrql);

    TI_DbgPrint(MAX_TRACE, ("Done.\n"));

    return Found;
}