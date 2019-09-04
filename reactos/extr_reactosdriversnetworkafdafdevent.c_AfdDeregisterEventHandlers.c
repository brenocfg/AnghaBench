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
struct TYPE_3__ {int SocketType; int /*<<< orphan*/  TdiAddressObject; } ;
typedef  TYPE_1__* PAFDFCB ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
#define  SOCK_DGRAM 130 
#define  SOCK_RAW 129 
#define  SOCK_STREAM 128 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TDI_EVENT_CHAINED_RECEIVE ; 
 int /*<<< orphan*/  TDI_EVENT_DISCONNECT ; 
 int /*<<< orphan*/  TDI_EVENT_ERROR ; 
 int /*<<< orphan*/  TDI_EVENT_RECEIVE ; 
 int /*<<< orphan*/  TDI_EVENT_RECEIVE_DATAGRAM ; 
 int /*<<< orphan*/  TDI_EVENT_RECEIVE_EXPEDITED ; 
 int /*<<< orphan*/  TdiSetEventHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

NTSTATUS AfdDeregisterEventHandlers(
    PAFDFCB FCB)
{
    NTSTATUS Status;

    Status = TdiSetEventHandler(FCB->TdiAddressObject,
        TDI_EVENT_ERROR,
        NULL,
        NULL);
    if (!NT_SUCCESS(Status)) { return Status; }

    switch (FCB->SocketType) {
    case SOCK_STREAM:
        Status = TdiSetEventHandler(FCB->TdiAddressObject,
            TDI_EVENT_DISCONNECT,
            NULL,
            NULL);
        if (!NT_SUCCESS(Status)) { return Status; }

        Status = TdiSetEventHandler(FCB->TdiAddressObject,
            TDI_EVENT_RECEIVE,
            NULL,
            NULL);
        if (!NT_SUCCESS(Status)) { return Status; }

        Status = TdiSetEventHandler(FCB->TdiAddressObject,
            TDI_EVENT_RECEIVE_EXPEDITED,
            NULL,
            NULL);
        if (!NT_SUCCESS(Status)) { return Status; }

        Status = TdiSetEventHandler(FCB->TdiAddressObject,
            TDI_EVENT_CHAINED_RECEIVE,
            NULL,
            NULL);
        if (!NT_SUCCESS(Status)) { return Status; }
        break;

    case SOCK_DGRAM:
    case SOCK_RAW:
        Status = TdiSetEventHandler(FCB->TdiAddressObject,
            TDI_EVENT_RECEIVE_DATAGRAM,
            NULL,
            NULL);
        if (!NT_SUCCESS(Status)) { return Status; }
    }
    return STATUS_SUCCESS;
}