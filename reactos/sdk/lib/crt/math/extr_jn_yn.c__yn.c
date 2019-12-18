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

/* Variables and functions */
 int /*<<< orphan*/  EDOM ; 
 scalar_t__ _FPCLASS_NINF ; 
 double __ieee754_yn (int,double) ; 
 int /*<<< orphan*/ * _errno () ; 
 int /*<<< orphan*/  _finite (double) ; 
 scalar_t__ _fpclass (double) ; 
 double sqrt (int) ; 

double _yn(int order, double num)
{
  double retval;
  if (!_finite(num)) *_errno() = EDOM;
  retval  = __ieee754_yn(order,num);
  if (_fpclass(retval) == _FPCLASS_NINF)
  {
    *_errno() = EDOM;
    retval = sqrt(-1);
  }
  return retval;
}