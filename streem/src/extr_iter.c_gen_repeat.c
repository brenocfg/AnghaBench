#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct repeat_data {scalar_t__ count; int /*<<< orphan*/  v; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_5__ {struct repeat_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strm_stream_close (TYPE_1__*) ; 

__attribute__((used)) static int
gen_repeat(strm_stream* strm, strm_value data)
{
  struct repeat_data *d = strm->data;

  d->count--;
  if (d->count == 0) {
    strm_emit(strm, d->v, NULL);
    strm_stream_close(strm);
  }
  else {
    strm_emit(strm, d->v, gen_repeat);
  }
  return STRM_OK;
}