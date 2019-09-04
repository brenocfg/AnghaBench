#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {scalar_t__ HeaderSize; int Media; } ;
struct TYPE_6__ {int /*<<< orphan*/  EType; } ;
typedef  TYPE_1__* PVOID ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  TYPE_2__* PLAN_ADAPTER ;
typedef  TYPE_1__* PETH_HEADER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_DATALINK ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
#define  NdisMedium802_3 128 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

NDIS_STATUS
GetPacketTypeFromHeaderBuffer(PLAN_ADAPTER Adapter,
                              PVOID HeaderBuffer,
                              ULONG HeaderBufferSize,
                              PULONG PacketType)
{
    PETH_HEADER EthHeader = HeaderBuffer;

    if (HeaderBufferSize < Adapter->HeaderSize)
    {
        TI_DbgPrint(DEBUG_DATALINK, ("Runt frame (size %d).\n", HeaderBufferSize));
        return NDIS_STATUS_NOT_ACCEPTED;
    }

    switch (Adapter->Media)
    {
        case NdisMedium802_3:
            /* Ethernet and IEEE 802.3 frames can be distinguished by
               looking at the IEEE 802.3 length field. This field is
               less than or equal to 1500 for a valid IEEE 802.3 frame
               and larger than 1500 is it's a valid EtherType value.
               See RFC 1122, section 2.3.3 for more information */

            *PacketType = EthHeader->EType;
            break;

        default:
            TI_DbgPrint(MIN_TRACE, ("Unsupported media.\n"));

            /* FIXME: Support other medias */
            return NDIS_STATUS_NOT_ACCEPTED;
    }
    
    TI_DbgPrint(DEBUG_DATALINK, ("EtherType (0x%X).\n", *PacketType));
    
    return NDIS_STATUS_SUCCESS;
}