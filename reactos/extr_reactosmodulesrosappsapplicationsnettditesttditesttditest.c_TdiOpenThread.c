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
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  PKEVENT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalAddress ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenError ; 
 int /*<<< orphan*/  TDI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TdiOpenTransport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TdiQueryAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TdiTransport ; 
 int /*<<< orphan*/  TdiTransportObject ; 
 int /*<<< orphan*/  UDP_DEVICE_NAME ; 

VOID TdiOpenThread(
    PVOID Context)
/*
 * FUNCTION: Open thread
 * ARGUMENTS:
 *     Context = Pointer to context information (event)
 */
{
	NTSTATUS Status;

	TDI_DbgPrint(MAX_TRACE, ("Called.\n"));

	OpenError = TRUE;

	Status = TdiOpenTransport(UDP_DEVICE_NAME, TEST_PORT, &TdiTransport, &TdiTransportObject);

	if (NT_SUCCESS(Status))
		{
			Status = TdiQueryAddress(TdiTransportObject, &LocalAddress);

			if (NT_SUCCESS(Status))
				{
					OpenError = FALSE;
					DbgPrint("Using local IP address 0x%X\n", LocalAddress);
				}
			else
				{
					TDI_DbgPrint(MIN_TRACE, ("Unable to determine local IP address.\n"));
				}
			}
	else
		TDI_DbgPrint(MIN_TRACE, ("Cannot open transport (Status = 0x%X).\n", Status));

	TDI_DbgPrint(MAX_TRACE, ("Setting close event.\n"));

	KeSetEvent((PKEVENT)Context, 0, FALSE);

	TDI_DbgPrint(MIN_TRACE, ("Leaving.\n"));
}