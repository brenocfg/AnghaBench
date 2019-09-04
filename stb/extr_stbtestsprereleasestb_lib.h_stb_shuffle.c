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
 int stb_randLCG () ; 
 unsigned long stb_srandLCG (unsigned long) ; 
 int /*<<< orphan*/  stb_swap (char*,char*,size_t) ; 

void stb_shuffle(void *p, size_t n, size_t sz, unsigned long seed)
{
   char *a;
   unsigned long old_seed;
   int i;
   if (seed)
      old_seed = stb_srandLCG(seed);
   a = (char *) p + (n-1) * sz;

   for (i=n; i > 1; --i) {
      int j = stb_randLCG() % i;
      stb_swap(a, (char *) p + j * sz, sz);
      a -= sz;
   }
   if (seed)
      stb_srandLCG(old_seed);
}