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
 double pow (double,double const) ; 

__attribute__((used)) static double QualityToJPEGCompression(double c, double alpha) {
  // We map the complexity 'alpha' and quality setting 'c' to a compression
  // exponent empirically matched to the compression curve of libjpeg6b.
  // On average, the WebP output size will be roughly similar to that of a
  // JPEG file compressed with same quality factor.
  const double amin = 0.30;
  const double amax = 0.85;
  const double exp_min = 0.4;
  const double exp_max = 0.9;
  const double slope = (exp_min - exp_max) / (amax - amin);
  // Linearly interpolate 'expn' from exp_min to exp_max
  // in the [amin, amax] range.
  const double expn = (alpha > amax) ? exp_min
                    : (alpha < amin) ? exp_max
                    : exp_max + slope * (alpha - amin);
  const double v = pow(c, expn);
  return v;
}