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
struct sort_data {size_t len; struct sort_data* buf; int /*<<< orphan*/  func; } ;
struct sort_arg {int /*<<< orphan*/  func; TYPE_1__* strm; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct sort_data* data; } ;
typedef  TYPE_1__ strm_stream ;
typedef  size_t strm_int ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  free (struct sort_data*) ; 
 int /*<<< orphan*/  mem_sort (struct sort_data*,size_t,struct sort_arg*) ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,struct sort_data,int /*<<< orphan*/ *) ; 
 scalar_t__ strm_nil_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
finish_sort(strm_stream* strm, strm_value data)
{
  struct sort_data* d = strm->data;
  strm_int i, len;

  if (strm_nil_p(d->func)) {
    mem_sort(d->buf, d->len, NULL);
  }
  else {
    struct sort_arg arg;

    arg.strm = strm;
    arg.func = d->func;
    mem_sort(d->buf, d->len, &arg);
  }

  for (i=0,len=d->len; i<len; i++) {
    strm_emit(strm, d->buf[i], NULL);
  }
  free(d->buf);
  free(d);
  return STRM_OK;
}