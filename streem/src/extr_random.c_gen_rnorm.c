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
struct rnorm_data {int dummy; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_5__ {struct rnorm_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 double rand_normal (struct rnorm_data*) ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int (*) (TYPE_1__*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  strm_float_value (double) ; 

__attribute__((used)) static int
gen_rnorm(strm_stream* strm, strm_value data)
{
  struct rnorm_data* d = strm->data;
  double f = rand_normal(d);

  strm_emit(strm, strm_float_value(f), gen_rnorm);
  return STRM_OK;
}