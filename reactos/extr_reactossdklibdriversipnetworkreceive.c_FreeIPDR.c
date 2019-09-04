#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_10__ {struct TYPE_10__* Flink; } ;
struct TYPE_11__ {scalar_t__ IPv4Header; int /*<<< orphan*/  Packet; scalar_t__ ReturnPacket; TYPE_1__ FragmentListHead; TYPE_1__ HoleListHead; } ;
typedef  TYPE_1__* PLIST_ENTRY ;
typedef  TYPE_2__* PIP_FRAGMENT ;
typedef  TYPE_2__* PIPDATAGRAM_REASSEMBLY ;
typedef  TYPE_2__* PIPDATAGRAM_HOLE ;

/* Variables and functions */
 TYPE_2__* CONTAINING_RECORD (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_IP ; 
 int /*<<< orphan*/  ExFreePoolWithTag (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  FreeNdisPacket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPDATAGRAM_HOLE ; 
 int /*<<< orphan*/  IPDRList ; 
 int /*<<< orphan*/  IPFragmentList ; 
 int /*<<< orphan*/  IPHoleList ; 
 int /*<<< orphan*/  IP_FRAGMENT ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  NdisReturnPackets (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PACKET_BUFFER_TAG ; 
 int /*<<< orphan*/  RemoveEntryList (TYPE_1__*) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

VOID FreeIPDR(
  PIPDATAGRAM_REASSEMBLY IPDR)
/*
 * FUNCTION: Frees an IP datagram reassembly structure
 * ARGUMENTS:
 *     IPDR = Pointer to IP datagram reassembly structure
 */
{
  PLIST_ENTRY CurrentEntry;
  PLIST_ENTRY NextEntry;
  PIPDATAGRAM_HOLE CurrentH;
  PIP_FRAGMENT CurrentF;

  TI_DbgPrint(DEBUG_IP, ("Freeing IP datagram reassembly descriptor (0x%X).\n", IPDR));

  /* Free all descriptors */
  CurrentEntry = IPDR->HoleListHead.Flink;
  while (CurrentEntry != &IPDR->HoleListHead) {
    NextEntry = CurrentEntry->Flink;
	  CurrentH = CONTAINING_RECORD(CurrentEntry, IPDATAGRAM_HOLE, ListEntry);
    /* Unlink it from the list */
    RemoveEntryList(CurrentEntry);

    TI_DbgPrint(DEBUG_IP, ("Freeing hole descriptor at (0x%X).\n", CurrentH));

    /* And free the hole descriptor */
    ExFreeToNPagedLookasideList(&IPHoleList, CurrentH);

    CurrentEntry = NextEntry;
  }

  /* Free all fragments */
  CurrentEntry = IPDR->FragmentListHead.Flink;
  while (CurrentEntry != &IPDR->FragmentListHead) {
    NextEntry = CurrentEntry->Flink;
	  CurrentF = CONTAINING_RECORD(CurrentEntry, IP_FRAGMENT, ListEntry);
    /* Unlink it from the list */
    RemoveEntryList(CurrentEntry);

    TI_DbgPrint(DEBUG_IP, ("Freeing fragment packet at (0x%X).\n", CurrentF->Packet));

    /* Free the fragment data buffer */
    if (CurrentF->ReturnPacket)
    {
        NdisReturnPackets(&CurrentF->Packet, 1);
    }
    else
    {
        FreeNdisPacket(CurrentF->Packet);
    }

    TI_DbgPrint(DEBUG_IP, ("Freeing fragment at (0x%X).\n", CurrentF));

    /* And free the fragment descriptor */
    ExFreeToNPagedLookasideList(&IPFragmentList, CurrentF);
    CurrentEntry = NextEntry;
  }

  if (IPDR->IPv4Header)
  {
      TI_DbgPrint(DEBUG_IP, ("Freeing IPDR header at (0x%X).\n", IPDR->IPv4Header));
      ExFreePoolWithTag(IPDR->IPv4Header, PACKET_BUFFER_TAG);
  }

  TI_DbgPrint(DEBUG_IP, ("Freeing IPDR data at (0x%X).\n", IPDR));

  ExFreeToNPagedLookasideList(&IPDRList, IPDR);
}