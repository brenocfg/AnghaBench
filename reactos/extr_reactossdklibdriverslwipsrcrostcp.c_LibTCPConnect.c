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
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_7__ {int /*<<< orphan*/  Error; } ;
struct TYPE_8__ {TYPE_3__ Connect; } ;
struct TYPE_5__ {int /*<<< orphan*/  Port; struct ip_addr* IpAddress; int /*<<< orphan*/  Connection; } ;
struct TYPE_6__ {TYPE_1__ Connect; } ;
struct lwip_callback_msg {TYPE_4__ Output; int /*<<< orphan*/  Event; TYPE_2__ Input; } ;
struct ip_addr {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;
typedef  int /*<<< orphan*/  PCONNECTION_ENDPOINT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CLSD ; 
 int /*<<< orphan*/  ERR_MEM ; 
 struct lwip_callback_msg* ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,struct lwip_callback_msg*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LibTCPConnectCallback ; 
 int /*<<< orphan*/  MessageLookasideList ; 
 int /*<<< orphan*/  NotificationEvent ; 
 scalar_t__ WaitForEventSafely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpip_callback_with_block (int /*<<< orphan*/ ,struct lwip_callback_msg*,int) ; 

err_t
LibTCPConnect(PCONNECTION_ENDPOINT Connection, struct ip_addr *const ipaddr, const u16_t port)
{
    struct lwip_callback_msg *msg;
    err_t ret;

    msg = ExAllocateFromNPagedLookasideList(&MessageLookasideList);
    if (msg)
    {
        KeInitializeEvent(&msg->Event, NotificationEvent, FALSE);
        msg->Input.Connect.Connection = Connection;
        msg->Input.Connect.IpAddress = ipaddr;
        msg->Input.Connect.Port = port;

        tcpip_callback_with_block(LibTCPConnectCallback, msg, 1);

        if (WaitForEventSafely(&msg->Event))
        {
            ret = msg->Output.Connect.Error;
        }
        else
            ret = ERR_CLSD;

        ExFreeToNPagedLookasideList(&MessageLookasideList, msg);

        return ret;
    }

    return ERR_MEM;
}