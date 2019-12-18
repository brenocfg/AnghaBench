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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int Type; scalar_t__ Header; int /*<<< orphan*/  MappedHeader; int /*<<< orphan*/ * NdisPacket; scalar_t__ ReturnPacket; } ;
typedef  TYPE_1__* PVOID ;
typedef  TYPE_1__* PIP_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeNdisPacket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  NdisReturnPackets (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  PACKET_BUFFER_TAG ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

VOID DeinitializePacket(
    PVOID Object)
/*
 * FUNCTION: Frees buffers attached to the packet
 * ARGUMENTS:
 *     Object = Pointer to an IP packet structure
 */
{
    PIP_PACKET IPPacket = Object;

    TI_DbgPrint(MAX_TRACE, ("Freeing object: 0x%p\n", Object));

    /* Detect double free */
    ASSERT(IPPacket->Type != 0xFF);
    IPPacket->Type = 0xFF;

    /* Check if there's a packet to free */
    if (IPPacket->NdisPacket != NULL)
    {
        if (IPPacket->ReturnPacket)
        {
            /* Return the packet to the miniport driver */
            TI_DbgPrint(MAX_TRACE, ("Returning packet 0x%p\n",
                                    IPPacket->NdisPacket));
            NdisReturnPackets(&IPPacket->NdisPacket, 1);
        }
        else
        {
            /* Free it the conventional way */
            TI_DbgPrint(MAX_TRACE, ("Freeing packet 0x%p\n",
                                    IPPacket->NdisPacket));
            FreeNdisPacket(IPPacket->NdisPacket);
        }
    }

    /* Check if we have a pool-allocated header */
    if (!IPPacket->MappedHeader && IPPacket->Header)
    {
        /* Free it */
        TI_DbgPrint(MAX_TRACE, ("Freeing header: 0x%p\n",
                                IPPacket->Header));
        ExFreePoolWithTag(IPPacket->Header,
                          PACKET_BUFFER_TAG);
    }
}