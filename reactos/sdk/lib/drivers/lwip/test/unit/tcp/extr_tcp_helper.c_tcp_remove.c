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
struct tcp_pcb {struct tcp_pcb* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcp_abort (struct tcp_pcb*) ; 

__attribute__((used)) static void
tcp_remove(struct tcp_pcb* pcb_list)
{
  struct tcp_pcb *pcb = pcb_list;
  struct tcp_pcb *pcb2;

  while(pcb != NULL) {
    pcb2 = pcb;
    pcb = pcb->next;
    tcp_abort(pcb2);
  }
}