#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcp_pcb {int dummy; } ;
typedef  int /*<<< orphan*/  PTCP_PCB ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (void*) ; 
 int /*<<< orphan*/  InternalErrorEventHandler ; 
 int /*<<< orphan*/  InternalRecvEventHandler ; 
 int /*<<< orphan*/  InternalSendEventHandler ; 
 int /*<<< orphan*/  tcp_accepted (struct tcp_pcb*) ; 
 int /*<<< orphan*/  tcp_arg (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  tcp_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_sent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
LibTCPAccept(PTCP_PCB pcb, struct tcp_pcb *listen_pcb, void *arg)
{
    ASSERT(arg);

    tcp_arg(pcb, NULL);
    tcp_recv(pcb, InternalRecvEventHandler);
    tcp_sent(pcb, InternalSendEventHandler);
    tcp_err(pcb, InternalErrorEventHandler);
    tcp_arg(pcb, arg);

    tcp_accepted(listen_pcb);
}