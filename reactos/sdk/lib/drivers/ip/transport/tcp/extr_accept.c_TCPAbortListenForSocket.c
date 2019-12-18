#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {struct TYPE_13__* Flink; } ;
struct TYPE_14__ {TYPE_2__ ListenRequest; } ;
struct TYPE_12__ {int /*<<< orphan*/  Entry; TYPE_3__* AssociatedEndpoint; } ;
typedef  TYPE_1__* PTDI_BUCKET ;
typedef  TYPE_2__* PLIST_ENTRY ;
typedef  TYPE_3__* PCONNECTION_ENDPOINT ;
typedef  int /*<<< orphan*/  KIRQL ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 TYPE_1__* CONTAINING_RECORD (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DereferenceObject (TYPE_3__*) ; 
 int /*<<< orphan*/  Entry ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LockObject (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TDI_BUCKET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TdiBucketLookasideList ; 
 int /*<<< orphan*/  UnlockObject (TYPE_3__*,int /*<<< orphan*/ ) ; 

BOOLEAN TCPAbortListenForSocket
(   PCONNECTION_ENDPOINT Listener,
    PCONNECTION_ENDPOINT Connection)
{
    PLIST_ENTRY ListEntry;
    PTDI_BUCKET Bucket;
    KIRQL OldIrql;
    BOOLEAN Found = FALSE;

    LockObject(Listener, &OldIrql);

    ListEntry = Listener->ListenRequest.Flink;
    while (ListEntry != &Listener->ListenRequest)
    {
        Bucket = CONTAINING_RECORD(ListEntry, TDI_BUCKET, Entry);

        if (Bucket->AssociatedEndpoint == Connection)
        {
            DereferenceObject(Bucket->AssociatedEndpoint);
            RemoveEntryList( &Bucket->Entry );
            ExFreeToNPagedLookasideList(&TdiBucketLookasideList, Bucket);
            Found = TRUE;
            break;
        }

        ListEntry = ListEntry->Flink;
    }

    UnlockObject(Listener, OldIrql);

    return Found;
}