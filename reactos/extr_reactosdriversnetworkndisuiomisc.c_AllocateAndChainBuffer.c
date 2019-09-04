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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  BufferPoolHandle; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PNDIS_PACKET ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;
typedef  TYPE_1__* PNDISUIO_ADAPTER_CONTEXT ;
typedef  scalar_t__ NDIS_STATUS ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  NdisAllocateBuffer (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisChainBufferAtBack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisChainBufferAtFront (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NDIS_STATUS
AllocateAndChainBuffer(PNDISUIO_ADAPTER_CONTEXT AdapterContext,
                       PNDIS_PACKET Packet,
                       PVOID Buffer,
                       ULONG BufferSize,
                       BOOLEAN Front)
{
    NDIS_STATUS Status;
    PNDIS_BUFFER NdisBuffer;

    /* Allocate the NDIS buffer mapping the pool */
    NdisAllocateBuffer(&Status,
                       &NdisBuffer,
                       AdapterContext->BufferPoolHandle,
                       Buffer,
                       BufferSize);
    if (Status != NDIS_STATUS_SUCCESS)
    {
        DPRINT1("No free buffer descriptors\n");
        return Status;
    }

    if (Front)
    {
        /* Chain the buffer to front */
        NdisChainBufferAtFront(Packet, NdisBuffer);
    }
    else
    {
        /* Chain the buffer to back */
        NdisChainBufferAtBack(Packet, NdisBuffer);
    }

    /* Return success */
    return NDIS_STATUS_SUCCESS;
}