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
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ PUCHAR ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TRACE ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NdisGetNextBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisQueryBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int SkipToOffset (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*) ; 

UINT CopyBufferChainToBuffer(
    PUCHAR DstData,
    PNDIS_BUFFER SrcBuffer,
    UINT SrcOffset,
    UINT Length)
/*
 * FUNCTION: Copies data from an NDIS buffer chain to a buffer
 * ARGUMENTS:
 *     DstData   = Pointer to destination buffer
 *     SrcBuffer = Pointer to source NDIS buffer
 *     SrcOffset = Source start offset
 *     Length    = Number of bytes to copy
 * RETURNS:
 *     Number of bytes copied to destination buffer
 * NOTES:
 *     The number of bytes copied may be limited by the source
 *     buffer size
 */
{
    UINT BytesCopied, BytesToCopy, SrcSize;
    PUCHAR SrcData;

    NDIS_DbgPrint(MAX_TRACE, ("DstData 0x%X  SrcBuffer 0x%X  SrcOffset 0x%X  Length %d\n",DstData,SrcBuffer, SrcOffset, Length));

    /* Skip SrcOffset bytes in the source buffer chain */
    if (SkipToOffset(SrcBuffer, SrcOffset, &SrcData, &SrcSize) == 0xFFFFFFFF)
        return 0;

    /* Start copying the data */
    BytesCopied = 0;
    for (;;) {
        BytesToCopy = MIN(SrcSize, Length);

        NDIS_DbgPrint(MAX_TRACE, ("Copying (%d) bytes from 0x%X to 0x%X\n", BytesToCopy, SrcData, DstData));

        RtlCopyMemory((PVOID)DstData, (PVOID)SrcData, BytesToCopy);
        BytesCopied += BytesToCopy;
        DstData      = (PUCHAR)((ULONG_PTR) DstData + BytesToCopy);

        Length -= BytesToCopy;
        if (Length == 0)
            break;

        SrcSize -= BytesToCopy;
        if (SrcSize == 0) {
            /* No more bytes in source buffer. Proceed to
               the next buffer in the source buffer chain */
            NdisGetNextBuffer(SrcBuffer, &SrcBuffer);
            if (!SrcBuffer)
                break;

            NdisQueryBuffer(SrcBuffer, (PVOID)&SrcData, &SrcSize);
        }
    }

    return BytesCopied;
}