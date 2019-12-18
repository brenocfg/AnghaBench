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
 double strm_value_float (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
num_cmp(strm_value x, strm_value y)
{
  double a = strm_value_float(x);
  double b = strm_value_float(y);
  if(a > b)
    return 1;
  else if(a < b)
    return -1;
  return 0;
}