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
typedef  scalar_t__ UINT ;
typedef  int UCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  Netmask; int /*<<< orphan*/  NetworkAddress; TYPE_1__* Router; } ;
struct TYPE_9__ {struct TYPE_9__* Flink; } ;
struct TYPE_8__ {int State; int /*<<< orphan*/  Address; } ;
typedef  TYPE_1__* PNEIGHBOR_CACHE_ENTRY ;
typedef  TYPE_2__* PLIST_ENTRY ;
typedef  int /*<<< orphan*/ * PIP_ADDRESS ;
typedef  TYPE_3__* PFIB_ENTRY ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  A2S (int /*<<< orphan*/ *) ; 
 scalar_t__ AddrCountPrefixBits (int /*<<< orphan*/ *) ; 
 TYPE_3__* CONTAINING_RECORD (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CommonPrefixLength (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEBUG_ROUTER ; 
 TYPE_2__ FIBListHead ; 
 int /*<<< orphan*/  FIBLock ; 
 int /*<<< orphan*/  FIB_ENTRY ; 
 int /*<<< orphan*/  ListEntry ; 
 int NUD_INCOMPLETE ; 
 int NUD_STALE ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

PNEIGHBOR_CACHE_ENTRY RouterGetRoute(PIP_ADDRESS Destination)
/*
 * FUNCTION: Finds a router to use to get to Destination
 * ARGUMENTS:
 *     Destination = Pointer to destination address (NULL means don't care)
 * RETURNS:
 *     Pointer to NCE for router, NULL if none was found
 * NOTES:
 *     If found the NCE is referenced
 */
{
    KIRQL OldIrql;
    PLIST_ENTRY CurrentEntry;
    PLIST_ENTRY NextEntry;
    PFIB_ENTRY Current;
    UCHAR State;
    UINT Length, BestLength = 0, MaskLength;
    PNEIGHBOR_CACHE_ENTRY NCE, BestNCE = NULL;

    TI_DbgPrint(DEBUG_ROUTER, ("Called. Destination (0x%X)\n", Destination));

    TI_DbgPrint(DEBUG_ROUTER, ("Destination (%s)\n", A2S(Destination)));

    TcpipAcquireSpinLock(&FIBLock, &OldIrql);

    CurrentEntry = FIBListHead.Flink;
    while (CurrentEntry != &FIBListHead) {
        NextEntry = CurrentEntry->Flink;
	    Current = CONTAINING_RECORD(CurrentEntry, FIB_ENTRY, ListEntry);

        NCE   = Current->Router;
        State = NCE->State;

	Length = CommonPrefixLength(Destination, &Current->NetworkAddress);
	MaskLength = AddrCountPrefixBits(&Current->Netmask);

	TI_DbgPrint(DEBUG_ROUTER,("This-Route: %s (Sharing %d bits)\n",
				  A2S(&NCE->Address), Length));

	if(Length >= MaskLength && (Length > BestLength || !BestNCE) &&
           ((!(State & NUD_STALE) && !(State & NUD_INCOMPLETE)) || !BestNCE)) {
	    /* This seems to be a better router */
	    BestNCE    = NCE;
	    BestLength = Length;
	    TI_DbgPrint(DEBUG_ROUTER,("Route selected\n"));
	}

        CurrentEntry = NextEntry;
    }

    TcpipReleaseSpinLock(&FIBLock, OldIrql);

    if( BestNCE ) {
	TI_DbgPrint(DEBUG_ROUTER,("Routing to %s\n", A2S(&BestNCE->Address)));
    } else {
	TI_DbgPrint(DEBUG_ROUTER,("Packet won't be routed\n"));
    }

    return BestNCE;
}