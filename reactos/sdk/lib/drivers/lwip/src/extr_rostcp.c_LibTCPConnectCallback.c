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
struct TYPE_9__ {scalar_t__ Error; } ;
struct TYPE_10__ {TYPE_4__ Connect; } ;
struct TYPE_7__ {int /*<<< orphan*/  Port; int /*<<< orphan*/  IpAddress; TYPE_1__* Connection; } ;
struct TYPE_8__ {TYPE_2__ Connect; } ;
struct lwip_callback_msg {int /*<<< orphan*/  Event; TYPE_5__ Output; TYPE_3__ Input; } ;
typedef  scalar_t__ err_t ;
struct TYPE_6__ {scalar_t__ SocketContext; } ;
typedef  int /*<<< orphan*/  PTCP_PCB ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (void*) ; 
 scalar_t__ ERR_CLSD ; 
 scalar_t__ ERR_INPROGRESS ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  InternalConnectEventHandler ; 
 int /*<<< orphan*/  InternalRecvEventHandler ; 
 int /*<<< orphan*/  InternalSendEventHandler ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_sent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
LibTCPConnectCallback(void *arg)
{
    struct lwip_callback_msg *msg = arg;
    err_t Error;

    ASSERT(arg);

    if (!msg->Input.Connect.Connection->SocketContext)
    {
        msg->Output.Connect.Error = ERR_CLSD;
        goto done;
    }

    tcp_recv((PTCP_PCB)msg->Input.Connect.Connection->SocketContext, InternalRecvEventHandler);
    tcp_sent((PTCP_PCB)msg->Input.Connect.Connection->SocketContext, InternalSendEventHandler);

    Error = tcp_connect((PTCP_PCB)msg->Input.Connect.Connection->SocketContext,
                        msg->Input.Connect.IpAddress, ntohs(msg->Input.Connect.Port),
                        InternalConnectEventHandler);

    msg->Output.Connect.Error = Error == ERR_OK ? ERR_INPROGRESS : Error;

done:
    KeSetEvent(&msg->Event, IO_NO_INCREMENT, FALSE);
}