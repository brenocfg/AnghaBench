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
typedef  int /*<<< orphan*/  PLAN_ADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  IPDestroyInterface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPUnregisterInterface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Loopback ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

NDIS_STATUS LoopUnregisterAdapter(
  PLAN_ADAPTER Adapter)
/*
 * FUNCTION: Unregisters loopback adapter with the network layer
 * ARGUMENTS:
 *   Adapter = Unused
 * RETURNS:
 *   Status of operation
 * NOTES:
 *   Does not care wether we have registered loopback adapter
 */
{
  TI_DbgPrint(MID_TRACE, ("Called.\n"));

  if (Loopback != NULL)
    {
      IPUnregisterInterface(Loopback);
      IPDestroyInterface(Loopback);
      Loopback = NULL;
    }

  TI_DbgPrint(MAX_TRACE, ("Leaving.\n"));

  return NDIS_STATUS_SUCCESS;
}