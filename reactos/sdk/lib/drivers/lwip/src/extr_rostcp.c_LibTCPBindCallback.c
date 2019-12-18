#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  Port; int /*<<< orphan*/  IpAddress; TYPE_4__* Connection; } ;
struct TYPE_12__ {TYPE_3__ Bind; } ;
struct TYPE_8__ {int /*<<< orphan*/  Error; } ;
struct TYPE_9__ {TYPE_1__ Bind; } ;
struct lwip_callback_msg {int /*<<< orphan*/  Event; TYPE_5__ Input; TYPE_2__ Output; } ;
struct TYPE_13__ {int /*<<< orphan*/  so_options; } ;
struct TYPE_11__ {TYPE_6__* SocketContext; } ;
typedef  TYPE_6__* PTCP_PCB ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct lwip_callback_msg*) ; 
 int /*<<< orphan*/  ERR_CLSD ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOF_REUSEADDR ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_bind (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
LibTCPBindCallback(void *arg)
{
    struct lwip_callback_msg *msg = arg;
    PTCP_PCB pcb = msg->Input.Bind.Connection->SocketContext;

    ASSERT(msg);

    if (!msg->Input.Bind.Connection->SocketContext)
    {
        msg->Output.Bind.Error = ERR_CLSD;
        goto done;
    }

    /* We're guaranteed that the local address is valid to bind at this point */
    pcb->so_options |= SOF_REUSEADDR;

    msg->Output.Bind.Error = tcp_bind(pcb,
                                      msg->Input.Bind.IpAddress,
                                      ntohs(msg->Input.Bind.Port));

done:
    KeSetEvent(&msg->Event, IO_NO_INCREMENT, FALSE);
}