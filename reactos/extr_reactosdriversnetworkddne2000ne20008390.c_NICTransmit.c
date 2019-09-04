#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int TXCurrent; } ;
typedef  TYPE_1__* PNIC_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ NICPrepareForTransmit (TYPE_1__*) ; 
 int /*<<< orphan*/  NICStartTransmit (TYPE_1__*) ; 

VOID NICTransmit(
    PNIC_ADAPTER Adapter)
/*
 * FUNCTION: Starts transmitting packets in the transmit queue
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 * NOTES:
 *     There must be at least one packet in the transmit queue
 */
{
    NDIS_DbgPrint(MAX_TRACE, ("Called.\n"));

    if (Adapter->TXCurrent == -1) {
        /* NIC is not transmitting, so start transmitting now */

        /* Load next packet onto the card, and start transmitting */
        if (NICPrepareForTransmit(Adapter))
            NICStartTransmit(Adapter);
    }
}