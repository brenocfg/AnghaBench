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
typedef  int /*<<< orphan*/  strm_stream_mode ;
struct TYPE_4__ {int /*<<< orphan*/  queue; scalar_t__ excl; scalar_t__ refcnt; int /*<<< orphan*/ * exc; scalar_t__ flags; scalar_t__ rcapa; scalar_t__ rsize; int /*<<< orphan*/ * rest; int /*<<< orphan*/ * dst; void* data; void* close_func; void* start_func; int /*<<< orphan*/  mode; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ strm_stream ;
typedef  void* strm_callback ;

/* Variables and functions */
 int /*<<< orphan*/  STRM_PTR_STREAM ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  stream_count ; 
 int /*<<< orphan*/  strm_atomic_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_queue_new () ; 

strm_stream*
strm_stream_new(strm_stream_mode mode, strm_callback start_func, strm_callback close_func, void* data)
{
  strm_stream *s = malloc(sizeof(strm_stream));
  s->type = STRM_PTR_STREAM;
  s->mode = mode;
  s->start_func = start_func;
  s->close_func = close_func;
  s->data = data;
  s->dst = NULL;
  s->rest = NULL;
  s->rsize = 0;
  s->rcapa = 0;
  s->flags = 0;
  s->exc = NULL;
  s->refcnt = 0;
  s->excl = 0;
  s->queue = strm_queue_new();
  strm_atomic_inc(stream_count);

  return s;
}