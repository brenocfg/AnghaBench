#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
struct TYPE_14__ {int /*<<< orphan*/  Lock; } ;
struct TYPE_13__ {TYPE_3__* Context; int /*<<< orphan*/  DLComplete; } ;
struct TYPE_9__ {int /*<<< orphan*/  Address; } ;
struct TYPE_12__ {int State; int /*<<< orphan*/  LinkAddress; TYPE_2__* Interface; int /*<<< orphan*/  PacketQueue; TYPE_1__ Address; } ;
struct TYPE_11__ {int /*<<< orphan*/  Packet; } ;
struct TYPE_10__ {int /*<<< orphan*/  Context; int /*<<< orphan*/  (* Transmit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int* PULONG ;
typedef  TYPE_3__* PNEIGHBOR_PACKET ;
typedef  TYPE_4__* PNEIGHBOR_CACHE_ENTRY ;
typedef  int /*<<< orphan*/ * PLIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_3__* CONTAINING_RECORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExInterlockedRemoveHeadList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LAN_PROTO_IPv4 ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  NBCompleteSend ; 
 int NB_HASHMASK ; 
 int /*<<< orphan*/  NEIGHBOR_PACKET ; 
 int NUD_INCOMPLETE ; 
 TYPE_6__* NeighborCache ; 
 int /*<<< orphan*/  Next ; 
 TYPE_5__* PC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID NBSendPackets( PNEIGHBOR_CACHE_ENTRY NCE ) {
    PLIST_ENTRY PacketEntry;
    PNEIGHBOR_PACKET Packet;
    UINT HashValue;

    ASSERT(!(NCE->State & NUD_INCOMPLETE));

    HashValue  = *(PULONG)(&NCE->Address.Address);
    HashValue ^= HashValue >> 16;
    HashValue ^= HashValue >> 8;
    HashValue ^= HashValue >> 4;
    HashValue &= NB_HASHMASK;

    /* Send any waiting packets */
    while ((PacketEntry = ExInterlockedRemoveHeadList(&NCE->PacketQueue,
                                              &NeighborCache[HashValue].Lock)) != NULL)
    {
	Packet = CONTAINING_RECORD( PacketEntry, NEIGHBOR_PACKET, Next );

	TI_DbgPrint
	    (MID_TRACE,
	     ("PacketEntry: %x, NdisPacket %x\n",
	      PacketEntry, Packet->Packet));

	PC(Packet->Packet)->DLComplete = NBCompleteSend;
	PC(Packet->Packet)->Context  = Packet;

	NCE->Interface->Transmit
	    ( NCE->Interface->Context,
	      Packet->Packet,
	      0,
	      NCE->LinkAddress,
	      LAN_PROTO_IPv4 );
    }
}