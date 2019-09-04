#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {scalar_t__ MappedSystemVa; int /*<<< orphan*/  ByteCount; int /*<<< orphan*/  ByteOffset; } ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  PNDIS_PACKET ;
typedef  TYPE_1__* PNDIS_BUFFER ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PBUFFER ; 
 int /*<<< orphan*/  NdisQueryPacket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

PVOID AdjustPacket(
    PNDIS_PACKET Packet,
    UINT Available,
    UINT Needed)
/*
 * FUNCTION: Adjusts the amount of unused space at the beginning of the packet
 * ARGUMENTS:
 *     Packet    = Pointer to packet
 *     Available = Number of bytes available at start of first buffer
 *     Needed    = Number of bytes needed for the header
 * RETURNS:
 *     Pointer to start of packet
 */
{
    PNDIS_BUFFER NdisBuffer;
    INT Adjust;

    TI_DbgPrint(DEBUG_PBUFFER, ("Available = %d, Needed = %d.\n", Available, Needed));

    Adjust = Available - Needed;

    NdisQueryPacket(Packet, NULL, NULL, &NdisBuffer, NULL);

    /* If Adjust is zero there is no need to adjust this packet as
       there is no additional space at start the of first buffer */
    if (Adjust != 0) {
        NdisBuffer->MappedSystemVa  = (PVOID) ((ULONG_PTR)(NdisBuffer->MappedSystemVa) + Adjust);
        NdisBuffer->ByteOffset     += Adjust;
        NdisBuffer->ByteCount      -= Adjust;
    }

    return NdisBuffer->MappedSystemVa;
}