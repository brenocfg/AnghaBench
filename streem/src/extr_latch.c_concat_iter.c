#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct concat_data {size_t i; size_t len; TYPE_1__** latch; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_9__ {struct concat_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strm_latch_finish_p (TYPE_1__*) ; 
 int /*<<< orphan*/  strm_latch_receive (TYPE_1__*,TYPE_1__*,int (*) (TYPE_1__*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  strm_stream_close (TYPE_1__*) ; 

__attribute__((used)) static int
concat_iter(strm_stream* strm, strm_value data)
{
  struct concat_data* d = strm->data;

  strm_emit(strm, data, NULL);
  if (strm_latch_finish_p(d->latch[d->i])) {
    strm_stream_close(d->latch[d->i]);
    d->i++;
  }
  if (d->i < d->len) {
    strm_latch_receive(d->latch[d->i], strm, concat_iter);
  }
  else {
    strm_stream_close(strm);
  }
  return STRM_OK;
}