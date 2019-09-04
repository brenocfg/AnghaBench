#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ResetStatus; int /*<<< orphan*/  Lock; scalar_t__ FirstPendingPacket; scalar_t__ PendingRequest; } ;
struct TYPE_6__ {TYPE_1__ NdisMiniportBlock; } ;
typedef  TYPE_2__* PLOGICAL_ADAPTER ;
typedef  scalar_t__ NDIS_WORK_ITEM_TYPE ;
typedef  int /*<<< orphan*/  KIRQL ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KeAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MiniGetFirstWorkItem (TYPE_2__*,scalar_t__) ; 
 scalar_t__ NDIS_STATUS_PENDING ; 
 scalar_t__ NdisWorkItemRequest ; 
 scalar_t__ NdisWorkItemResetRequested ; 
 scalar_t__ NdisWorkItemSend ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
MiniIsBusy(
    PLOGICAL_ADAPTER Adapter,
    NDIS_WORK_ITEM_TYPE Type)
{
    BOOLEAN Busy = FALSE;
    KIRQL OldIrql;

    KeAcquireSpinLock(&Adapter->NdisMiniportBlock.Lock, &OldIrql);

    if (MiniGetFirstWorkItem(Adapter, Type))
    {
        Busy = TRUE;
    }
    else if (Type == NdisWorkItemRequest && Adapter->NdisMiniportBlock.PendingRequest)
    {
       Busy = TRUE;
    }
    else if (Type == NdisWorkItemSend && Adapter->NdisMiniportBlock.FirstPendingPacket)
    {
       Busy = TRUE;
    }
    else if (Type == NdisWorkItemResetRequested &&
             Adapter->NdisMiniportBlock.ResetStatus == NDIS_STATUS_PENDING)
    {
       Busy = TRUE;
    }

    KeReleaseSpinLock(&Adapter->NdisMiniportBlock.Lock, OldIrql);

    return Busy;
}