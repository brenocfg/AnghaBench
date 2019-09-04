#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_13__ {int /*<<< orphan*/  ReceiveQueue; } ;
struct TYPE_12__ {int /*<<< orphan*/  ListEntry; int /*<<< orphan*/  Irp; TYPE_3__* AddressFile; struct TYPE_12__* Context; void* Complete; int /*<<< orphan*/  UserContext; void* UserComplete; int /*<<< orphan*/  BufferSize; int /*<<< orphan*/  Buffer; TYPE_1__* ReturnInfo; int /*<<< orphan*/  RemoteAddress; scalar_t__ RemotePort; } ;
struct TYPE_11__ {scalar_t__ RemoteAddressLength; scalar_t__ RemoteAddress; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PULONG ;
typedef  TYPE_1__* PTDI_CONNECTION_INFORMATION ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  TYPE_2__* PDATAGRAM_RECEIVE_REQUEST ;
typedef  void* PDATAGRAM_COMPLETION_ROUTINE ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  TYPE_3__* PADDRESS_FILE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KIRQL ;
typedef  int /*<<< orphan*/  DATAGRAM_RECEIVE_REQUEST ;

/* Variables and functions */
 int /*<<< orphan*/  AddrGetAddress (scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  AddrInitIPv4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DATAGRAM_RECV_TAG ; 
 scalar_t__ DGReceiveComplete ; 
 TYPE_2__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoMarkIrpPending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockObject (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_PENDING ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UnlockObject (TYPE_3__*,int /*<<< orphan*/ ) ; 

NTSTATUS DGReceiveDatagram(
    PADDRESS_FILE AddrFile,
    PTDI_CONNECTION_INFORMATION ConnInfo,
    PCHAR BufferData,
    ULONG ReceiveLength,
    ULONG ReceiveFlags,
    PTDI_CONNECTION_INFORMATION ReturnInfo,
    PULONG BytesReceived,
    PDATAGRAM_COMPLETION_ROUTINE Complete,
    PVOID Context,
    PIRP Irp)
/*
 * FUNCTION: Attempts to receive an DG datagram from a remote address
 * ARGUMENTS:
 *     Request       = Pointer to TDI request
 *     ConnInfo      = Pointer to connection information
 *     Buffer        = Pointer to NDIS buffer chain to store received data
 *     ReceiveLength = Maximum size to use of buffer, 0 if all can be used
 *     ReceiveFlags  = Receive flags (None, Normal, Peek)
 *     ReturnInfo    = Pointer to structure for return information
 *     BytesReceive  = Pointer to structure for number of bytes received
 * RETURNS:
 *     Status of operation
 * NOTES:
 *     This is the high level interface for receiving DG datagrams
 */
{
    NTSTATUS Status;
    PDATAGRAM_RECEIVE_REQUEST ReceiveRequest;
    KIRQL OldIrql;

    TI_DbgPrint(MAX_TRACE, ("Called.\n"));

    LockObject(AddrFile, &OldIrql);

    ReceiveRequest = ExAllocatePoolWithTag(NonPagedPool, sizeof(DATAGRAM_RECEIVE_REQUEST),
                                           DATAGRAM_RECV_TAG);
    if (ReceiveRequest)
    {
	/* Initialize a receive request */

	/* Extract the remote address filter from the request (if any) */
	if ((ConnInfo->RemoteAddressLength != 0) &&
	    (ConnInfo->RemoteAddress))
        {
	    Status = AddrGetAddress(ConnInfo->RemoteAddress,
				    &ReceiveRequest->RemoteAddress,
				    &ReceiveRequest->RemotePort);
	    if (!NT_SUCCESS(Status))
            {
		ExFreePoolWithTag(ReceiveRequest, DATAGRAM_RECV_TAG);
	        UnlockObject(AddrFile, OldIrql);
		return Status;
            }
	}
	else
        {
	    ReceiveRequest->RemotePort = 0;
	    AddrInitIPv4(&ReceiveRequest->RemoteAddress, 0);
        }

	IoMarkIrpPending(Irp);

	ReceiveRequest->ReturnInfo = ReturnInfo;
	ReceiveRequest->Buffer = BufferData;
	ReceiveRequest->BufferSize = ReceiveLength;
	ReceiveRequest->UserComplete = Complete;
	ReceiveRequest->UserContext = Context;
	ReceiveRequest->Complete =
		(PDATAGRAM_COMPLETION_ROUTINE)DGReceiveComplete;
	ReceiveRequest->Context = ReceiveRequest;
        ReceiveRequest->AddressFile = AddrFile;
        ReceiveRequest->Irp = Irp;

	/* Queue receive request */
	InsertTailList(&AddrFile->ReceiveQueue, &ReceiveRequest->ListEntry);

	TI_DbgPrint(MAX_TRACE, ("Leaving (pending %08x).\n", ReceiveRequest));

	UnlockObject(AddrFile, OldIrql);

	return STATUS_PENDING;
    }
    else
    {
	UnlockObject(AddrFile, OldIrql);
        Status = STATUS_INSUFFICIENT_RESOURCES;
    }

    TI_DbgPrint(MAX_TRACE, ("Leaving with errors (0x%X).\n", Status));

    return Status;
}