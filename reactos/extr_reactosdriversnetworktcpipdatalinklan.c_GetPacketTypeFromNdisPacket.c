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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  HeaderSize; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PULONG ;
typedef  int /*<<< orphan*/  PNDIS_PACKET ;
typedef  TYPE_1__* PLAN_ADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  CopyPacketToBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_DATALINK ; 
 int /*<<< orphan*/  ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetPacketTypeFromHeaderBuffer (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEADER_TAG ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_RESOURCES ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

NDIS_STATUS
GetPacketTypeFromNdisPacket(PLAN_ADAPTER Adapter,
                            PNDIS_PACKET NdisPacket,
                            PULONG PacketType)
{
    PVOID HeaderBuffer;
    ULONG BytesCopied;
    NDIS_STATUS Status;
    
    HeaderBuffer = ExAllocatePoolWithTag(NonPagedPool,
                                         Adapter->HeaderSize,
                                         HEADER_TAG);
    if (!HeaderBuffer)
        return NDIS_STATUS_RESOURCES;
    
    /* Copy the media header */
    BytesCopied = CopyPacketToBuffer(HeaderBuffer,
                                     NdisPacket,
                                     0,
                                     Adapter->HeaderSize);
    if (BytesCopied != Adapter->HeaderSize)
    {
        /* Runt frame */
        ExFreePoolWithTag(HeaderBuffer, HEADER_TAG);
        TI_DbgPrint(DEBUG_DATALINK, ("Runt frame (size %d).\n", BytesCopied));
        return NDIS_STATUS_NOT_ACCEPTED;
    }

    Status = GetPacketTypeFromHeaderBuffer(Adapter,
                                           HeaderBuffer,
                                           BytesCopied,
                                           PacketType);
    
    ExFreePoolWithTag(HeaderBuffer, HEADER_TAG);
    
    return Status;
}