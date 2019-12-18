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
typedef  int uint32 ;

/* Variables and functions */
 scalar_t__ ldexp (float,int) ; 

__attribute__((used)) static float float32_unpack(uint32 x)
{
   // from the specification
   uint32 mantissa = x & 0x1fffff;
   uint32 sign = x & 0x80000000;
   uint32 exp = (x & 0x7fe00000) >> 21;
   double res = sign ? -(double)mantissa : (double)mantissa;
   return (float) ldexp((float)res, exp-788);
}