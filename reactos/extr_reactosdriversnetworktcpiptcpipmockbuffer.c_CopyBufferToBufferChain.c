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
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;
typedef  scalar_t__ PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PBUFFER ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  NdisGetNextBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int SkipToOffset (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XNdisQueryBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

UINT CopyBufferToBufferChain(
    PNDIS_BUFFER DstBuffer,
    UINT DstOffset,
    PCHAR SrcData,
    UINT Length)
/*
 * FUNCTION: Copies data from a buffer to an NDIS buffer chain
 * ARGUMENTS:
 *     DstBuffer = Pointer to destination NDIS buffer
 *     DstOffset = Destination start offset
 *     SrcData   = Pointer to source buffer
 *     Length    = Number of bytes to copy
 * RETURNS:
 *     Number of bytes copied to destination buffer
 * NOTES:
 *     The number of bytes copied may be limited by the destination
 *     buffer size
 */
{
    UINT BytesCopied, BytesToCopy, DstSize;
    PCHAR DstData;

    TI_DbgPrint(DEBUG_PBUFFER, ("DstBuffer (0x%X)  DstOffset (0x%X)  SrcData (0x%X)  Length (%d)\n", DstBuffer, DstOffset, SrcData, Length));

    /* Skip DstOffset bytes in the destination buffer chain */
    if (SkipToOffset(DstBuffer, DstOffset, &DstData, &DstSize) == -1)
        return 0;

    /* Start copying the data */
    BytesCopied = 0;
    for (;;) {
        BytesToCopy = MIN(DstSize, Length);

        RtlCopyMemory((PVOID)DstData, (PVOID)SrcData, BytesToCopy);
        BytesCopied += BytesToCopy;
        SrcData      = (PCHAR)((ULONG_PTR)SrcData + BytesToCopy);

        Length -= BytesToCopy;
        if (Length == 0)
            break;

        DstSize -= BytesToCopy;
        if (DstSize == 0) {
            /* No more bytes in destination buffer. Proceed to
               the next buffer in the destination buffer chain */
            NdisGetNextBuffer(DstBuffer, &DstBuffer);
            if (!DstBuffer)
                break;

            XNdisQueryBuffer(DstBuffer, (PVOID)&DstData, &DstSize);
        }
    }

    return BytesCopied;
}