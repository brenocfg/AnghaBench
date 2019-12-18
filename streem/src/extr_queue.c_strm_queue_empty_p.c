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
struct strm_queue {scalar_t__ head; scalar_t__ tail; } ;

/* Variables and functions */

int
strm_queue_empty_p(struct strm_queue* q)
{
  if (q->head == q->tail) return 1;
  return 0;
}