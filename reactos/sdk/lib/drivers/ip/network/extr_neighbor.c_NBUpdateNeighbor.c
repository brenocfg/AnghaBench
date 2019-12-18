#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  Lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  Address; } ;
struct TYPE_7__ {int State; scalar_t__ EventTimer; scalar_t__ EventCount; int /*<<< orphan*/  LinkAddressLength; int /*<<< orphan*/  LinkAddress; TYPE_1__ Address; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int* PULONG ;
typedef  TYPE_2__* PNEIGHBOR_CACHE_ENTRY ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 scalar_t__ ARP_COMPLETE_TIMEOUT ; 
 int /*<<< orphan*/  DEBUG_NCACHE ; 
 int /*<<< orphan*/  NBSendPackets (TYPE_2__*) ; 
 int NB_HASHMASK ; 
 int NUD_INCOMPLETE ; 
 TYPE_3__* NeighborCache ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

VOID NBUpdateNeighbor(
  PNEIGHBOR_CACHE_ENTRY NCE,
  PVOID LinkAddress,
  UCHAR State)
/*
 * FUNCTION: Update link address information in NCE
 * ARGUMENTS:
 *   NCE         = Pointer to NCE to update
 *   LinkAddress = Pointer to link address
 *   State       = State of NCE
 * NOTES:
 *   The link address and state is updated. Any waiting packets are sent
 */
{
    KIRQL OldIrql;
    UINT HashValue;

    TI_DbgPrint(DEBUG_NCACHE, ("Called. NCE (0x%X)  LinkAddress (0x%X)  State (0x%X).\n", NCE, LinkAddress, State));

    HashValue  = *(PULONG)(&NCE->Address.Address);
    HashValue ^= HashValue >> 16;
    HashValue ^= HashValue >> 8;
    HashValue ^= HashValue >> 4;
    HashValue &= NB_HASHMASK;

    TcpipAcquireSpinLock(&NeighborCache[HashValue].Lock, &OldIrql);

    RtlCopyMemory(NCE->LinkAddress, LinkAddress, NCE->LinkAddressLength);
    NCE->State = State;
    NCE->EventCount = 0;

    TcpipReleaseSpinLock(&NeighborCache[HashValue].Lock, OldIrql);

    if( !(NCE->State & NUD_INCOMPLETE) )
    {
        if (NCE->EventTimer) NCE->EventTimer = ARP_COMPLETE_TIMEOUT;
        NBSendPackets( NCE );
    }
}