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
struct TYPE_3__ {int State; int /*<<< orphan*/  Interface; int /*<<< orphan*/ * LinkAddress; int /*<<< orphan*/  Address; } ;
typedef  TYPE_1__* PNEIGHBOR_CACHE_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ARPTransmit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_NCACHE ; 
 int NUD_INCOMPLETE ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

VOID NBSendSolicit(PNEIGHBOR_CACHE_ENTRY NCE)
/*
 * FUNCTION: Sends a neighbor solicitation message
 * ARGUMENTS:
 *   NCE = Pointer to NCE of neighbor to solicit
 * NOTES:
 *   May be called with lock held on NCE's table
 */
{
    TI_DbgPrint(DEBUG_NCACHE, ("Called. NCE (0x%X).\n", NCE));

    ARPTransmit(&NCE->Address,
                (NCE->State & NUD_INCOMPLETE) ? NULL : NCE->LinkAddress,
                NCE->Interface);
}