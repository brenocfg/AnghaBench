#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_5__ {scalar_t__ Content; scalar_t__ Size; } ;
struct TYPE_6__ {void* TdiReceiveClosed; TYPE_1__ Recv; scalar_t__ LastReceiveStatus; } ;
typedef  TYPE_2__* PAFD_FCB ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  RefillSocketBuffer (TYPE_2__*) ; 
 scalar_t__ STATUS_SUCCESS ; 
 void* TRUE ; 

__attribute__((used)) static VOID HandleReceiveComplete( PAFD_FCB FCB, NTSTATUS Status, ULONG_PTR Information )
{
    FCB->LastReceiveStatus = Status;

    /* We got closed while the receive was in progress */
    if (FCB->TdiReceiveClosed)
    {
        /* The received data is discarded */
    }
    /* Receive successful */
    else if (Status == STATUS_SUCCESS)
    {
        FCB->Recv.Content += Information;
        ASSERT(FCB->Recv.Content <= FCB->Recv.Size);

        /* Check for graceful closure */
        if (Information == 0)
        {
            /* Receive is closed */
            FCB->TdiReceiveClosed = TRUE;
        }
        else
        {
            /* Issue another receive IRP to keep the buffer well stocked */
            RefillSocketBuffer(FCB);
        }
    }
    /* Receive failed with no data (unexpected closure) */
    else
    {
        /* Previously received data remains intact */
        FCB->TdiReceiveClosed = TRUE;
    }
}