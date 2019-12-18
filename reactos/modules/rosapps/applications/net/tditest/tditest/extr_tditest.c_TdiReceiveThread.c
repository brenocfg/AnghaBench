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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  Data ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 scalar_t__ NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  OpenError ; 
 int /*<<< orphan*/  PsTerminateSystemThread (scalar_t__) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,int) ; 
 scalar_t__ STATUS_CANCELLED ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  TDI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TEST_PORT ; 
 scalar_t__ TdiReceiveDatagram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  TdiTransportObject ; 

VOID TdiReceiveThread(
    PVOID Context)
/*
 * FUNCTION: Receive thread
 * ARGUMENTS:
 *     Context = Pointer to context information
 * NOTES:
 *     Waits until an UDP packet is received on the chosen endpoint and displays the data
 */
{
	ULONG Address;
	UCHAR Data[40];
	ULONG Size;
	NTSTATUS Status = STATUS_SUCCESS;

	if (!OpenError)
		{
			while (NT_SUCCESS(Status))
				{
					Size = sizeof(Data);
					RtlZeroMemory(Data, Size);

					Status = TdiReceiveDatagram(TdiTransportObject, TEST_PORT, &Address, Data, &Size);

					if (NT_SUCCESS(Status))
						{
							DbgPrint("Received data - '%s'\n", Data);
						}
					else
						if (Status != STATUS_CANCELLED)
							{
								TDI_DbgPrint(MIN_TRACE, ("Receive error (Status = 0x%X).\n", Status));
							}
						else
							{
								TDI_DbgPrint(MAX_TRACE, ("IRP was cancelled.\n"));
							}
				}
		}

	TDI_DbgPrint(MAX_TRACE, ("Terminating receive thread...\n"));

	PsTerminateSystemThread(STATUS_SUCCESS);
}