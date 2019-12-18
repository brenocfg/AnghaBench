#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct recv_data {int /*<<< orphan*/  (* func ) (TYPE_1__*,int /*<<< orphan*/ ) ;TYPE_1__* strm; } ;
struct latch_data {int /*<<< orphan*/  rq; int /*<<< orphan*/  dq; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_7__ {scalar_t__ start_func; struct latch_data* data; } ;
typedef  TYPE_1__ strm_stream ;
typedef  int /*<<< orphan*/  (* strm_callback ) (TYPE_1__*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ latch_push ; 
 struct recv_data* malloc (int) ; 
 int /*<<< orphan*/  strm_queue_add (int /*<<< orphan*/ ,struct recv_data*) ; 
 int /*<<< orphan*/ * strm_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
strm_latch_receive(strm_stream* latch, strm_stream* strm, strm_callback func)
{
  struct latch_data* d;
  strm_value* v;

  assert(latch->start_func == latch_push);
  d = latch->data;
  v = strm_queue_get(d->dq);
  if (v) {
    (*func)(strm, *v);
    free(v);
  }
  else {
    struct recv_data* r = malloc(sizeof(struct recv_data));
    r->strm = strm;
    r->func = func;
    strm_queue_add(d->rq, r);
  }
}