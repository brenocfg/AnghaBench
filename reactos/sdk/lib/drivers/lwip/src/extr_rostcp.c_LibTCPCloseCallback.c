#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_5__* Connection; scalar_t__ Callback; } ;
struct TYPE_10__ {TYPE_3__ Close; } ;
struct TYPE_7__ {void* Error; } ;
struct TYPE_8__ {TYPE_1__ Close; } ;
struct lwip_callback_msg {int /*<<< orphan*/  Event; TYPE_4__ Input; TYPE_2__ Output; } ;
struct TYPE_11__ {scalar_t__ Closing; int /*<<< orphan*/ * SocketContext; } ;
typedef  int /*<<< orphan*/ * PTCP_PCB ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CLSD ; 
 void* ERR_OK ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LibTCPEmptyQueue (TYPE_5__*) ; 
 int /*<<< orphan*/  TCPFinEventHandler (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  tcp_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* tcp_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void
LibTCPCloseCallback(void *arg)
{
    struct lwip_callback_msg *msg = arg;
    PTCP_PCB pcb = msg->Input.Close.Connection->SocketContext;

    /* Empty the queue even if we're already "closed" */
    LibTCPEmptyQueue(msg->Input.Close.Connection);

    /* Check if we've already been closed */
    if (msg->Input.Close.Connection->Closing)
    {
        msg->Output.Close.Error = ERR_OK;
        goto done;
    }

    /* Enter "closing" mode if we're doing a normal close */
    if (msg->Input.Close.Callback)
        msg->Input.Close.Connection->Closing = TRUE;

    /* Check if the PCB was already "closed" but the client doesn't know it yet */
    if (!msg->Input.Close.Connection->SocketContext)
    {
        msg->Output.Close.Error = ERR_OK;
        goto done;
    }

    /* Clear the PCB pointer and stop callbacks */
    msg->Input.Close.Connection->SocketContext = NULL;
    tcp_arg(pcb, NULL);

    /* This may generate additional callbacks but we don't care,
     * because they're too inconsistent to rely on */
    msg->Output.Close.Error = tcp_close(pcb);

    if (msg->Output.Close.Error)
    {
        /* Restore the PCB pointer */
        msg->Input.Close.Connection->SocketContext = pcb;
        msg->Input.Close.Connection->Closing = FALSE;
    }
    else if (msg->Input.Close.Callback)
    {
        TCPFinEventHandler(msg->Input.Close.Connection, ERR_CLSD);
    }

done:
    KeSetEvent(&msg->Event, IO_NO_INCREMENT, FALSE);
}