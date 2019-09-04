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
typedef  int /*<<< orphan*/  stb_ps ;

/* Variables and functions */
 void** stb_ps_fastlist (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ stb_ps_fastlist_valid (void*) ; 
 int /*<<< orphan*/  stb_ps_find (int /*<<< orphan*/ *,void*) ; 

int stb_ps_subset(stb_ps *bigger, stb_ps *smaller)
{
   int i, listlen;
   void **list = stb_ps_fastlist(smaller, &listlen);
   for(i=0; i < listlen; ++i)
      if (stb_ps_fastlist_valid(list[i]))
         if (!stb_ps_find(bigger, list[i]))
            return 0;
   return 1;
}