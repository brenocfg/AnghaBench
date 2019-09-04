#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  ListEntry; } ;
typedef  TYPE_1__* PIPDATAGRAM_REASSEMBLY ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_IP ; 
 int /*<<< orphan*/  ReassemblyListLock ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

VOID RemoveIPDR(
  PIPDATAGRAM_REASSEMBLY IPDR)
/*
 * FUNCTION: Removes an IP datagram reassembly structure from the global list
 * ARGUMENTS:
 *     IPDR = Pointer to IP datagram reassembly structure
 */
{
  KIRQL OldIrql;

  TI_DbgPrint(DEBUG_IP, ("Removing IPDR at (0x%X).\n", IPDR));

  TcpipAcquireSpinLock(&ReassemblyListLock, &OldIrql);
  RemoveEntryList(&IPDR->ListEntry);
  TcpipReleaseSpinLock(&ReassemblyListLock, OldIrql);
}