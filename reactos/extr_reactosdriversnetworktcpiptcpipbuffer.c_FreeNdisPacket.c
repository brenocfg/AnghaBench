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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PNDIS_PACKET ;
typedef  int /*<<< orphan*/ * PNDIS_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PBUFFER ; 
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisFreeBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisFreePacket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisGetNextBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  NdisQueryBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisQueryPacket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_BUFFER_TAG ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

VOID FreeNdisPacket
( PNDIS_PACKET Packet )
/*
 * FUNCTION: Frees an NDIS packet
 * ARGUMENTS:
 *     Packet = Pointer to NDIS packet to be freed
 */
{
    PNDIS_BUFFER Buffer, NextBuffer;

    TI_DbgPrint(DEBUG_PBUFFER, ("Packet (0x%X)\n", Packet));

    /* Free all the buffers in the packet first */
    NdisQueryPacket(Packet, NULL, NULL, &Buffer, NULL);
    for (; Buffer != NULL; Buffer = NextBuffer) {
        PVOID Data;
        UINT Length;

        NdisGetNextBuffer(Buffer, &NextBuffer);
        NdisQueryBuffer(Buffer, &Data, &Length);
	TI_DbgPrint(DEBUG_PBUFFER, ("Freeing ndis buffer (0x%X)\n", Buffer));
        NdisFreeBuffer(Buffer);
	TI_DbgPrint(DEBUG_PBUFFER, ("Freeing exal buffer (0x%X)\n", Data));
        ExFreePoolWithTag(Data, PACKET_BUFFER_TAG);
    }

    /* Finally free the NDIS packet descriptor */
    NdisFreePacket(Packet);
}