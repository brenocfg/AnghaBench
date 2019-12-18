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
 scalar_t__ malloc (int) ; 

stb_bitset *stb_bitset_new(int value, int len)
{
   int i;
   stb_bitset *d = (stb_bitset *) malloc(sizeof(*d) * len);
   if (value) value = 0xffffffff;
   for (i=0; i < len; ++i) d[i] = value;
   return d;
}