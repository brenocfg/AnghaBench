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
struct minmax_data {double num; void* data; scalar_t__ min; scalar_t__ start; int /*<<< orphan*/  func; } ;
typedef  void* strm_value ;
struct TYPE_4__ {struct minmax_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ STRM_NG ; 
 int STRM_OK ; 
 scalar_t__ strm_funcall (TYPE_1__*,int /*<<< orphan*/ ,int,void**,void**) ; 
 int /*<<< orphan*/  strm_nil_p (int /*<<< orphan*/ ) ; 
 double strm_value_float (void*) ; 

__attribute__((used)) static int
iter_minmax(strm_stream* strm, strm_value data)
{
  struct minmax_data* d = strm->data;
  strm_value e;
  double num;

  if (!strm_nil_p(d->func)) {
    if (strm_funcall(strm, d->func, 1, &data, &e) == STRM_NG) {
      return STRM_NG;
    }
  }
  else {
    e = data;
  }
  num = strm_value_float(e);
  if (d->start) {
    d->start = FALSE;
    d->num = num;
    d->data = data;
  }
  else if (d->min) {            /* min */
    if (d->num > num) {
      d->num = num;
      d->data = data;
    }
  }
  else {                        /* max */
    if (d->num < num) {
      d->num = num;
      d->data = data;
    }
  }
  return STRM_OK;
}