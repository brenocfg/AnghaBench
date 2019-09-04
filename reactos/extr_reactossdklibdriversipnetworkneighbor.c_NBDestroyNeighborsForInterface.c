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
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
struct TYPE_6__ {int /*<<< orphan*/  Lock; TYPE_1__* Cache; } ;
struct TYPE_5__ {scalar_t__ Interface; struct TYPE_5__* Next; } ;
typedef  TYPE_1__* PNEIGHBOR_CACHE_ENTRY ;
typedef  scalar_t__ PIP_INTERFACE ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_LEVEL ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeLowerIrql (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeRaiseIrql (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NBFlushPacketQueue (TYPE_1__*,int /*<<< orphan*/ ) ; 
 size_t NB_HASHMASK ; 
 int /*<<< orphan*/  NCE_TAG ; 
 int /*<<< orphan*/  NDIS_STATUS_REQUEST_ABORTED ; 
 TYPE_2__* NeighborCache ; 
 int /*<<< orphan*/  TcpipAcquireSpinLockAtDpcLevel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLockFromDpcLevel (int /*<<< orphan*/ *) ; 

VOID NBDestroyNeighborsForInterface(PIP_INTERFACE Interface)
{
    KIRQL OldIrql;
    PNEIGHBOR_CACHE_ENTRY *PrevNCE;
    PNEIGHBOR_CACHE_ENTRY NCE;
    ULONG i;

    KeRaiseIrql(DISPATCH_LEVEL, &OldIrql);
    for (i = 0; i <= NB_HASHMASK; i++)
    {
        TcpipAcquireSpinLockAtDpcLevel(&NeighborCache[i].Lock);
        
        for (PrevNCE = &NeighborCache[i].Cache;
             (NCE = *PrevNCE) != NULL;)
        {
            if (NCE->Interface == Interface)
            {
                /* Unlink and destroy the NCE */
                *PrevNCE = NCE->Next;

                NBFlushPacketQueue(NCE, NDIS_STATUS_REQUEST_ABORTED);
                ExFreePoolWithTag(NCE, NCE_TAG);

                continue;
            }
            else
            {
                PrevNCE = &NCE->Next;
            }
        }
        
        TcpipReleaseSpinLockFromDpcLevel(&NeighborCache[i].Lock);
    }
    KeLowerIrql(OldIrql);
}