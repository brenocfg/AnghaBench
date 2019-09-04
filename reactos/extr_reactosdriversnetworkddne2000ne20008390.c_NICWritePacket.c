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
typedef  int ULONG_PTR ;
typedef  int ULONG ;
typedef  int UINT ;
struct TYPE_4__ {int TXStart; int TXCount; size_t TXNext; int /*<<< orphan*/ * TXSize; int /*<<< orphan*/  TXQueueHead; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ PUCHAR ;
typedef  TYPE_1__* PNIC_ADAPTER ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;

/* Variables and functions */
 int DRIVER_BLOCK_SIZE ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NICWriteData (TYPE_1__*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  NdisGetNextBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisQueryBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  NdisQueryPacket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VOID NICWritePacket(
    PNIC_ADAPTER Adapter)
/*
 * FUNCTION: Writes a full packet to the transmit buffer ring
 * ARGUMENTS:
 *     Adapter  = Pointer to adapter information
 * NOTES:
 *     There must be enough free buffers available in the transmit buffer ring.
 *     The packet is taken from the head of the transmit queue and the position
 *     into the transmit buffer ring is taken from TXNext
 */
{
    PNDIS_BUFFER SrcBuffer;
    UINT BytesToCopy, SrcSize, DstSize;
    PUCHAR SrcData;
    ULONG DstData;
    UINT TXStart;
    UINT TXStop;

    NDIS_DbgPrint(MAX_TRACE, ("Called.\n"));

    TXStart = Adapter->TXStart * DRIVER_BLOCK_SIZE;
    TXStop  = (Adapter->TXStart + Adapter->TXCount) * DRIVER_BLOCK_SIZE;

    NdisQueryPacket(Adapter->TXQueueHead,
                    NULL,
                    NULL,
                    &SrcBuffer,
                    &Adapter->TXSize[Adapter->TXNext]);

    NDIS_DbgPrint(MID_TRACE, ("Packet (%d) is now size (%d).\n",
        Adapter->TXNext,
        Adapter->TXSize[Adapter->TXNext]));

    NdisQueryBuffer(SrcBuffer, (PVOID)&SrcData, &SrcSize);

    DstData = TXStart + Adapter->TXNext * DRIVER_BLOCK_SIZE;
    DstSize = TXStop - DstData;

    /* Start copying the data */
    for (;;) {
        BytesToCopy = (SrcSize < DstSize)? SrcSize : DstSize;

        NICWriteData(Adapter, DstData, SrcData, BytesToCopy);

        SrcData = (PUCHAR)((ULONG_PTR) SrcData + BytesToCopy);
        SrcSize            -= BytesToCopy;
        DstData            += BytesToCopy;
        DstSize            -= BytesToCopy;

        if (SrcSize == 0) {
            /* No more bytes in source buffer. Proceed to
               the next buffer in the source buffer chain */
            NdisGetNextBuffer(SrcBuffer, &SrcBuffer);
            if (!SrcBuffer)
                break;

            NdisQueryBuffer(SrcBuffer, (PVOID)&SrcData, &SrcSize);
        }

        if (DstSize == 0) {
            /* Wrap around the end of the transmit buffer ring */
            DstData = TXStart;
            DstSize = Adapter->TXCount * DRIVER_BLOCK_SIZE;
        }
    }
}