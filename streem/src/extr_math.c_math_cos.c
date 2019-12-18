#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  cos (double) ; 
 int /*<<< orphan*/  strm_float_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,double*) ; 
 double strm_value_float (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
math_cos(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  double f;

  strm_get_args(strm, argc, args, "f", &f);
  f = strm_value_float(args[0]);
  *ret = strm_float_value(cos(f));
  return STRM_OK;
}