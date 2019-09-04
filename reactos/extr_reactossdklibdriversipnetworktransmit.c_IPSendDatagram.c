#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* Interface; } ;
struct TYPE_5__ {int /*<<< orphan*/  MTU; } ;
typedef  TYPE_2__* PNEIGHBOR_CACHE_ENTRY ;
typedef  int /*<<< orphan*/  PIP_PACKET ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY_IP_PACKET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  SendFragments (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

NTSTATUS IPSendDatagram(PIP_PACKET IPPacket, PNEIGHBOR_CACHE_ENTRY NCE)
/*
 * FUNCTION: Sends an IP datagram to a remote address
 * ARGUMENTS:
 *     IPPacket = Pointer to an IP packet
 *     RCN      = Pointer to route cache node
 * RETURNS:
 *     Status of operation
 * NOTES:
 *     This is the highest level IP send routine. It possibly breaks the packet
 *     into two or more fragments before passing it on to the next lower level
 *     send routine (IPSendFragment)
 */
{
    TI_DbgPrint(MAX_TRACE, ("Called. IPPacket (0x%X)  NCE (0x%X)\n", IPPacket, NCE));

    DISPLAY_IP_PACKET(IPPacket);

    /* Fetch path MTU now, because it may change */
    TI_DbgPrint(MID_TRACE,("PathMTU: %d\n", NCE->Interface->MTU));

    return SendFragments(IPPacket, NCE, NCE->Interface->MTU);
}