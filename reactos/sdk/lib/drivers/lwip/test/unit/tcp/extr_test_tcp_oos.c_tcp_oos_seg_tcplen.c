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
struct tcp_seg {struct tcp_seg* next; } ;
struct tcp_pcb {struct tcp_seg* ooseq; } ;

/* Variables and functions */
 int TCP_TCPLEN (struct tcp_seg*) ; 
 int /*<<< orphan*/  fail () ; 

__attribute__((used)) static int
tcp_oos_seg_tcplen(struct tcp_pcb* pcb, int seg_index)
{
  int num = 0;
  struct tcp_seg* seg = pcb->ooseq;

  /* then check the actual segment */
  while(seg != NULL) {
    if(num == seg_index) {
      return TCP_TCPLEN(seg);
    }
    num++;
    seg = seg->next;
  }
  fail();
  return -1;
}