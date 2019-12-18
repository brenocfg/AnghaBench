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
struct recv_data {int /*<<< orphan*/  strm; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct latch_data {int /*<<< orphan*/  rq; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_3__ {struct latch_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  free (struct recv_data*) ; 
 struct recv_data* strm_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
latch_close(strm_stream* strm, strm_value data)
{
  struct latch_data* d = strm->data;

  for (;;) {
    struct recv_data* r = strm_queue_get(d->rq);
    if (!r) break;
    (*r->func)(r->strm, data);
    free(r);
  }
  return STRM_OK;
}