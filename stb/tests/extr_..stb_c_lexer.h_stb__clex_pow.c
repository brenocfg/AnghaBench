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

__attribute__((used)) static double stb__clex_pow(double base, unsigned int exponent)
{
   double value=1;
   for ( ; exponent; exponent >>= 1) {
      if (exponent & 1)
         value *= base;
      base *= base;
   }
   return value;
}