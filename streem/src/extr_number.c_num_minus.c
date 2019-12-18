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
 int STRM_NG ; 
 int STRM_OK ; 
 scalar_t__ strm_float_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_float_value (scalar_t__) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strm_int_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_int_value (scalar_t__) ; 
 scalar_t__ strm_number_p (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_value_float (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_value_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
num_minus(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  if (argc == 1) {
    if (strm_int_p(args[0])) {
      *ret = strm_int_value(-strm_value_int(args[0]));
      return STRM_OK;
    }
    if (strm_float_p(args[0])) {
      *ret = strm_float_value(-strm_value_float(args[0]));
      return STRM_OK;
    }
  }
  else {
    strm_value x, y;

    strm_get_args(strm, argc, args, "NN", &x, &y);
    if (strm_int_p(x) && strm_int_p(y)) {
      *ret = strm_int_value(strm_value_int(x)-strm_value_int(y));
      return STRM_OK;
    }
    if (strm_number_p(x) && strm_number_p(y)) {
      *ret = strm_float_value(strm_value_float(x)-strm_value_float(y));
      return STRM_OK;
    }
  }
  return STRM_NG;
}