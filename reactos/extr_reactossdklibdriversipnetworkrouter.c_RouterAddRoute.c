#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int /*<<< orphan*/  ListEntry; int /*<<< orphan*/  Metric; TYPE_1__* Router; int /*<<< orphan*/  Netmask; int /*<<< orphan*/  NetworkAddress; } ;
struct TYPE_6__ {int /*<<< orphan*/  Address; } ;
typedef  TYPE_1__* PNEIGHBOR_CACHE_ENTRY ;
typedef  int /*<<< orphan*/ * PIP_ADDRESS ;
typedef  TYPE_2__* PFIB_ENTRY ;
typedef  int /*<<< orphan*/  FIB_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  A2S (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEBUG_ROUTER ; 
 TYPE_2__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIBListHead ; 
 int /*<<< orphan*/  FIBLock ; 
 int /*<<< orphan*/  FIB_TAG ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TcpipInterlockedInsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

PFIB_ENTRY RouterAddRoute(
    PIP_ADDRESS NetworkAddress,
    PIP_ADDRESS Netmask,
    PNEIGHBOR_CACHE_ENTRY Router,
    UINT Metric)
/*
 * FUNCTION: Adds a route to the Forward Information Base (FIB)
 * ARGUMENTS:
 *     NetworkAddress = Pointer to address of network
 *     Netmask        = Pointer to netmask of network
 *     Router         = Pointer to NCE of router to use
 *     Metric         = Cost of this route
 * RETURNS:
 *     Pointer to FIB entry if the route was added, NULL if not
 * NOTES:
 *     The FIB entry references the NetworkAddress, Netmask and
 *     the NCE of the router. The caller is responsible for providing
 *     these references
 */
{
    PFIB_ENTRY FIBE;

    TI_DbgPrint(DEBUG_ROUTER, ("Called. NetworkAddress (0x%X)  Netmask (0x%X) "
        "Router (0x%X)  Metric (%d).\n", NetworkAddress, Netmask, Router, Metric));

    TI_DbgPrint(DEBUG_ROUTER, ("NetworkAddress (%s)  Netmask (%s)  Router (%s).\n",
			       A2S(NetworkAddress),
			       A2S(Netmask),
			       A2S(&Router->Address)));

    FIBE = ExAllocatePoolWithTag(NonPagedPool, sizeof(FIB_ENTRY), FIB_TAG);
    if (!FIBE) {
        TI_DbgPrint(MIN_TRACE, ("Insufficient resources.\n"));
        return NULL;
    }

    RtlCopyMemory( &FIBE->NetworkAddress, NetworkAddress,
		   sizeof(FIBE->NetworkAddress) );
    RtlCopyMemory( &FIBE->Netmask, Netmask,
		   sizeof(FIBE->Netmask) );
    FIBE->Router         = Router;
    FIBE->Metric         = Metric;

    /* Add FIB to the forward information base */
    TcpipInterlockedInsertTailList(&FIBListHead, &FIBE->ListEntry, &FIBLock);

    return FIBE;
}