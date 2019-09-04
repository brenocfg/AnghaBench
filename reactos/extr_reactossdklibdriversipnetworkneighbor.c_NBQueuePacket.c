#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_11__ {int /*<<< orphan*/  Lock; } ;
struct TYPE_8__ {int /*<<< orphan*/  Address; } ;
struct TYPE_10__ {int State; int /*<<< orphan*/  PacketQueue; TYPE_1__ Address; } ;
struct TYPE_9__ {int /*<<< orphan*/  Next; int /*<<< orphan*/  Packet; int /*<<< orphan*/  Context; int /*<<< orphan*/  Complete; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int* PULONG ;
typedef  int /*<<< orphan*/  PNEIGHBOR_PACKET_COMPLETE ;
typedef  TYPE_2__* PNEIGHBOR_PACKET ;
typedef  TYPE_3__* PNEIGHBOR_CACHE_ENTRY ;
typedef  int /*<<< orphan*/  PNDIS_PACKET ;
typedef  int /*<<< orphan*/  NEIGHBOR_PACKET ;
typedef  int /*<<< orphan*/  KIRQL ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_NCACHE ; 
 TYPE_2__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NBSendPackets (TYPE_3__*) ; 
 int NB_HASHMASK ; 
 int /*<<< orphan*/  NEIGHBOR_PACKET_TAG ; 
 int NUD_INCOMPLETE ; 
 TYPE_4__* NeighborCache ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOLEAN NBQueuePacket(
  PNEIGHBOR_CACHE_ENTRY NCE,
  PNDIS_PACKET NdisPacket,
  PNEIGHBOR_PACKET_COMPLETE PacketComplete,
  PVOID PacketContext)
/*
 * FUNCTION: Queues a packet on an NCE for later transmission
 * ARGUMENTS:
 *   NCE        = Pointer to NCE to queue packet on
 *   NdisPacket = Pointer to NDIS packet to queue
 * RETURNS:
 *   TRUE if the packet was successfully queued, FALSE if not
 */
{
  KIRQL OldIrql;
  PNEIGHBOR_PACKET Packet;
  UINT HashValue;

  TI_DbgPrint
      (DEBUG_NCACHE,
       ("Called. NCE (0x%X)  NdisPacket (0x%X).\n", NCE, NdisPacket));

  Packet = ExAllocatePoolWithTag( NonPagedPool, sizeof(NEIGHBOR_PACKET),
                                  NEIGHBOR_PACKET_TAG );
  if( !Packet ) return FALSE;

  /* FIXME: Should we limit the number of queued packets? */

  HashValue  = *(PULONG)(&NCE->Address.Address);
  HashValue ^= HashValue >> 16;
  HashValue ^= HashValue >> 8;
  HashValue ^= HashValue >> 4;
  HashValue &= NB_HASHMASK;

  TcpipAcquireSpinLock(&NeighborCache[HashValue].Lock, &OldIrql);

  Packet->Complete = PacketComplete;
  Packet->Context = PacketContext;
  Packet->Packet = NdisPacket;
  InsertTailList( &NCE->PacketQueue, &Packet->Next );

  TcpipReleaseSpinLock(&NeighborCache[HashValue].Lock, OldIrql);

  if( !(NCE->State & NUD_INCOMPLETE) )
      NBSendPackets( NCE );

  return TRUE;
}