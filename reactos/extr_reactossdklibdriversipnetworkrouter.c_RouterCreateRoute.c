#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_13__ {int /*<<< orphan*/  Netmask; int /*<<< orphan*/  NetworkAddress; TYPE_1__* Router; } ;
struct TYPE_12__ {struct TYPE_12__* Flink; } ;
struct TYPE_11__ {scalar_t__ Interface; } ;
typedef  TYPE_1__* PNEIGHBOR_CACHE_ENTRY ;
typedef  TYPE_2__* PLIST_ENTRY ;
typedef  scalar_t__ PIP_INTERFACE ;
typedef  int /*<<< orphan*/  PIP_ADDRESS ;
typedef  TYPE_3__* PFIB_ENTRY ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  A2S (int /*<<< orphan*/ ) ; 
 scalar_t__ AddrIsEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* CONTAINING_RECORD (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_ROUTER ; 
 TYPE_2__ FIBListHead ; 
 int /*<<< orphan*/  FIBLock ; 
 int /*<<< orphan*/  FIB_ENTRY ; 
 int /*<<< orphan*/  ListEntry ; 
 TYPE_1__* NBFindOrCreateNeighbor (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* RouterAddRoute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

PFIB_ENTRY RouterCreateRoute(
    PIP_ADDRESS NetworkAddress,
    PIP_ADDRESS Netmask,
    PIP_ADDRESS RouterAddress,
    PIP_INTERFACE Interface,
    UINT Metric)
/*
 * FUNCTION: Creates a route with IPv4 addresses as parameters
 * ARGUMENTS:
 *     NetworkAddress = Address of network
 *     Netmask        = Netmask of network
 *     RouterAddress  = Address of router to use
 *     NTE            = Pointer to NTE to use
 *     Metric         = Cost of this route
 * RETURNS:
 *     Pointer to FIB entry if the route was created, NULL if not.
 *     The FIB entry references the NTE. The caller is responsible
 *     for providing this reference
 */
{
    KIRQL OldIrql;
    PLIST_ENTRY CurrentEntry;
    PLIST_ENTRY NextEntry;
    PFIB_ENTRY Current;
    PNEIGHBOR_CACHE_ENTRY NCE;

    TcpipAcquireSpinLock(&FIBLock, &OldIrql);

    CurrentEntry = FIBListHead.Flink;
    while (CurrentEntry != &FIBListHead) {
        NextEntry = CurrentEntry->Flink;
        Current = CONTAINING_RECORD(CurrentEntry, FIB_ENTRY, ListEntry);

        NCE   = Current->Router;

        if(AddrIsEqual(NetworkAddress, &Current->NetworkAddress) &&
           AddrIsEqual(Netmask, &Current->Netmask) &&
           NCE->Interface == Interface)
        {
            TI_DbgPrint(DEBUG_ROUTER,("Attempting to add duplicate route to %s\n", A2S(NetworkAddress)));
            TcpipReleaseSpinLock(&FIBLock, OldIrql);
            return NULL;
        }

        CurrentEntry = NextEntry;
    }

    TcpipReleaseSpinLock(&FIBLock, OldIrql);

    /* The NCE references RouterAddress. The NCE is referenced for us */
    NCE = NBFindOrCreateNeighbor(Interface, RouterAddress, TRUE);

    if (!NCE) {
        /* Not enough free resources */
        return NULL;
    }

    return RouterAddRoute(NetworkAddress, Netmask, NCE, Metric);
}