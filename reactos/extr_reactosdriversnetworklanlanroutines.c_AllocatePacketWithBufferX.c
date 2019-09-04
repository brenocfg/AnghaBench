#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  PNDIS_PACKET ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  scalar_t__ NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  FreeNdisPacket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalBufferPool ; 
 int /*<<< orphan*/  GlobalPacketPool ; 
 int /*<<< orphan*/  NDIS_BUFFER_TAG ; 
 int /*<<< orphan*/  NDIS_PACKET_TAG ; 
 scalar_t__ NDIS_STATUS_NOT_ACCEPTED ; 
 scalar_t__ NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  NdisAllocateBuffer (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisAllocatePacket (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisChainBufferAtFront (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TrackWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exAllocatePool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exFreePool (int /*<<< orphan*/ ) ; 

NDIS_STATUS AllocatePacketWithBufferX( PNDIS_PACKET *NdisPacket,
				       PCHAR Data, UINT Len,
				       PCHAR File, UINT Line ) {
    PNDIS_PACKET Packet;
    PNDIS_BUFFER Buffer;
    NDIS_STATUS Status;
    PCHAR NewData;

    NewData = exAllocatePool( NonPagedPool, Len );
    if( !NewData ) return NDIS_STATUS_NOT_ACCEPTED; // XXX

    if( Data )
	RtlCopyMemory(NewData, Data, Len);

    NdisAllocatePacket( &Status, &Packet, GlobalPacketPool );
    if( Status != NDIS_STATUS_SUCCESS ) {
	exFreePool( NewData );
	return Status;
    }
    TrackWithTag(NDIS_PACKET_TAG, Packet, File, Line);

    NdisAllocateBuffer( &Status, &Buffer, GlobalBufferPool, NewData, Len );
    if( Status != NDIS_STATUS_SUCCESS ) {
	exFreePool( NewData );
	FreeNdisPacket( Packet );
    }
    TrackWithTag(NDIS_BUFFER_TAG, Buffer, File, Line);

    NdisChainBufferAtFront( Packet, Buffer );
    *NdisPacket = Packet;

    return NDIS_STATUS_SUCCESS;
}