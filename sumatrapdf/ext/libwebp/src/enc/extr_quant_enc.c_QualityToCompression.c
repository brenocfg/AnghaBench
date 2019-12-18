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
 double pow (double const,int) ; 

__attribute__((used)) static double QualityToCompression(double c) {
  const double linear_c = (c < 0.75) ? c * (2. / 3.) : 2. * c - 1.;
  // The file size roughly scales as pow(quantizer, 3.). Actually, the
  // exponent is somewhere between 2.8 and 3.2, but we're mostly interested
  // in the mid-quant range. So we scale the compressibility inversely to
  // this power-law: quant ~= compression ^ 1/3. This law holds well for
  // low quant. Finer modeling for high-quant would make use of kAcTable[]
  // more explicitly.
  const double v = pow(linear_c, 1 / 3.);
  return v;
}