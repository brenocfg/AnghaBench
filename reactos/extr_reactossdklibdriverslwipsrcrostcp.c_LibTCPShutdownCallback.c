#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_5__* Connection; scalar_t__ shut_tx; scalar_t__ shut_rx; } ;
struct TYPE_9__ {TYPE_3__ Shutdown; } ;
struct TYPE_6__ {void* Error; } ;
struct TYPE_7__ {TYPE_1__ Shutdown; } ;
struct lwip_callback_msg {int /*<<< orphan*/  Event; TYPE_4__ Input; TYPE_2__ Output; } ;
struct TYPE_10__ {int /*<<< orphan*/ * SocketContext; void* SendShutdown; void* ReceiveShutdown; int /*<<< orphan*/  ReceiveShutdownStatus; } ;
typedef  int /*<<< orphan*/ * PTCP_PCB ;

/* Variables and functions */
 void* ERR_CLSD ; 
 void* FALSE ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  STATUS_FILE_CLOSED ; 
 int /*<<< orphan*/  TCPFinEventHandler (TYPE_5__*,void*) ; 
 void* TRUE ; 
 int /*<<< orphan*/  tcp_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* tcp_shutdown (int /*<<< orphan*/ *,void*,void*) ; 

__attribute__((used)) static
void
LibTCPShutdownCallback(void *arg)
{
    struct lwip_callback_msg *msg = arg;
    PTCP_PCB pcb = msg->Input.Shutdown.Connection->SocketContext;

    if (!msg->Input.Shutdown.Connection->SocketContext)
    {
        msg->Output.Shutdown.Error = ERR_CLSD;
        goto done;
    }

    /* LwIP makes the (questionable) assumption that SHUTDOWN_RDWR is equivalent to tcp_close().
     * This assumption holds even if the shutdown calls are done separately (even through multiple
     * WinSock shutdown() calls). This assumption means that lwIP has the right to deallocate our
     * PCB without telling us if we shutdown TX and RX. To avoid these problems, we'll clear the
     * socket context if we have called shutdown for TX and RX.
     */
    if (msg->Input.Shutdown.shut_rx) {
        msg->Output.Shutdown.Error = tcp_shutdown(pcb, TRUE, FALSE);
    }
    if (msg->Input.Shutdown.shut_tx) {
        msg->Output.Shutdown.Error = tcp_shutdown(pcb, FALSE, TRUE);
    }

    if (!msg->Output.Shutdown.Error)
    {
        if (msg->Input.Shutdown.shut_rx)
        {
            msg->Input.Shutdown.Connection->ReceiveShutdown = TRUE;
            msg->Input.Shutdown.Connection->ReceiveShutdownStatus = STATUS_FILE_CLOSED;
        }

        if (msg->Input.Shutdown.shut_tx)
            msg->Input.Shutdown.Connection->SendShutdown = TRUE;

        if (msg->Input.Shutdown.Connection->ReceiveShutdown &&
            msg->Input.Shutdown.Connection->SendShutdown)
        {
            /* The PCB is not ours anymore */
            msg->Input.Shutdown.Connection->SocketContext = NULL;
            tcp_arg(pcb, NULL);
            TCPFinEventHandler(msg->Input.Shutdown.Connection, ERR_CLSD);
        }
    }

done:
    KeSetEvent(&msg->Event, IO_NO_INCREMENT, FALSE);
}