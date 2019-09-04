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
typedef  int stb_uint ;

/* Variables and functions */

int     stb_size_ranged(int b, stb_uint n)
{
   if (n > (1 << 24)) return 4;
   if (n > (1 << 16)) return 3;
   if (n > (1 <<  8)) return 2;
   return 1;
}