#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* USHORT ;
typedef  int ULONG_PTR ;
typedef  int ULONG ;
typedef  int UCHAR ;
struct TYPE_5__ {int HWAddrLen; int ProtoAddrLen; void* Opcode; void* ProtoType; void* HWType; } ;
struct TYPE_4__ {scalar_t__ HeaderSize; scalar_t__ MinFrameSize; } ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  PUINT ;
typedef  int /*<<< orphan*/ * PNDIS_PACKET ;
typedef  TYPE_1__* PIP_INTERFACE ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  TYPE_2__* PARP_HEADER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  int /*<<< orphan*/  ARP_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  AllocatePacketWithBuffer (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DEBUG_ARP ; 
 int /*<<< orphan*/  GetDataPtr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX (int,scalar_t__) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (scalar_t__,int) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

PNDIS_PACKET PrepareARPPacket(
    PIP_INTERFACE IF,
    USHORT HardwareType,
    USHORT ProtocolType,
    UCHAR LinkAddressLength,
    UCHAR ProtoAddressLength,
    PVOID SenderLinkAddress,
    PVOID SenderProtoAddress,
    PVOID TargetLinkAddress,
    PVOID TargetProtoAddress,
    USHORT Opcode)
/*
 * FUNCTION: Prepares an ARP packet
 * ARGUMENTS:
 *     HardwareType       = Hardware type (in network byte order)
 *     ProtocolType       = Protocol type (in network byte order)
 *     LinkAddressLength  = Length of link address fields
 *     ProtoAddressLength = Length of protocol address fields
 *     SenderLinkAddress  = Sender's link address
 *     SenderProtoAddress = Sender's protocol address
 *     TargetLinkAddress  = Target's link address (NULL if don't care)
 *     TargetProtoAddress = Target's protocol address
 *     Opcode             = ARP opcode (in network byte order)
 * RETURNS:
 *     Pointer to NDIS packet, NULL if there is not enough free resources
 */
{
    PNDIS_PACKET NdisPacket;
    NDIS_STATUS NdisStatus;
    PARP_HEADER Header;
    PVOID DataBuffer;
    ULONG Size, Contig;

    TI_DbgPrint(DEBUG_ARP, ("Called.\n"));

    /* Prepare ARP packet */
    Size = sizeof(ARP_HEADER) +
        2 * LinkAddressLength + /* Hardware address length */
        2 * ProtoAddressLength; /* Protocol address length */
    Size = MAX(Size, IF->MinFrameSize - IF->HeaderSize);

    NdisStatus = AllocatePacketWithBuffer( &NdisPacket, NULL, Size );
    if( !NT_SUCCESS(NdisStatus) ) return NULL;

    GetDataPtr( NdisPacket, 0, (PCHAR *)&DataBuffer, (PUINT)&Contig );
    ASSERT(DataBuffer);

    RtlZeroMemory(DataBuffer, Size);
    Header = (PARP_HEADER)((ULONG_PTR)DataBuffer);
    Header->HWType       = HardwareType;
    Header->ProtoType    = ProtocolType;
    Header->HWAddrLen    = LinkAddressLength;
    Header->ProtoAddrLen = ProtoAddressLength;
    Header->Opcode       = Opcode; /* Already swapped */
    DataBuffer = (PVOID)((ULONG_PTR)Header + sizeof(ARP_HEADER));

    /* Our hardware address */
    RtlCopyMemory(DataBuffer, SenderLinkAddress, LinkAddressLength);
    DataBuffer = (PVOID)((ULONG_PTR)DataBuffer + LinkAddressLength);

    /* Our protocol address */
    RtlCopyMemory(DataBuffer, SenderProtoAddress, ProtoAddressLength);

    if (TargetLinkAddress) {
        DataBuffer = (PVOID)((ULONG_PTR)DataBuffer + ProtoAddressLength);
        /* Target hardware address */
        RtlCopyMemory(DataBuffer, TargetLinkAddress, LinkAddressLength);
        DataBuffer = (PVOID)((ULONG_PTR)DataBuffer + LinkAddressLength);
    } else
        /* Don't care about target hardware address */
        DataBuffer = (PVOID)((ULONG_PTR)DataBuffer + ProtoAddressLength + LinkAddressLength);

    /* Target protocol address */
    RtlCopyMemory(DataBuffer, TargetProtoAddress, ProtoAddressLength);

    return NdisPacket;
}