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
typedef  int UINT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_3__ {void* WordMode; scalar_t__ IOBase; scalar_t__* SAPROM; int /*<<< orphan*/  PermanentAddress; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PNIC_ADAPTER ;
typedef  void* BOOLEAN ;

/* Variables and functions */
 int CR_PAGE0 ; 
 int CR_RD0 ; 
 int CR_STA ; 
 int DCR_FT10 ; 
 int DCR_LS ; 
 int DCR_WTS ; 
 int /*<<< orphan*/  DRIVER_LENGTH_OF_ADDRESS ; 
 void* FALSE ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ NIC_DATA ; 
 int /*<<< orphan*/  NdisMoveMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisRawReadPortUchar (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  NdisRawWritePortUchar (scalar_t__,int) ; 
 scalar_t__ PG0_CR ; 
 scalar_t__ PG0_DCR ; 
 scalar_t__ PG0_RBCR0 ; 
 scalar_t__ PG0_RBCR1 ; 
 scalar_t__ PG0_RSAR0 ; 
 scalar_t__ PG0_RSAR1 ; 
 void* TRUE ; 

__attribute__((used)) static BOOLEAN NICReadSAPROM(
    PNIC_ADAPTER Adapter)
/*
 * FUNCTION: Reads the Station Address PROM data from the NIC
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 * RETURNS:
 *     TRUE if a the NIC is an NE2000
 * NOTES:
 *    This routine also determines if the NIC can support word mode transfers
 *    and if it does initializes the NIC for word mode.
 *    The station address in the adapter structure is initialized with
 *    the address from the SAPROM
 */
{
    UINT i;
    UCHAR Buffer[32];
    UCHAR WordLength;

    NDIS_DbgPrint(MAX_TRACE, ("Called.\n"));

    /* Read Station Address PROM (SAPROM) which is 16 bytes at remote DMA address 0.
       Some cards double the data read which we must compensate for */

    /* Initialize RBCR0 and RBCR1 - Remote Byte Count Registers */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RBCR0, 0x20);
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RBCR1, 0x00);

    /* Initialize RSAR0 and RSAR1 - Remote Start Address Registers */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RSAR0, 0x00);
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RSAR1, 0x00);

    /* Select page 0, read and start the NIC */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_CR, CR_STA | CR_RD0 | CR_PAGE0);

    /* Read one byte at a time */
    WordLength = 2; /* Assume a word is two bytes */
    for (i = 0; i < 32; i += 2) {
        NdisRawReadPortUchar(Adapter->IOBase + NIC_DATA, &Buffer[i]);
        NdisRawReadPortUchar(Adapter->IOBase + NIC_DATA, &Buffer[i + 1]);
		if (Buffer[i] != Buffer[i + 1])
			WordLength = 1; /* A word is one byte long */
	}

    /* If WordLength is 2 the data read before was doubled. We must compensate for this */
    if (WordLength == 2) {
        NDIS_DbgPrint(MAX_TRACE,("NE2000 or compatible network adapter found.\n"));

        Adapter->WordMode = TRUE;

        /* Move the SAPROM data to the adapter object */
        for (i = 0; i < 16; i++)
            Adapter->SAPROM[i] = Buffer[i * 2];

        /* Copy the permanent address */
        NdisMoveMemory(
            (PVOID)&Adapter->PermanentAddress,
            (PVOID)&Adapter->SAPROM,
            DRIVER_LENGTH_OF_ADDRESS);

        /* Initialize DCR - Data Configuration Register (word mode/4 words FIFO) */
        NdisRawWritePortUchar(Adapter->IOBase + PG0_DCR, DCR_WTS | DCR_LS | DCR_FT10);

        return TRUE;
    } else {
        NDIS_DbgPrint(MAX_TRACE, ("NE1000 or compatible network adapter found.\n"));

        Adapter->WordMode = FALSE;

        return FALSE;
    }
}