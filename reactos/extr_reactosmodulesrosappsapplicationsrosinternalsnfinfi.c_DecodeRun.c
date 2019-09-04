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
typedef  scalar_t__ ULONGLONG ;
typedef  int ULONG64 ;
typedef  int UCHAR ;
typedef  int* PUCHAR ;
typedef  int LONGLONG ;
typedef  int LONG64 ;
typedef  int CHAR ;

/* Variables and functions */

PUCHAR DecodeRun(PUCHAR DataRun, LONGLONG *DataRunOffset, ULONGLONG *DataRunLength)
{
    UCHAR DataRunOffsetSize;
    UCHAR DataRunLengthSize;
    CHAR i;

    /* Get the offset size (in bytes) of the run */
    DataRunOffsetSize = (*DataRun >> 4) & 0xF;
    /* Get the length size (in bytes) of the run */
    DataRunLengthSize = *DataRun & 0xF;

    /* Initialize values */
    *DataRunOffset = 0;
    *DataRunLength = 0;

    /* Move to next byte */
    DataRun++;

    /* First, extract (byte after byte) run length with the size extracted from header */
    for (i = 0; i < DataRunLengthSize; i++)
    {
        *DataRunLength += ((ULONG64)*DataRun) << (i * 8);
        /* Next byte */
        DataRun++;
    }

    /* If offset size is 0, return -1 to show that's sparse run */
    if (DataRunOffsetSize == 0)
    {
        *DataRunOffset = -1;
    }
    /* Otherwise, extract offset */
    else
    {
        /* Extract (byte after byte) run offset with the size extracted from header */
        for (i = 0; i < DataRunOffsetSize - 1; i++)
        {
            *DataRunOffset += ((ULONG64)*DataRun) << (i * 8);
            /* Next byte */
            DataRun++;
        }
        /* The last byte contains sign so we must process it different way. */
        *DataRunOffset = ((LONG64)(CHAR)(*(DataRun++)) << (i * 8)) + *DataRunOffset;
    }

    /* Return next run */
    return DataRun;
}