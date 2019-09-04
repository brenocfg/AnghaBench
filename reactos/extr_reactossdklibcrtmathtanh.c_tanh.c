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
 double exp (double) ; 

double tanh(double x)
{
  if (x > 50)
    return 1;
  else if (x < -50)
    return -1;
  else
  {
    const double ebig = exp(x);
    const double esmall = 1.0/ebig;
    return (ebig - esmall) / (ebig + esmall);
  }
}