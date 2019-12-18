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
 scalar_t__ TCP_TCPLEN (struct tcp_seg*) ; 

__attribute__((used)) static int
tcp_oos_tcplen(struct tcp_pcb* pcb)
{
  int len = 0;
  struct tcp_seg* seg = pcb->ooseq;

  /* then check the actual segment */
  while(seg != NULL) {
    len += TCP_TCPLEN(seg);
    seg = seg->next;
  }
  return len;
}