#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PKSPIN_LOCK ;
typedef  int /*<<< orphan*/  PIPDATAGRAM_REASSEMBLY ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  FreeIPDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  RemoveIPDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__inline VOID Cleanup(
  PKSPIN_LOCK Lock,
  KIRQL OldIrql,
  PIPDATAGRAM_REASSEMBLY IPDR)
/*
 * FUNCTION: Performs cleaning operations on errors
 * ARGUMENTS:
 *     Lock     = Pointer to spin lock to be released
 *     OldIrql  = Value of IRQL when spin lock was acquired
 *     IPDR     = Pointer to IP datagram reassembly structure to free
 *     Buffer   = Optional pointer to a buffer to free
 */
{
  TI_DbgPrint(MIN_TRACE, ("Insufficient resources.\n"));

  TcpipReleaseSpinLock(Lock, OldIrql);
  RemoveIPDR(IPDR);
  FreeIPDR(IPDR);
}