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
 double __ieee754_j0 (double) ; 
 int /*<<< orphan*/ * _errno () ; 
 int /*<<< orphan*/  _finite (double) ; 

double _j0(double num)
{
  if (!_finite(num)) *_errno() = EDOM;
  return __ieee754_j0(num);
}