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
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {scalar_t__ mode; int rsize; struct TYPE_4__** rest; struct TYPE_4__* dst; scalar_t__ start_func; } ;
typedef  TYPE_1__ strm_stream ;
typedef  scalar_t__ strm_callback ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  sched_yield () ; 
 scalar_t__ strm_dying ; 
 scalar_t__ strm_killed ; 
 int /*<<< orphan*/  strm_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_nil_value () ; 
 int /*<<< orphan*/  strm_task_push (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

void
strm_emit(strm_stream* strm, strm_value data, strm_callback func)
{
  if (strm->mode == strm_dying) return;
  if (!strm_nil_p(data)) {
    if (strm->dst) {
      strm_task_push(strm->dst, strm->dst->start_func, data);
      if (strm->dst->mode == strm_killed) {
        strm->dst = NULL;
      }
    }
    if (strm->rest) {
      int i;

      for (i=0; i<strm->rsize; i++) {
        strm_task_push(strm->rest[i], strm->rest[i]->start_func, data);
      }
    }

    /* termination check */
    if (strm->dst == NULL) {
      int closed = TRUE;
      if (strm->rest) {
        int i;

        for (i=0; i<strm->rsize; i++) {
          if (strm->rest[i]->mode != strm_killed) {
            closed = FALSE;
            break;
          }
        }
      }
      if (closed) {
        strm->mode = strm_dying;
        return;
      }
    }
  }
  sched_yield();
  if (func) {
    strm_task_push(strm, func, strm_nil_value());
  }
}