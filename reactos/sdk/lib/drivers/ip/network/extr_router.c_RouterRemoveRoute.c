#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  NetworkAddress; TYPE_1__* Router; } ;
struct TYPE_9__ {struct TYPE_9__* Flink; } ;
struct TYPE_8__ {int /*<<< orphan*/  Address; } ;
typedef  TYPE_1__* PNEIGHBOR_CACHE_ENTRY ;
typedef  TYPE_2__* PLIST_ENTRY ;
typedef  int /*<<< orphan*/  PIP_ADDRESS ;
typedef  TYPE_3__* PFIB_ENTRY ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KIRQL ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  A2S (int /*<<< orphan*/ ) ; 
 scalar_t__ AddrIsEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* CONTAINING_RECORD (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_ROUTER ; 
 int /*<<< orphan*/  DestroyFIBE (TYPE_3__*) ; 
 scalar_t__ FALSE ; 
 TYPE_2__ FIBListHead ; 
 int /*<<< orphan*/  FIBLock ; 
 int /*<<< orphan*/  FIB_ENTRY ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  RouterDumpRoutes () ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS RouterRemoveRoute(PIP_ADDRESS Target, PIP_ADDRESS Router)
/*
 * FUNCTION: Removes a route from the Forward Information Base (FIB)
 * ARGUMENTS:
 *     Target: The machine or network targeted by the route
 *     Router: The router used to pass the packet to the destination
 *
 * Searches the FIB and removes a route matching the indicated parameters.
 */
{
    KIRQL OldIrql;
    PLIST_ENTRY CurrentEntry;
    PLIST_ENTRY NextEntry;
    PFIB_ENTRY Current;
    BOOLEAN Found = FALSE;
    PNEIGHBOR_CACHE_ENTRY NCE;

    TI_DbgPrint(DEBUG_ROUTER, ("Called\n"));
    TI_DbgPrint(DEBUG_ROUTER, ("Deleting Route From: %s\n", A2S(Router)));
    TI_DbgPrint(DEBUG_ROUTER, ("                 To: %s\n", A2S(Target)));

    TcpipAcquireSpinLock(&FIBLock, &OldIrql);

    RouterDumpRoutes();

    CurrentEntry = FIBListHead.Flink;
    while (CurrentEntry != &FIBListHead) {
        NextEntry = CurrentEntry->Flink;
	Current = CONTAINING_RECORD(CurrentEntry, FIB_ENTRY, ListEntry);

        NCE   = Current->Router;

	if( AddrIsEqual( &Current->NetworkAddress, Target ) &&
	    AddrIsEqual( &NCE->Address, Router ) ) {
	    Found = TRUE;
	    break;
	}

	Current = NULL;
        CurrentEntry = NextEntry;
    }

    if( Found ) {
        TI_DbgPrint(DEBUG_ROUTER, ("Deleting route\n"));
        DestroyFIBE( Current );
    }

    RouterDumpRoutes();

    TcpipReleaseSpinLock(&FIBLock, OldIrql);

    TI_DbgPrint(DEBUG_ROUTER, ("Leaving\n"));

    return Found ? STATUS_SUCCESS : STATUS_UNSUCCESSFUL;
}