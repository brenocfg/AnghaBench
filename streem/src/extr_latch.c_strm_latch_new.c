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
struct latch_data {void* rq; void* dq; } ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latch_close ; 
 int /*<<< orphan*/  latch_push ; 
 struct latch_data* malloc (int) ; 
 int /*<<< orphan*/  strm_consumer ; 
 void* strm_queue_new () ; 
 int /*<<< orphan*/ * strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct latch_data*) ; 

strm_stream*
strm_latch_new()
{
  struct latch_data* d = malloc(sizeof(struct latch_data));

  assert(d != NULL);
  d->dq = strm_queue_new();
  d->rq = strm_queue_new();
  return strm_stream_new(strm_consumer, latch_push, latch_close, d);
}