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

int stb_lowbit8(unsigned int n)
{
   static signed char lowbit4[16] = { -1,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0 };
   int k = lowbit4[n & 15];
   if (k >= 0) return k;
   k = lowbit4[(n >> 4) & 15];
   if (k >= 0) return k+4;
   return k;
}