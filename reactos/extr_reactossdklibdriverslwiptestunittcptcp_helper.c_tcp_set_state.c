#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u16_t ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct tcp_pcb {int state; void* remote_port; TYPE_2__ remote_ip; void* local_port; TYPE_1__ local_ip; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_3__ ip_addr_t ;
typedef  enum tcp_state { ____Placeholder_tcp_state } tcp_state ;
struct TYPE_10__ {int /*<<< orphan*/  pcbs; } ;

/* Variables and functions */
 int ESTABLISHED ; 
 int LISTEN ; 
 int /*<<< orphan*/  TCP_REG (int /*<<< orphan*/ *,struct tcp_pcb*) ; 
 int TIME_WAIT ; 
 int /*<<< orphan*/  fail () ; 
 int /*<<< orphan*/  tcp_active_pcbs ; 
 TYPE_6__ tcp_listen_pcbs ; 
 int /*<<< orphan*/  tcp_tw_pcbs ; 

void
tcp_set_state(struct tcp_pcb* pcb, enum tcp_state state, ip_addr_t* local_ip,
                   ip_addr_t* remote_ip, u16_t local_port, u16_t remote_port)
{
  /* @todo: are these all states? */
  /* @todo: remove from previous list */
  pcb->state = state;
  if (state == ESTABLISHED) {
    TCP_REG(&tcp_active_pcbs, pcb);
    pcb->local_ip.addr = local_ip->addr;
    pcb->local_port = local_port;
    pcb->remote_ip.addr = remote_ip->addr;
    pcb->remote_port = remote_port;
  } else if(state == LISTEN) {
    TCP_REG(&tcp_listen_pcbs.pcbs, pcb);
    pcb->local_ip.addr = local_ip->addr;
    pcb->local_port = local_port;
  } else if(state == TIME_WAIT) {
    TCP_REG(&tcp_tw_pcbs, pcb);
    pcb->local_ip.addr = local_ip->addr;
    pcb->local_port = local_port;
    pcb->remote_ip.addr = remote_ip->addr;
    pcb->remote_port = remote_port;
  } else {
    fail();
  }
}