#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_18__ {int /*<<< orphan*/  Protocol; } ;
struct TYPE_17__ {int Type; } ;
struct TYPE_16__ {int /*<<< orphan*/  Flags; scalar_t__ Data; scalar_t__ Header; int /*<<< orphan*/  (* Free ) (TYPE_1__*) ;int /*<<< orphan*/  NdisPacket; scalar_t__ TotalSize; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PIP_PACKET ;
typedef  TYPE_2__* PIP_ADDRESS ;
typedef  scalar_t__ PCHAR ;
typedef  TYPE_3__* PADDRESS_FILE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IPv4_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  A2S (TYPE_2__*) ; 
 int /*<<< orphan*/  AddGenericHeaderIPv4 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AllocatePacketWithBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  DISPLAY_IP_PACKET (TYPE_1__*) ; 
 int /*<<< orphan*/  IPInitializePacket (TYPE_1__*,int) ; 
#define  IP_ADDRESS_V4 129 
#define  IP_ADDRESS_V6 128 
 int /*<<< orphan*/  IP_PACKET_FLAG_RAW ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

NTSTATUS BuildRawIpPacket(
    PADDRESS_FILE AddrFile,
    PIP_PACKET Packet,
    PIP_ADDRESS RemoteAddress,
    USHORT RemotePort,
    PIP_ADDRESS LocalAddress,
    USHORT LocalPort,
    PCHAR DataBuffer,
    UINT DataLen )
/*
 * FUNCTION: Builds an RawIp packet
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
    PCHAR Payload;

    TI_DbgPrint(MAX_TRACE, ("Called.\n"));

    /* FIXME: Assumes IPv4 */
    IPInitializePacket(Packet, IP_ADDRESS_V4);

    Packet->TotalSize = sizeof(IPv4_HEADER) + DataLen;

    /* Prepare packet */
    Status = AllocatePacketWithBuffer( &Packet->NdisPacket,
				       NULL,
				       Packet->TotalSize );

    if( !NT_SUCCESS(Status) ) return Status;

    TI_DbgPrint(MID_TRACE, ("Allocated packet: %x\n", Packet->NdisPacket));
    TI_DbgPrint(MID_TRACE, ("Local Addr : %s\n", A2S(LocalAddress)));
    TI_DbgPrint(MID_TRACE, ("Remote Addr: %s\n", A2S(RemoteAddress)));

    switch (RemoteAddress->Type) {
    case IP_ADDRESS_V4:
	Status = AddGenericHeaderIPv4
            (AddrFile, RemoteAddress, RemotePort,
             LocalAddress, LocalPort, Packet, DataLen,
             AddrFile->Protocol,
             0, (PVOID *)&Payload );
	break;
    case IP_ADDRESS_V6:
	/* FIXME: Support IPv6 */
        Status = STATUS_UNSUCCESSFUL;
	TI_DbgPrint(MIN_TRACE, ("IPv6 RawIp datagrams are not supported.\n"));
        break;

    default:
	Status = STATUS_UNSUCCESSFUL;
        TI_DbgPrint(MIN_TRACE, ("Bad Address Type %d\n", RemoteAddress->Type));
	break;
    }

    if( !NT_SUCCESS(Status) ) {
        TI_DbgPrint(MIN_TRACE, ("Cannot add header. Status = (0x%X)\n",
                                Status));
        Packet->Free(Packet);
        return Status;
    }

    TI_DbgPrint(MID_TRACE, ("Copying data (hdr %x data %x (%d))\n",
			    Packet->Header, Packet->Data,
			    (PCHAR)Packet->Data - (PCHAR)Packet->Header));

    RtlCopyMemory( Packet->Data, DataBuffer, DataLen );

    Packet->Flags |= IP_PACKET_FLAG_RAW;

    TI_DbgPrint(MID_TRACE, ("Displaying packet\n"));

    DISPLAY_IP_PACKET(Packet);

    TI_DbgPrint(MID_TRACE, ("Leaving\n"));

    return STATUS_SUCCESS;
}