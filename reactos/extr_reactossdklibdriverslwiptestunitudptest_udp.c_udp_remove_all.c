#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct udp_pcb {struct udp_pcb* next; } ;
struct TYPE_4__ {TYPE_1__* memp; } ;
struct TYPE_3__ {scalar_t__ used; } ;

/* Variables and functions */
 size_t MEMP_UDP_PCB ; 
 int /*<<< orphan*/  fail_unless (int) ; 
 TYPE_2__ lwip_stats ; 
 struct udp_pcb* udp_pcbs ; 
 int /*<<< orphan*/  udp_remove (struct udp_pcb*) ; 

__attribute__((used)) static void
udp_remove_all(void)
{
  struct udp_pcb *pcb = udp_pcbs;
  struct udp_pcb *pcb2;

  while(pcb != NULL) {
    pcb2 = pcb;
    pcb = pcb->next;
    udp_remove(pcb2);
  }
  fail_unless(lwip_stats.memp[MEMP_UDP_PCB].used == 0);
}