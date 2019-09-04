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
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  stb__arr_addlen_ (void**,int,int) ; 
 int stb_arr_len2 (void*) ; 

void stb__arr_insertn_(void **pp, int size, int i, int n)
{
   void *p = *pp;
   if (n) {
      int z;

      if (p == NULL) {
         stb__arr_addlen_(pp, size, n);
         return;
      }

      z = stb_arr_len2(p);
      stb__arr_addlen_(&p, size, n);
      memmove((char *) p + (i+n)*size, (char *) p + i*size, size * (z-i));
   }
   *pp = p;
}