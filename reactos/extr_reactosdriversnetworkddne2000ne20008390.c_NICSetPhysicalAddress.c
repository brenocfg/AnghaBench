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
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
struct TYPE_3__ {int* StationAddress; scalar_t__ IOBase; } ;
typedef  TYPE_1__* PNIC_ADAPTER ;

/* Variables and functions */
 int CR_PAGE0 ; 
 int CR_PAGE1 ; 
 int CR_RD2 ; 
 int CR_STP ; 
 int /*<<< orphan*/  NdisRawWritePortUchar (scalar_t__,int) ; 
 scalar_t__ PG0_CR ; 
 scalar_t__ PG1_PAR ; 

__attribute__((used)) static VOID NICSetPhysicalAddress(
    PNIC_ADAPTER Adapter)
/*
 * FUNCTION: Initializes the physical address on the NIC
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 * NOTES:
 *     The physical address is taken from Adapter.
 *     The NIC is stopped by this operation
 */
{
    UINT i;

    /* Select page 1 */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_CR, CR_STP | CR_RD2 | CR_PAGE1);

    /* Initialize PAR - Physical Address Registers */
    for (i = 0; i < 0x06; i++)
        NdisRawWritePortUchar(Adapter->IOBase + PG1_PAR + i, Adapter->StationAddress[i]);

    /* Go back to page 0 */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_CR, CR_STP | CR_RD2 | CR_PAGE0);
}