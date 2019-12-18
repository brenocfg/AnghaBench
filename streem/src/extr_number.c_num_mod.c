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
typedef  int strm_int ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  fmod (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strm_float_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_float_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ strm_int_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_int_value (int) ; 
 int /*<<< orphan*/  strm_value_float (int /*<<< orphan*/ ) ; 
 int strm_value_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
num_mod(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_value x;
  strm_int y;

  strm_get_args(strm, argc, args, "Ni", &x, &y);
  if (strm_int_p(x)) {
    *ret = strm_int_value(strm_value_int(x)%y);
    return STRM_OK;
  }
  if (strm_float_p(x)) {
    *ret = strm_float_value(fmod(strm_value_float(x), y));
    return STRM_OK;
  }
  return STRM_NG;
}