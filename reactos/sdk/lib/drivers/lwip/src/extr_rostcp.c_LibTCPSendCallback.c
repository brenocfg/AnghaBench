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
struct TYPE_9__ {scalar_t__ Error; scalar_t__ Information; } ;
struct TYPE_10__ {TYPE_4__ Send; } ;
struct TYPE_7__ {scalar_t__ DataLength; TYPE_1__* Connection; int /*<<< orphan*/  Data; } ;
struct TYPE_8__ {TYPE_2__ Send; } ;
struct lwip_callback_msg {int /*<<< orphan*/  Event; TYPE_5__ Output; TYPE_3__ Input; } ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {scalar_t__ SocketContext; scalar_t__ SendShutdown; } ;
typedef  scalar_t__ PTCP_PCB ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct lwip_callback_msg*) ; 
 void* ERR_CLSD ; 
 void* ERR_INPROGRESS ; 
 scalar_t__ ERR_MEM ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_WRITE_FLAG_COPY ; 
 int /*<<< orphan*/  TCP_WRITE_FLAG_MORE ; 
 int /*<<< orphan*/  tcp_output (scalar_t__) ; 
 scalar_t__ tcp_sndbuf (scalar_t__) ; 
 scalar_t__ tcp_write (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
LibTCPSendCallback(void *arg)
{
    struct lwip_callback_msg *msg = arg;
    PTCP_PCB pcb = msg->Input.Send.Connection->SocketContext;
    ULONG SendLength;
    UCHAR SendFlags;

    ASSERT(msg);

    if (!msg->Input.Send.Connection->SocketContext)
    {
        msg->Output.Send.Error = ERR_CLSD;
        goto done;
    }

    if (msg->Input.Send.Connection->SendShutdown)
    {
        msg->Output.Send.Error = ERR_CLSD;
        goto done;
    }

    SendFlags = TCP_WRITE_FLAG_COPY;
    SendLength = msg->Input.Send.DataLength;
    if (tcp_sndbuf(pcb) == 0)
    {
        /* No buffer space so return pending */
        msg->Output.Send.Error = ERR_INPROGRESS;
        goto done;
    }
    else if (tcp_sndbuf(pcb) < SendLength)
    {
        /* We've got some room so let's send what we can */
        SendLength = tcp_sndbuf(pcb);

        /* Don't set the push flag */
        SendFlags |= TCP_WRITE_FLAG_MORE;
    }

    msg->Output.Send.Error = tcp_write(pcb,
                                       msg->Input.Send.Data,
                                       SendLength,
                                       SendFlags);
    if (msg->Output.Send.Error == ERR_OK)
    {
        /* Queued successfully so try to send it */
        tcp_output((PTCP_PCB)msg->Input.Send.Connection->SocketContext);
        msg->Output.Send.Information = SendLength;
    }
    else if (msg->Output.Send.Error == ERR_MEM)
    {
        /* The queue is too long */
        msg->Output.Send.Error = ERR_INPROGRESS;
    }

done:
    KeSetEvent(&msg->Event, IO_NO_INCREMENT, FALSE);
}