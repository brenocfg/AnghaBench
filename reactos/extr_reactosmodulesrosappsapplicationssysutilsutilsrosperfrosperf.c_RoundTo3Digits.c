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

__attribute__((used)) static double
RoundTo3Digits(double d)
{
  /* It's kind of silly to print out things like ``193658.4/sec'' so just
     junk all but 3 most significant digits. */

  double exponent, sign;

  exponent = 1.0;
  /* the code below won't work if d should happen to be non-positive. */
  if (d < 0.0)
    {
      d = -d;
      sign = -1.0;
    }
  else
    {
      sign = 1.0;
    }

  if (1000.0 <= d)
    {
      do
        {
          exponent *= 10.0;
        }
      while (1000.0 <= d / exponent);
      d = (double)((int)(d / exponent + 0.5));
      d *= exponent;
    }
  else
    {
      if (0.0 != d)
        {
          while (d * exponent < 100.0)
            {
              exponent *= 10.0;
            }
        }
      d = (double)((int)(d * exponent + 0.5));
      d /= exponent;
    }

  return d * sign;
}