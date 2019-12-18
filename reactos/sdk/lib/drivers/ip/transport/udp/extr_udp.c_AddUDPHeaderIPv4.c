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
typedef  void* USHORT ;
typedef  void* UINT ;
typedef  int /*<<< orphan*/  UDP_HEADER ;
struct TYPE_6__ {scalar_t__ Data; scalar_t__ Header; int /*<<< orphan*/  NdisPacket; } ;
struct TYPE_5__ {void* Checksum; void* Length; void* DestPort; void* SourcePort; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PUDP_HEADER ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int /*<<< orphan*/  PIPv4_HEADER ;
typedef  TYPE_2__* PIP_PACKET ;
typedef  int /*<<< orphan*/  PIP_ADDRESS ;
typedef  scalar_t__ PCHAR ;
typedef  int /*<<< orphan*/  PADDRESS_FILE ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AddGenericHeaderIPv4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,TYPE_2__*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 void* UDPv4ChecksumCalculate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 void* WH2N (void*) ; 

NTSTATUS AddUDPHeaderIPv4(
    PADDRESS_FILE AddrFile,
    PIP_ADDRESS RemoteAddress,
    USHORT RemotePort,
    PIP_ADDRESS LocalAddress,
    USHORT LocalPort,
    PIP_PACKET IPPacket,
    PVOID Data,
    UINT DataLength)
/*
 * FUNCTION: Adds an IPv4 and UDP header to an IP packet
 * ARGUMENTS:
 *     SendRequest  = Pointer to send request
 *     LocalAddress = Pointer to our local address
 *     LocalPort    = The port we send this datagram from
 *     IPPacket     = Pointer to IP packet
 * RETURNS:
 *     Status of operation
 */
{
    PUDP_HEADER UDPHeader;
    NTSTATUS Status;

    TI_DbgPrint(MID_TRACE, ("Packet: %x NdisPacket %x\n",
			    IPPacket, IPPacket->NdisPacket));

    Status = AddGenericHeaderIPv4
        ( AddrFile, RemoteAddress, RemotePort,
          LocalAddress, LocalPort,
          IPPacket, DataLength, IPPROTO_UDP,
          sizeof(UDP_HEADER), (PVOID *)&UDPHeader );

    if (!NT_SUCCESS(Status))
        return Status;

    /* Port values are already big-endian values */
    UDPHeader->SourcePort = LocalPort;
    UDPHeader->DestPort   = RemotePort;
    UDPHeader->Checksum   = 0;
    /* Length of UDP header and data */
    UDPHeader->Length     = WH2N(DataLength + sizeof(UDP_HEADER));

    TI_DbgPrint(MID_TRACE, ("Copying data (hdr %x data %x (%d))\n",
			    IPPacket->Header, IPPacket->Data,
			    (PCHAR)IPPacket->Data - (PCHAR)IPPacket->Header));

    RtlCopyMemory(IPPacket->Data, Data, DataLength);

    UDPHeader->Checksum = UDPv4ChecksumCalculate((PIPv4_HEADER)IPPacket->Header,
                                                 (PUCHAR)UDPHeader,
                                                 DataLength + sizeof(UDP_HEADER));
    UDPHeader->Checksum = WH2N(UDPHeader->Checksum);

    TI_DbgPrint(MID_TRACE, ("Packet: %d ip %d udp %d payload\n",
			    (PCHAR)UDPHeader - (PCHAR)IPPacket->Header,
			    (PCHAR)IPPacket->Data - (PCHAR)UDPHeader,
			    DataLength));

    return STATUS_SUCCESS;
}