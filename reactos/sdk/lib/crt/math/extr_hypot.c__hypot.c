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
 double __SQRT_DBL_MAX ; 
 double __SQRT_DBL_MIN ; 
 double fabs (double) ; 
 double sqrt (double) ; 

double
_hypot(double x, double y)
{
  double abig = fabs(x), asmall = fabs(y);
  double ratio;

  /* Make abig = max(|x|, |y|), asmall = min(|x|, |y|).  */
  if (abig < asmall)
    {
      double temp = abig;

      abig = asmall;
      asmall = temp;
    }

  /* Trivial case.  */
  if (asmall == 0.)
    return abig;

  /* Scale the numbers as much as possible by using its ratio.
     For example, if both ABIG and ASMALL are VERY small, then
     X^2 + Y^2 might be VERY inaccurate due to loss of
     significant digits.  Dividing ASMALL by ABIG scales them
     to a certain degree, so that accuracy is better.  */

  if ((ratio = asmall / abig) > __SQRT_DBL_MIN && abig < __SQRT_DBL_MAX)
    return abig * sqrt(1.0 + ratio*ratio);
  else
    {
      /* Slower but safer algorithm due to Moler and Morrison.  Never
         produces any intermediate result greater than roughly the
         larger of X and Y.  Should converge to machine-precision
         accuracy in 3 iterations.  */

      double r = ratio*ratio, t, s, p = abig, q = asmall;

      do {
        t = 4. + r;
        if (t == 4.)
          break;
        s = r / t;
        p += 2. * s * p;
        q *= s;
        r = (q / p) * (q / p);
      } while (1);

      return p;
    }
}