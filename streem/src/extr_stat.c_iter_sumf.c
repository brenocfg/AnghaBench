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
struct sum_data {double sum; double c; int /*<<< orphan*/  num; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct sum_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  convert_number (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fabs (double) ; 
 int /*<<< orphan*/  strm_number_p (int /*<<< orphan*/ ) ; 
 double strm_value_float (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iter_sumf(strm_stream* strm, strm_value data)
{
  struct sum_data* d = strm->data;
  double x, t;

  data = convert_number(strm, data, d->func);
  if (!strm_number_p(data)) {
    return STRM_NG;
  }
  x = strm_value_float(data);
  t = d->sum + x;
  if (fabs(d->sum) >= fabs(x))
    d->c += ((d->sum - t) + x);
  else
    d->c += ((x - t) + d->sum);
  d->sum = t;
  d->num++;
  return STRM_OK;
}