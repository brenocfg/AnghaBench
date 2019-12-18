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
struct correl_data {int n; int sxx; int syy; double sxy; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct correl_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 double sqrt (int) ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_float_value (double) ; 

__attribute__((used)) static int
correl_finish(strm_stream* strm, strm_value data)
{
  struct correl_data* d = strm->data;

  d->n--;
  double sxx = sqrt(d->sxx / d->n);
  double syy = sqrt(d->syy / d->n);
  double sxy = d->sxy / (d->n * sxx * syy);
  strm_emit(strm, strm_float_value(sxy), NULL);
  return STRM_OK;
}