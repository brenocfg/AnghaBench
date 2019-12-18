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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  strm_value ;

/* Variables and functions */
 int /*<<< orphan*/  STRM_TAG_NAN ; 
 scalar_t__ isnan (double) ; 

strm_value
strm_float_value(double f)
{
  union {
    double f;
    uint64_t i;
  } u;

  if (isnan(f)) {
    return STRM_TAG_NAN;
  }
  u.f = f;
  return u.i;
}