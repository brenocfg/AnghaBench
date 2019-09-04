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
typedef  int* PUSHORT ;
typedef  int* PUCHAR ;
typedef  int /*<<< orphan*/  PNIC_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  NICReadDataAlign (int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  NICWriteDataAlign (int /*<<< orphan*/ ,int,int*,int) ; 

VOID NICWriteData(
    PNIC_ADAPTER Adapter,
    ULONG_PTR Target,
    PUCHAR Source,
    USHORT Length)
/*
 * FUNCTION: Copies data from a buffer into NIC's RAM
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 *     Target  = Offset into NIC's RAM to store data
 *     Source  = Pointer to buffer to copy data from (in host memory)
 *     Length  = Number of bytes to copy from buffer
 */
{
    USHORT Tmp;

    /* Avoid transfers to odd addresses */
    if (Target & 0x01) {
        /* Read one word */
        NICReadDataAlign(Adapter, &Tmp, Target - 1, 0x02);

        /* Merge LSB with the new byte which become the new MSB */
        Tmp = (Tmp & 0x00FF) | (*Source << 8);

        /* Finally write the value back */
        NICWriteDataAlign(Adapter, Target - 1, &Tmp, 0x02);

        /* Update pointers */
        Source = (PUCHAR) ((ULONG_PTR) Source + 1);
        Target += 1;
        Length--;
    }

    if (Length & 0x01) {
        /* Transfer as many words as we can without exceeding the transfer length */
        Tmp = Length & 0xFFFE;
        NICWriteDataAlign(Adapter, Target, (PUSHORT)Source, Tmp);
        Source += Tmp;
        Target += Tmp;

        /* Read one word */
        NICReadDataAlign(Adapter, &Tmp, Target, 0x02);

        /* Merge MSB with the new byte which become the new LSB */
        Tmp = (Tmp & 0xFF00) | (*Source);

        /* Finally write the value back */
        NICWriteDataAlign(Adapter, Target, &Tmp, 0x02);
    } else
        /* Transfer the rest of the data */
        NICWriteDataAlign(Adapter, Target, (PUSHORT)Source, Length);
}