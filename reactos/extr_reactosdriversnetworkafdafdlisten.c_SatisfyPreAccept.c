#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  Address; int /*<<< orphan*/  SequenceNumber; } ;
struct TYPE_23__ {TYPE_2__* ConnInfo; int /*<<< orphan*/  Seq; } ;
struct TYPE_20__ {int /*<<< orphan*/  Status; scalar_t__ Information; } ;
struct TYPE_16__ {int /*<<< orphan*/  SystemBuffer; } ;
struct TYPE_22__ {TYPE_5__ IoStatus; scalar_t__ MdlAddress; TYPE_1__ AssociatedIrp; } ;
struct TYPE_21__ {TYPE_4__* Address; int /*<<< orphan*/  TAAddressCount; } ;
struct TYPE_19__ {TYPE_3__* Address; int /*<<< orphan*/  AddressLength; int /*<<< orphan*/  AddressType; } ;
struct TYPE_18__ {int /*<<< orphan*/  in_addr; int /*<<< orphan*/  sin_port; } ;
struct TYPE_17__ {int /*<<< orphan*/  RemoteAddress; } ;
typedef  TYPE_6__* PTA_IP_ADDRESS ;
typedef  TYPE_7__* PIRP ;
typedef  scalar_t__ PCHAR ;
typedef  TYPE_8__* PAFD_TDI_OBJECT_QELT ;
typedef  TYPE_9__* PAFD_RECEIVED_ACCEPT_DATA ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AFD_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IO_NETWORK_INCREMENT ; 
 int /*<<< orphan*/  IoCompleteRequest (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoGetCurrentIrpStackLocation (TYPE_7__*) ; 
 int /*<<< orphan*/  IoSetCancelRoutine (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TaCopyTransportAddressInPlace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockRequest (TYPE_7__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static NTSTATUS SatisfyPreAccept( PIRP Irp, PAFD_TDI_OBJECT_QELT Qelt ) {
    PAFD_RECEIVED_ACCEPT_DATA ListenReceive =
        (PAFD_RECEIVED_ACCEPT_DATA)Irp->AssociatedIrp.SystemBuffer;
    PTA_IP_ADDRESS IPAddr;

    ListenReceive->SequenceNumber = Qelt->Seq;

    AFD_DbgPrint(MID_TRACE,("Giving SEQ %u to userland\n", Qelt->Seq));
    AFD_DbgPrint(MID_TRACE,("Socket Address (K) %p (U) %p\n",
                            &ListenReceive->Address,
                            Qelt->ConnInfo->RemoteAddress));

    TaCopyTransportAddressInPlace( &ListenReceive->Address,
                                   Qelt->ConnInfo->RemoteAddress );

    IPAddr = (PTA_IP_ADDRESS)&ListenReceive->Address;

    AFD_DbgPrint(MID_TRACE,("IPAddr->TAAddressCount %d\n",
                            IPAddr->TAAddressCount));
    AFD_DbgPrint(MID_TRACE,("IPAddr->Address[0].AddressType %u\n",
                            IPAddr->Address[0].AddressType));
    AFD_DbgPrint(MID_TRACE,("IPAddr->Address[0].AddressLength %u\n",
                            IPAddr->Address[0].AddressLength));
    AFD_DbgPrint(MID_TRACE,("IPAddr->Address[0].Address[0].sin_port %x\n",
                            IPAddr->Address[0].Address[0].sin_port));
    AFD_DbgPrint(MID_TRACE,("IPAddr->Address[0].Address[0].sin_addr %x\n",
                            IPAddr->Address[0].Address[0].in_addr));

    if( Irp->MdlAddress ) UnlockRequest( Irp, IoGetCurrentIrpStackLocation( Irp ) );

    Irp->IoStatus.Information = ((PCHAR)&IPAddr[1]) - ((PCHAR)ListenReceive);
    Irp->IoStatus.Status = STATUS_SUCCESS;
    (void)IoSetCancelRoutine(Irp, NULL);
    IoCompleteRequest( Irp, IO_NETWORK_INCREMENT );
    return STATUS_SUCCESS;
}