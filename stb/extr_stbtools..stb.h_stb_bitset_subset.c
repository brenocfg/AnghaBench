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
typedef  int stb_bitset ;

/* Variables and functions */

int stb_bitset_subset(stb_bitset *bigger, stb_bitset *smaller, int len)
{
   int i;
   for (i=0; i < len; ++i)
      if ((bigger[i] & smaller[i]) != smaller[i]) return 0;
   return 1;
}