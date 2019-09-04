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
typedef  scalar_t__* PUINT ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;
typedef  scalar_t__ PCHAR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  NdisGetNextBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XNdisQueryBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__inline INT SkipToOffset(
    PNDIS_BUFFER Buffer,
    UINT Offset,
    PCHAR *Data,
    PUINT Size)
/*
 * FUNCTION: Skip Offset bytes into a buffer chain
 * ARGUMENTS:
 *     Buffer = Pointer to NDIS buffer
 *     Offset = Number of bytes to skip
 *     Data   = Address of a pointer that on return will contain the
 *              address of the offset in the buffer
 *     Size   = Address of a pointer that on return will contain the
 *              size of the destination buffer
 * RETURNS:
 *     Offset into buffer, -1 if buffer chain was smaller than Offset bytes
 * NOTES:
 *     Buffer may be NULL
 */
{
    for (;;) {

        if (!Buffer)
            return -1;

        XNdisQueryBuffer(Buffer, (PVOID)Data, Size);

        if (Offset < *Size) {
            *Data = (PCHAR)((ULONG_PTR) *Data + Offset);
            *Size              -= Offset;
            break;
        }

        Offset -= *Size;

        NdisGetNextBuffer(Buffer, &Buffer);
    }

    return Offset;
}