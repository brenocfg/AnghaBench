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
struct TYPE_3__ {scalar_t__ IOBase; } ;
typedef  TYPE_1__* PNIC_ADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  NdisRawWritePortUchar (scalar_t__,int) ; 
 scalar_t__ PG0_RCR ; 
 scalar_t__ PG0_TCR ; 
 int RCR_AB ; 
 int RCR_AM ; 
 int RCR_PRO ; 

NDIS_STATUS NICStart(
    PNIC_ADAPTER Adapter)
/*
 * FUNCTION: Starts a NIC
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 * RETURNS:
 *     Status of operation
 */
{
    NDIS_DbgPrint(MAX_TRACE, ("Called.\n"));

    /* Take NIC out of loopback mode */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_TCR, 0x00);

    /* Initialize RCR - Receive Configuration Register (accept all) */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_RCR, RCR_AB | RCR_AM | RCR_PRO);

    return NDIS_STATUS_SUCCESS;
}