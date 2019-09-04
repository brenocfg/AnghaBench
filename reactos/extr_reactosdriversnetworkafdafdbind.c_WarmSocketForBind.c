#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_16__ {TYPE_1__* Address; } ;
struct TYPE_15__ {int /*<<< orphan*/  Buffer; int /*<<< orphan*/  Length; } ;
struct TYPE_13__ {scalar_t__ Size; scalar_t__ Content; int /*<<< orphan*/  Window; } ;
struct TYPE_12__ {int /*<<< orphan*/  Object; int /*<<< orphan*/  Handle; } ;
struct TYPE_11__ {int /*<<< orphan*/  InFlightRequest; } ;
struct TYPE_14__ {int Flags; int /*<<< orphan*/  AddressFrom; TYPE_4__ Recv; TYPE_3__ AddressFile; TYPE_2__ ReceiveIrp; TYPE_9__* LocalAddress; TYPE_8__ TdiDeviceName; } ;
struct TYPE_10__ {int /*<<< orphan*/  AddressType; } ;
typedef  TYPE_5__* PAFD_FCB ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AFD_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int AFD_ENDPOINT_CONNECTIONLESS ; 
 int /*<<< orphan*/  ExAllocatePoolWithTag (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 scalar_t__ NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  PacketSocketRecvComplete ; 
 int /*<<< orphan*/  PagedPool ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_NO_MEMORY ; 
 scalar_t__ STATUS_NO_SUCH_DEVICE ; 
 scalar_t__ STATUS_PENDING ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  TAG_AFD_DATA_BUFFER ; 
 scalar_t__ TdiOpenAddressFile (TYPE_8__*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TdiQueryMaxDatagramLength (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ TdiReceiveDatagram (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 

NTSTATUS WarmSocketForBind( PAFD_FCB FCB, ULONG ShareType ) {
    NTSTATUS Status;

    AFD_DbgPrint(MID_TRACE,("Called (AF %u)\n",
                            FCB->LocalAddress->Address[0].AddressType));

    if( !FCB->TdiDeviceName.Length || !FCB->TdiDeviceName.Buffer ) {
        AFD_DbgPrint(MIN_TRACE,("Null Device\n"));
        return STATUS_NO_SUCH_DEVICE;
    }
    if( !FCB->LocalAddress ) {
        AFD_DbgPrint(MIN_TRACE,("No local address\n"));
        return STATUS_INVALID_PARAMETER;
    }

    Status = TdiOpenAddressFile(&FCB->TdiDeviceName,
                                FCB->LocalAddress,
                                ShareType,
                                &FCB->AddressFile.Handle,
                                &FCB->AddressFile.Object );
    if (!NT_SUCCESS(Status))
        return Status;

    if (FCB->Flags & AFD_ENDPOINT_CONNECTIONLESS)
    {
        if (!FCB->Recv.Size)
        {
            Status = TdiQueryMaxDatagramLength(FCB->AddressFile.Object,
                                               &FCB->Recv.Size);
        }

        if (NT_SUCCESS(Status) && !FCB->Recv.Window)
        {
            FCB->Recv.Window = ExAllocatePoolWithTag(PagedPool,
                                                     FCB->Recv.Size,
                                                     TAG_AFD_DATA_BUFFER);

            if (!FCB->Recv.Window)
                Status = STATUS_NO_MEMORY;
        }

        if (NT_SUCCESS(Status) && FCB->Recv.Content < FCB->Recv.Size)
        {
            Status = TdiReceiveDatagram(&FCB->ReceiveIrp.InFlightRequest,
                                        FCB->AddressFile.Object,
                                        0,
                                        FCB->Recv.Window,
                                        FCB->Recv.Size,
                                        FCB->AddressFrom,
                                        PacketSocketRecvComplete,
                                        FCB);

            /* We don't want to wait for this read to complete. */
            if( Status == STATUS_PENDING ) Status = STATUS_SUCCESS;
        }
    }

    AFD_DbgPrint(MID_TRACE,("Returning %x\n", Status));

    return Status;
}