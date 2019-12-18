#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ NewPcb; } ;
struct TYPE_7__ {TYPE_2__ Socket; } ;
struct TYPE_8__ {int /*<<< orphan*/  Arg; } ;
struct TYPE_5__ {TYPE_4__ Socket; } ;
struct lwip_callback_msg {int /*<<< orphan*/  Event; TYPE_3__ Output; TYPE_1__ Input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct lwip_callback_msg*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  InternalErrorEventHandler ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_arg (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_err (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_new () ; 

__attribute__((used)) static
void
LibTCPSocketCallback(void *arg)
{
    struct lwip_callback_msg *msg = arg;

    ASSERT(msg);

    msg->Output.Socket.NewPcb = tcp_new();

    if (msg->Output.Socket.NewPcb)
    {
        tcp_arg(msg->Output.Socket.NewPcb, msg->Input.Socket.Arg);
        tcp_err(msg->Output.Socket.NewPcb, InternalErrorEventHandler);
    }

    KeSetEvent(&msg->Event, IO_NO_INCREMENT, FALSE);
}