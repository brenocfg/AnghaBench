#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_4__ {scalar_t__ callback_arg; } ;
typedef  TYPE_1__* PTCP_PCB ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CLSD ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  TCPAcceptEventHandler (void*,TYPE_1__*) ; 

__attribute__((used)) static
err_t
InternalAcceptEventHandler(void *arg, PTCP_PCB newpcb, const err_t err)
{
    /* Make sure the socket didn't get closed */
    if (!arg)
        return ERR_CLSD;

    TCPAcceptEventHandler(arg, newpcb);

    /* Set in LibTCPAccept (called from TCPAcceptEventHandler) */
    if (newpcb->callback_arg)
        return ERR_OK;
    else
        return ERR_CLSD;
}