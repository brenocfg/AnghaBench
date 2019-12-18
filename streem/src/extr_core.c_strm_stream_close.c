#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ strm_stream_mode ;
struct TYPE_4__ {scalar_t__ mode; scalar_t__ refcnt; scalar_t__ (* close_func ) (TYPE_1__*,int /*<<< orphan*/ ) ;int rsize; scalar_t__* rest; scalar_t__ dst; scalar_t__* data; } ;
typedef  TYPE_1__ strm_stream ;
typedef  int /*<<< orphan*/  strm_callback ;

/* Variables and functions */
 scalar_t__ STRM_NG ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ stream_count ; 
 int /*<<< orphan*/  strm_atomic_cas (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strm_atomic_dec (scalar_t__) ; 
 scalar_t__ strm_killed ; 
 int /*<<< orphan*/  strm_nil_value () ; 
 int /*<<< orphan*/  strm_task_push (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
strm_stream_close(strm_stream* strm)
{
  strm_stream_mode mode = strm->mode;

  if (mode == strm_killed) return;
  strm_atomic_dec(strm->refcnt);
  if (strm->refcnt > 0) return;
  if (!strm_atomic_cas(strm->mode, mode, strm_killed)) {
    return;
  }
  if (strm->close_func) {
    if ((*strm->close_func)(strm, strm_nil_value()) == STRM_NG)
      return;
  }
  else {
    free(strm->data);
    strm->data = NULL;
  }

  if (strm->dst) {
    strm_task_push(strm->dst, (strm_callback)strm_stream_close, strm_nil_value());
  }
  if (strm->rest) {
    int i;

    for (i=0; i<strm->rsize; i++) {
      strm_task_push(strm->rest[i], (strm_callback)strm_stream_close, strm_nil_value());
    }
    free(strm->rest);
  }
  strm_atomic_dec(stream_count);
}