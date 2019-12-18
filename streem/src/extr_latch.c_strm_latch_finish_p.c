#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct latch_data {int /*<<< orphan*/  dq; } ;
struct TYPE_3__ {scalar_t__ mode; struct latch_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 scalar_t__ strm_consumer ; 
 int strm_queue_empty_p (int /*<<< orphan*/ ) ; 

int
strm_latch_finish_p(strm_stream* latch)
{
  struct latch_data* c;

  if (latch->mode == strm_consumer) return 0;
  c = latch->data;
  return strm_queue_empty_p(c->dq);
}