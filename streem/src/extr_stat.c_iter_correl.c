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
struct correl_data {double n; double sx; double sy; int sxx; int syy; int sxy; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct correl_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  strm_array_p (int /*<<< orphan*/ ) ; 
 int strm_ary_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ary_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_number_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_raise (TYPE_1__*,char*) ; 
 double strm_value_float (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iter_correl(strm_stream* strm, strm_value data)
{
  struct correl_data* d = strm->data;
  strm_value *v;
  double dx, dy;

  if (!strm_array_p(data) || strm_ary_len(data) != 2) {
    strm_raise(strm, "invalid data");
    return STRM_NG;
  }

  v = strm_ary_ptr(data);
  if (!strm_number_p(v[0]) || !strm_number_p(v[1])) {
    strm_raise(strm, "correl() requires [num, num]");
    return STRM_NG;
  }
  d->n++;
  dx = strm_value_float(v[0]) - d->sx; d->sx += dx / d->n;
  dy = strm_value_float(v[1]) - d->sy; d->sy += dy / d->n;
  d->sxx += (d->n-1) * dx * dx / d->n;
  d->syy += (d->n-1) * dy * dy / d->n;
  d->sxy += (d->n-1) * dx * dy / d->n;
  return STRM_OK;
}