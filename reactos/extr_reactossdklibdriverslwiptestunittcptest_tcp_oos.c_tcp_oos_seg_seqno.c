#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32_t ;
struct tcp_seg {struct tcp_seg* next; TYPE_1__* tcphdr; } ;
struct tcp_pcb {struct tcp_seg* ooseq; } ;
struct TYPE_2__ {int /*<<< orphan*/  seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  fail () ; 

__attribute__((used)) static u32_t
tcp_oos_seg_seqno(struct tcp_pcb* pcb, int seg_index)
{
  int num = 0;
  struct tcp_seg* seg = pcb->ooseq;

  /* then check the actual segment */
  while(seg != NULL) {
    if(num == seg_index) {
      return seg->tcphdr->seqno;
    }
    num++;
    seg = seg->next;
  }
  fail();
  return 0;
}