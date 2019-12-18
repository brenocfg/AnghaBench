#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UDP_HEADER ;
struct TYPE_15__ {int Type; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* Free ) (TYPE_1__*) ;int /*<<< orphan*/  NdisPacket; scalar_t__ TotalSize; } ;
typedef  TYPE_1__* PIP_PACKET ;
typedef  TYPE_2__* PIP_ADDRESS ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  PADDRESS_FILE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IPv4_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  A2S (TYPE_2__*) ; 
 int /*<<< orphan*/  AddUDPHeaderIPv4 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AllocatePacketWithBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  DISPLAY_IP_PACKET (TYPE_1__*) ; 
 int /*<<< orphan*/  IPInitializePacket (TYPE_1__*,int) ; 
#define  IP_ADDRESS_V4 129 
#define  IP_ADDRESS_V6 128 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 

NTSTATUS BuildUDPPacket(
    PADDRESS_FILE AddrFile,
    PIP_PACKET Packet,
    PIP_ADDRESS RemoteAddress,
    USHORT RemotePort,
    PIP_ADDRESS LocalAddress,
    USHORT LocalPort,
    PCHAR DataBuffer,
    UINT DataLen )
/*
 * FUNCTION: Builds an UDP packet
 * ARGUMENTS:
 *     Context      = Pointer to context information (DATAGRAM_SEND_REQUEST)
 *     LocalAddress = Pointer to our local address
 *     LocalPort    = The port we send this datagram from
 *     IPPacket     = Address of pointer to IP packet
 * RETURNS:
 *     Status of operation
 */
{
    NTSTATUS Status;

    TI_DbgPrint(MAX_TRACE, ("Called.\n"));

    /* FIXME: Assumes IPv4 */
    IPInitializePacket(Packet, IP_ADDRESS_V4);

    Packet->TotalSize = sizeof(IPv4_HEADER) + sizeof(UDP_HEADER) + DataLen;

    /* Prepare packet */
    Status = AllocatePacketWithBuffer(&Packet->NdisPacket,
                                      NULL,
                                      Packet->TotalSize );

    if( !NT_SUCCESS(Status) )
    {
        Packet->Free(Packet);
        return Status;
    }

    TI_DbgPrint(MID_TRACE, ("Allocated packet: %x\n", Packet->NdisPacket));
    TI_DbgPrint(MID_TRACE, ("Local Addr : %s\n", A2S(LocalAddress)));
    TI_DbgPrint(MID_TRACE, ("Remote Addr: %s\n", A2S(RemoteAddress)));

    switch (RemoteAddress->Type) {
        case IP_ADDRESS_V4:
            Status = AddUDPHeaderIPv4(AddrFile, RemoteAddress, RemotePort,
                                      LocalAddress, LocalPort, Packet, DataBuffer, DataLen);
            break;
        case IP_ADDRESS_V6:
            /* FIXME: Support IPv6 */
            TI_DbgPrint(MIN_TRACE, ("IPv6 UDP datagrams are not supported.\n"));
        default:
            Status = STATUS_UNSUCCESSFUL;
            break;
    }
    if (!NT_SUCCESS(Status)) {
        TI_DbgPrint(MIN_TRACE, ("Cannot add UDP header. Status = (0x%X)\n",
                                Status));
        Packet->Free(Packet);
        return Status;
    }

    TI_DbgPrint(MID_TRACE, ("Displaying packet\n"));

    DISPLAY_IP_PACKET(Packet);

    TI_DbgPrint(MID_TRACE, ("Leaving\n"));

    return STATUS_SUCCESS;
}