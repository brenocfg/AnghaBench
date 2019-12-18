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
struct rand_data {int /*<<< orphan*/  seed; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_5__ {struct rand_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 double rand_float (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int (*) (TYPE_1__*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  strm_float_value (double) ; 

__attribute__((used)) static int
gen_rand(strm_stream* strm, strm_value data)
{
  struct rand_data* d = strm->data;
  double f = rand_float(d->seed);

  strm_emit(strm, strm_float_value(f), gen_rand);
  return STRM_OK;
}