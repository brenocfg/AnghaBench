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
typedef  int /*<<< orphan*/  u8_t ;
struct TYPE_6__ {int /*<<< orphan*/ * NewPcb; } ;
struct TYPE_7__ {TYPE_2__ Listen; } ;
struct TYPE_8__ {int /*<<< orphan*/  Backlog; int /*<<< orphan*/  Connection; } ;
struct TYPE_5__ {TYPE_4__ Listen; } ;
struct lwip_callback_msg {TYPE_3__ Output; int /*<<< orphan*/  Event; TYPE_1__ Input; } ;
typedef  int /*<<< orphan*/ * PTCP_PCB ;
typedef  int /*<<< orphan*/  PCONNECTION_ENDPOINT ;

/* Variables and functions */
 struct lwip_callback_msg* ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,struct lwip_callback_msg*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LibTCPListenCallback ; 
 int /*<<< orphan*/  MessageLookasideList ; 
 int /*<<< orphan*/  NotificationEvent ; 
 scalar_t__ WaitForEventSafely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpip_callback_with_block (int /*<<< orphan*/ ,struct lwip_callback_msg*,int) ; 

PTCP_PCB
LibTCPListen(PCONNECTION_ENDPOINT Connection, const u8_t backlog)
{
    struct lwip_callback_msg *msg;
    PTCP_PCB ret;

    msg = ExAllocateFromNPagedLookasideList(&MessageLookasideList);
    if (msg)
    {
        KeInitializeEvent(&msg->Event, NotificationEvent, FALSE);
        msg->Input.Listen.Connection = Connection;
        msg->Input.Listen.Backlog = backlog;

        tcpip_callback_with_block(LibTCPListenCallback, msg, 1);

        if (WaitForEventSafely(&msg->Event))
            ret = msg->Output.Listen.NewPcb;
        else
            ret = NULL;

        ExFreeToNPagedLookasideList(&MessageLookasideList, msg);

        return ret;
    }

    return NULL;
}