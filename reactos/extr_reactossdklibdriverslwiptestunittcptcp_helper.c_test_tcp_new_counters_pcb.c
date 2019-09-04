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
struct test_tcp_counters {int dummy; } ;
struct tcp_pcb {void* snd_wnd_max; void* snd_wnd; } ;

/* Variables and functions */
 void* TCP_WND ; 
 int /*<<< orphan*/  tcp_arg (struct tcp_pcb*,struct test_tcp_counters*) ; 
 int /*<<< orphan*/  tcp_err (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 struct tcp_pcb* tcp_new () ; 
 int /*<<< orphan*/  tcp_recv (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_tcp_counters_err ; 
 int /*<<< orphan*/  test_tcp_counters_recv ; 

struct tcp_pcb*
test_tcp_new_counters_pcb(struct test_tcp_counters* counters)
{
  struct tcp_pcb* pcb = tcp_new();
  if (pcb != NULL) {
    /* set up args and callbacks */
    tcp_arg(pcb, counters);
    tcp_recv(pcb, test_tcp_counters_recv);
    tcp_err(pcb, test_tcp_counters_err);
    pcb->snd_wnd = TCP_WND;
    pcb->snd_wnd_max = TCP_WND;
  }
  return pcb;
}