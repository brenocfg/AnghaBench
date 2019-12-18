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
struct TYPE_7__ {scalar_t__ mode; int rsize; int rcapa; int /*<<< orphan*/  start_func; int /*<<< orphan*/  refcnt; struct TYPE_7__** rest; struct TYPE_7__* dst; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__** realloc (TYPE_1__**,int) ; 
 int /*<<< orphan*/  strm_atomic_inc (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_consumer ; 
 int /*<<< orphan*/  strm_nil_value () ; 
 scalar_t__ strm_producer ; 
 int /*<<< orphan*/  strm_task_push (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_init () ; 

int
strm_stream_connect(strm_stream* src, strm_stream* dst)
{
  assert(src->mode != strm_consumer);
  assert(dst->mode != strm_producer);
  if (src->dst == NULL) {
    src->dst = dst;
  }
  else {
    if (src->rsize <= src->rcapa) {
      src->rcapa = src->rcapa*2+2;
      src->rest = realloc(src->rest, sizeof(strm_stream*)*src->rcapa);
    }
    src->rest[src->rsize++] = dst;
  }
  strm_atomic_inc(dst->refcnt);

  if (src->mode == strm_producer) {
    task_init();
    strm_task_push(src, src->start_func, strm_nil_value());
  }
  return STRM_OK;
}