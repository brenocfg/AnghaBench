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
struct bar_data {double* data; scalar_t__ offset; int dlen; double max; scalar_t__ row; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_5__ {struct bar_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SIGINT ; 
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (double*) ; 
 int init_bar (struct bar_data*) ; 
 void* interrupt ; 
 int /*<<< orphan*/  move_cursor (scalar_t__,int) ; 
 int /*<<< orphan*/  show_cursor () ; 
 int /*<<< orphan*/  show_graph (struct bar_data*) ; 
 int /*<<< orphan*/  sigupdate ; 
 int /*<<< orphan*/  strm_number_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_raise (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  strm_stream_close (TYPE_1__*) ; 
 int /*<<< orphan*/  strm_unsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double strm_value_float (int /*<<< orphan*/ ) ; 
 void* winch ; 

__attribute__((used)) static int
iter_bar(strm_stream* strm, strm_value data)
{
  struct bar_data* d = strm->data;
  double f, max = 1.0;

  if (interrupt) {
    interrupt = FALSE;
    strm_unsignal(SIGINT, sigupdate);
    move_cursor(d->row-1, 1);
    show_cursor();
    exit(1);
  }
  if (!strm_number_p(data)) {
    strm_raise(strm, "invalid data");
    return STRM_NG;
  }

  if (winch) {
    winch = FALSE;
    free(d->data);
    if (init_bar(d) == STRM_NG) {
      strm_stream_close(strm);
      return STRM_NG;
    }
  }
  f = strm_value_float(data);
  if (f < 0) f = 0;
  d->data[d->offset++] = f;
  max = 1.0;
  for (int i=0; i<d->dlen; i++) {
    f = d->data[i];
    if (f > max) max = f;
  }
  d->max = max;
  if (d->offset == d->dlen) {
    d->offset = 0;
  }
  show_graph(d);
  return STRM_OK;
}