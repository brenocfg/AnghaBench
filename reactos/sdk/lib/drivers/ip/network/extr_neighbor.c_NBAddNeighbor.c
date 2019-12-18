#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
typedef  void* UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  Lock; TYPE_1__* Cache; } ;
struct TYPE_8__ {int /*<<< orphan*/  Address; } ;
struct TYPE_7__ {struct TYPE_7__* Next; int /*<<< orphan*/  PacketQueue; scalar_t__ EventCount; void* EventTimer; int /*<<< orphan*/  State; scalar_t__ LinkAddress; void* LinkAddressLength; TYPE_2__ Address; int /*<<< orphan*/  Interface; } ;
typedef  scalar_t__ PVOID ;
typedef  int* PULONG ;
typedef  TYPE_1__* PNEIGHBOR_CACHE_ENTRY ;
typedef  int /*<<< orphan*/  PIP_INTERFACE ;
typedef  TYPE_2__* PIP_ADDRESS ;
typedef  int /*<<< orphan*/  NEIGHBOR_CACHE_ENTRY ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_NCACHE ; 
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int NB_HASHMASK ; 
 int /*<<< orphan*/  NCE_TAG ; 
 TYPE_3__* NeighborCache ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,void*) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,void*) ; 

PNEIGHBOR_CACHE_ENTRY NBAddNeighbor(
  PIP_INTERFACE Interface,
  PIP_ADDRESS Address,
  PVOID LinkAddress,
  UINT LinkAddressLength,
  UCHAR State,
  UINT EventTimer)
/*
 * FUNCTION: Adds a neighbor to the neighbor cache
 * ARGUMENTS:
 *   Interface         = Pointer to interface
 *   Address           = Pointer to IP address
 *   LinkAddress       = Pointer to link address (may be NULL)
 *   LinkAddressLength = Length of link address
 *   State             = State of NCE
 * RETURNS:
 *   Pointer to NCE, NULL there is not enough free resources
 * NOTES:
 *   The NCE if referenced for the caller if created. The NCE retains
 *   a reference to the IP address if it is created, the caller is
 *   responsible for providing this reference
 */
{
  PNEIGHBOR_CACHE_ENTRY NCE;
  ULONG HashValue;
  KIRQL OldIrql;

  TI_DbgPrint
      (DEBUG_NCACHE,
       ("Called. Interface (0x%X)  Address (0x%X)  "
	"LinkAddress (0x%X)  LinkAddressLength (%d)  State (0x%X)\n",
	Interface, Address, LinkAddress, LinkAddressLength, State));

  NCE = ExAllocatePoolWithTag
      (NonPagedPool, sizeof(NEIGHBOR_CACHE_ENTRY) + LinkAddressLength,
       NCE_TAG);
  if (NCE == NULL)
    {
      TI_DbgPrint(MIN_TRACE, ("Insufficient resources.\n"));
      return NULL;
    }

  NCE->Interface = Interface;
  NCE->Address = *Address;
  NCE->LinkAddressLength = LinkAddressLength;
  NCE->LinkAddress = (PVOID)&NCE[1];
  if( LinkAddress )
      RtlCopyMemory(NCE->LinkAddress, LinkAddress, LinkAddressLength);
  else
      memset(NCE->LinkAddress, 0xff, LinkAddressLength);
  NCE->State = State;
  NCE->EventTimer = EventTimer;
  NCE->EventCount = 0;
  InitializeListHead( &NCE->PacketQueue );

  TI_DbgPrint(MID_TRACE,("NCE: %x\n", NCE));

  HashValue = *(PULONG)&Address->Address;
  HashValue ^= HashValue >> 16;
  HashValue ^= HashValue >> 8;
  HashValue ^= HashValue >> 4;
  HashValue &= NB_HASHMASK;

  TcpipAcquireSpinLock(&NeighborCache[HashValue].Lock, &OldIrql);

  NCE->Next = NeighborCache[HashValue].Cache;
  NeighborCache[HashValue].Cache = NCE;

  TcpipReleaseSpinLock(&NeighborCache[HashValue].Lock, OldIrql);

  return NCE;
}