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

/* Variables and functions */
 int /*<<< orphan*/  assert (scalar_t__) ; 
 scalar_t__ strm_float_p (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_int_p (int /*<<< orphan*/ ) ; 
 double strm_to_float (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_to_int (int /*<<< orphan*/ ) ; 

double
strm_value_float(strm_value v)
{
  if (strm_int_p(v)) {
    return (double)strm_to_int(v);
  }
  else if (strm_float_p(v)) {
    return strm_to_float(v);
  }
  else {
    assert(strm_float_p(v));
  }
  /* not reached */
  return 0.0;
}