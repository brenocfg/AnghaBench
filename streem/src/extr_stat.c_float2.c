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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double,double) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strm_ary_new (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strm_float_value (double) ; 

__attribute__((used)) static strm_value
float2(double m, double s)
{
  strm_value buf[2];

  fprintf(stderr, "f2[%f, %f]\n", m, s);
  buf[0] = strm_float_value(m);
  buf[1] = strm_float_value(s);
  return strm_ary_new(buf, 2);
}