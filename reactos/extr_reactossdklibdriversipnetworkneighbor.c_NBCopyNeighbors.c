#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
typedef  size_t UINT ;
struct TYPE_9__ {int /*<<< orphan*/  IPv4Address; } ;
struct TYPE_14__ {TYPE_1__ Address; } ;
struct TYPE_13__ {int /*<<< orphan*/  Lock; TYPE_2__* Cache; } ;
struct TYPE_12__ {int /*<<< orphan*/  Type; int /*<<< orphan*/  LogAddr; int /*<<< orphan*/  PhysAddr; int /*<<< orphan*/  AddrSize; int /*<<< orphan*/  Index; } ;
struct TYPE_11__ {int /*<<< orphan*/  Index; int /*<<< orphan*/  Unicast; } ;
struct TYPE_10__ {int State; TYPE_8__ Address; int /*<<< orphan*/  LinkAddressLength; int /*<<< orphan*/  LinkAddress; TYPE_3__* Interface; struct TYPE_10__* Next; } ;
typedef  TYPE_2__* PNEIGHBOR_CACHE_ENTRY ;
typedef  TYPE_3__* PIP_INTERFACE ;
typedef  TYPE_4__* PIPARP_ENTRY ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  ARP_ENTRY_DYNAMIC ; 
 int /*<<< orphan*/  ARP_ENTRY_INVALID ; 
 int /*<<< orphan*/  ARP_ENTRY_STATIC ; 
 int /*<<< orphan*/  AddrIsEqual (TYPE_8__*,int /*<<< orphan*/ *) ; 
 size_t NB_HASHMASK ; 
 int NUD_INCOMPLETE ; 
 int NUD_PERMANENT ; 
 TYPE_5__* NeighborCache ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ULONG NBCopyNeighbors
(PIP_INTERFACE Interface,
 PIPARP_ENTRY ArpTable)
{
  PNEIGHBOR_CACHE_ENTRY CurNCE;
  KIRQL OldIrql;
  UINT Size = 0, i;

  for (i = 0; i <= NB_HASHMASK; i++) {
      TcpipAcquireSpinLock(&NeighborCache[i].Lock, &OldIrql);
      for( CurNCE = NeighborCache[i].Cache;
	   CurNCE;
	   CurNCE = CurNCE->Next ) {
	  if( CurNCE->Interface == Interface &&
              !AddrIsEqual( &CurNCE->Address, &CurNCE->Interface->Unicast ) ) {
	      if( ArpTable ) {
		  ArpTable[Size].Index = Interface->Index;
		  ArpTable[Size].AddrSize = CurNCE->LinkAddressLength;
		  RtlCopyMemory
		      (ArpTable[Size].PhysAddr, 
		       CurNCE->LinkAddress,
		       CurNCE->LinkAddressLength);
		  ArpTable[Size].LogAddr = CurNCE->Address.Address.IPv4Address;
		  if( CurNCE->State & NUD_PERMANENT )
		      ArpTable[Size].Type = ARP_ENTRY_STATIC;
		  else if( CurNCE->State & NUD_INCOMPLETE )
		      ArpTable[Size].Type = ARP_ENTRY_INVALID;
		  else
		      ArpTable[Size].Type = ARP_ENTRY_DYNAMIC;
	      }
	      Size++;
	  }
      }
      TcpipReleaseSpinLock(&NeighborCache[i].Lock, OldIrql);
  }
  
  return Size;
}