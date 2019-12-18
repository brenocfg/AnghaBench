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
struct tcp_seg {struct tcp_seg* next; int /*<<< orphan*/  p; } ;
struct tcp_pcb {struct tcp_seg* ooseq; } ;

/* Variables and functions */
 scalar_t__ pbuf_clen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcp_oos_pbuf_count(struct tcp_pcb* pcb)
{
  int num = 0;
  struct tcp_seg* seg = pcb->ooseq;
  while(seg != NULL) {
    num += pbuf_clen(seg->p);
    seg = seg->next;
  }
  return num;
}