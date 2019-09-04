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
typedef  char UCHAR ;
struct TYPE_3__ {long QuadPart; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/ * PKEVENT ;
typedef  char* NTSTATUS ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  KEVENT ;
typedef  int /*<<< orphan*/  Data ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,char*) ; 
 int /*<<< orphan*/  Executive ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KeReadStateEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeWaitForMultipleObjects (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  LocalAddress ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 scalar_t__ NT_SUCCESS (char*) ; 
 int /*<<< orphan*/  OpenError ; 
 int /*<<< orphan*/  PsTerminateSystemThread (char*) ; 
 char* STATUS_SUCCESS ; 
 int /*<<< orphan*/  StopEvent ; 
 int /*<<< orphan*/  SynchronizationEvent ; 
 int /*<<< orphan*/  TDI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TEST_PORT ; 
 char* TdiSendDatagram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  TdiTransportObject ; 
 int /*<<< orphan*/  WaitAny ; 

VOID TdiSendThread(
    PVOID Context)
/*
 * FUNCTION: Send thread
 * ARGUMENTS:
 *     Context = Pointer to context information
 * NOTES:
 *     Transmits an UDP packet every two seconds to ourselves on the chosen port
 */
{
	KEVENT Event;
	PKEVENT Events[2];
	LARGE_INTEGER Timeout;
	NTSTATUS Status = STATUS_SUCCESS;
	UCHAR Data[40]  = "Testing one, two, three, ...";

	if (!OpenError)
		{
			Timeout.QuadPart = 10000000L;           /* Second factor */
			Timeout.QuadPart *= 2;                  /* Number of seconds */
			Timeout.QuadPart = -(Timeout.QuadPart); /* Relative time */

			KeInitializeEvent(&Event, SynchronizationEvent, FALSE);

			Events[0] = &StopEvent;
			Events[1] = &Event;

			while (NT_SUCCESS(Status))
				{
					/* Wait until timeout or stop flag is set */
 					KeWaitForMultipleObjects( 2, (PVOID)Events, WaitAny, Executive, KernelMode, FALSE, &Timeout, NULL);

					if (KeReadStateEvent(&StopEvent) != 0)
						{
							TDI_DbgPrint(MAX_TRACE, ("Received terminate signal...\n"));
							break;
						}

					DbgPrint("Sending data - '%s'\n", Data);

					Status = TdiSendDatagram(TdiTransportObject, TEST_PORT, LocalAddress, Data, sizeof(Data));

					if (!NT_SUCCESS(Status))
						DbgPrint("Failed sending data (Status = 0x%X)\n", Status);
				}
		}

	TDI_DbgPrint(MAX_TRACE, ("Terminating send thread...\n"));

	PsTerminateSystemThread(STATUS_SUCCESS);
}