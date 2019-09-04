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
typedef  int USHORT ;
typedef  int ULONG_PTR ;
typedef  scalar_t__ UCHAR ;
typedef  int* PUSHORT ;
typedef  scalar_t__* PUCHAR ;
typedef  int /*<<< orphan*/  PNIC_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  NICReadDataAlign (int /*<<< orphan*/ ,int*,int,int) ; 

VOID NICReadData(
    PNIC_ADAPTER Adapter,
    PUCHAR Target,
    ULONG_PTR Source,
    USHORT Length)
/*
 * FUNCTION: Copies data from a NIC's RAM into a buffer
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 *     Target  = Pointer to buffer to copy data into (in host memory)
 *     Source  = Offset into NIC's RAM
 *     Length  = Number of bytes to copy from NIC's RAM
 */
{
    USHORT Tmp;

    /* Avoid transfers to odd addresses */
    if (Source & 0x01) {
        /* Transfer one word and use the MSB */
        NICReadDataAlign(Adapter, &Tmp, Source - 1, 0x02);
        *Target = (UCHAR)(Tmp >> 8);
        Source++;
        Target++;
        Length--;
    }

    if (Length & 0x01) {
        /* Transfer as many words as we can without exceeding the buffer length */
        Tmp = Length & 0xFFFE;
        NICReadDataAlign(Adapter, (PUSHORT)Target, Source, Tmp);
        Source += Tmp;
        Target  = (PUCHAR)((ULONG_PTR) Target + Tmp);

        /* Read one word and keep the LSB */
        NICReadDataAlign(Adapter, &Tmp, Source, 0x02);
        *Target = (UCHAR)(Tmp & 0x00FF);
    } else
        /* Transfer the rest of the data */
        NICReadDataAlign(Adapter, (PUSHORT)Target, Source, Length);
}