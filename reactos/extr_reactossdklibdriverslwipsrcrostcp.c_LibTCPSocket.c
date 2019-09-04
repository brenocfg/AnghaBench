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
struct tcp_pcb {int dummy; } ;
struct TYPE_5__ {struct tcp_pcb* NewPcb; } ;
struct TYPE_6__ {TYPE_1__ Socket; } ;
struct TYPE_7__ {void* Arg; } ;
struct TYPE_8__ {TYPE_3__ Socket; } ;
struct lwip_callback_msg {TYPE_2__ Output; int /*<<< orphan*/  Event; TYPE_4__ Input; } ;

/* Variables and functions */
 struct lwip_callback_msg* ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,struct lwip_callback_msg*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LibTCPSocketCallback ; 
 int /*<<< orphan*/  MessageLookasideList ; 
 int /*<<< orphan*/  NotificationEvent ; 
 scalar_t__ WaitForEventSafely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpip_callback_with_block (int /*<<< orphan*/ ,struct lwip_callback_msg*,int) ; 

struct tcp_pcb *
LibTCPSocket(void *arg)
{
    struct lwip_callback_msg *msg = ExAllocateFromNPagedLookasideList(&MessageLookasideList);
    struct tcp_pcb *ret;

    if (msg)
    {
        KeInitializeEvent(&msg->Event, NotificationEvent, FALSE);
        msg->Input.Socket.Arg = arg;

        tcpip_callback_with_block(LibTCPSocketCallback, msg, 1);

        if (WaitForEventSafely(&msg->Event))
            ret = msg->Output.Socket.NewPcb;
        else
            ret = NULL;

        ExFreeToNPagedLookasideList(&MessageLookasideList, msg);

        return ret;
    }

    return NULL;
}