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
 double log1p (double const) ; 

double THLog1p(const double x)
{
#if (defined(_MSC_VER) || defined(__MINGW32__))
  volatile double y = 1 + x;
  return log(y) - ((y-1)-x)/y ;  /* cancels errors with IEEE arithmetic */
#else
  return log1p(x);
#endif
}