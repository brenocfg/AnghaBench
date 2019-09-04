#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* p; } ;

/* Variables and functions */
 int STB_MALLOC_HISTORY_COUNT ; 
 TYPE_1__* stb__alloc_history ; 
 int stb__history_pos ; 

__attribute__((used)) static int stb__historyfind(void *p)
{
   int n = stb__history_pos;
   int i;
   for (i=0; i < STB_MALLOC_HISTORY_COUNT; ++i) {
      if (--n < 0) n = STB_MALLOC_HISTORY_COUNT-1;
      if (stb__alloc_history[n].p == p)
         return n;
   }
   return -1;
}