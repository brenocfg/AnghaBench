#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ USHORT ;
struct TYPE_8__ {int /*<<< orphan*/  IPv4Address; } ;
struct TYPE_11__ {TYPE_1__ Address; } ;
struct TYPE_10__ {scalar_t__ Checksum; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* Free ) (TYPE_2__*) ;TYPE_5__ DstAddr; scalar_t__ HeaderSize; scalar_t__ TotalSize; scalar_t__ Data; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PNEIGHBOR_CACHE_ENTRY ;
typedef  int /*<<< orphan*/  PIP_TRANSMIT_COMPLETE ;
typedef  TYPE_2__* PIP_PACKET ;
typedef  TYPE_3__* PICMP_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ICMP ; 
 int /*<<< orphan*/  IPSendDatagram (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ IPv4Checksum (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RouteGetRouteToDestination (TYPE_5__*) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

VOID ICMPTransmit(
    PIP_PACKET IPPacket,
    PIP_TRANSMIT_COMPLETE Complete,
    PVOID Context)
/*
 * FUNCTION: Transmits an ICMP packet
 * ARGUMENTS:
 *     NTE      = Pointer to net table entry to use (NULL if don't care)
 *     IPPacket = Pointer to IP packet to transmit
 */
{
    PNEIGHBOR_CACHE_ENTRY NCE;

    TI_DbgPrint(DEBUG_ICMP, ("Called.\n"));

    /* Calculate checksum of ICMP header and data */
    ((PICMP_HEADER)IPPacket->Data)->Checksum = (USHORT)
        IPv4Checksum(IPPacket->Data, IPPacket->TotalSize - IPPacket->HeaderSize, 0);

    /* Get a route to the destination address */
    if ((NCE = RouteGetRouteToDestination(&IPPacket->DstAddr))) {
        /* Send the packet */
        IPSendDatagram(IPPacket, NCE);
    } else {
        /* No route to destination (or no free resources) */
        TI_DbgPrint(DEBUG_ICMP, ("No route to destination address 0x%X.\n",
                                 IPPacket->DstAddr.Address.IPv4Address));
        IPPacket->Free(IPPacket);
    }
}