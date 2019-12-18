#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  State; } ;
typedef  TYPE_1__* PNEIGHBOR_CACHE_ENTRY ;
typedef  int /*<<< orphan*/  PNDIS_PACKET ;
typedef  int /*<<< orphan*/  PIPFRAGMENT_CONTEXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  IPSendComplete ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  NBQueuePacket (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

NTSTATUS IPSendFragment(
    PNDIS_PACKET NdisPacket,
    PNEIGHBOR_CACHE_ENTRY NCE,
    PIPFRAGMENT_CONTEXT IFC)
/*
 * FUNCTION: Sends an IP datagram fragment to a neighbor
 * ARGUMENTS:
 *     NdisPacket = Pointer to an NDIS packet containing fragment
 *     NCE        = Pointer to NCE for first hop to destination
 * RETURNS:
 *     Status of operation
 * NOTES:
 *     Lowest level IP send routine
 */
{
    TI_DbgPrint(MAX_TRACE, ("Called. NdisPacket (0x%X)  NCE (0x%X).\n", NdisPacket, NCE));

    TI_DbgPrint(MAX_TRACE, ("NCE->State = %d.\n", NCE->State));
    return NBQueuePacket(NCE, NdisPacket, IPSendComplete, IFC);
}