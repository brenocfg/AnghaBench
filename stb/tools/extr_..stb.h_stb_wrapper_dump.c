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
struct TYPE_2__ {scalar_t__ p; int line; char* file; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ STB_DEL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,scalar_t__,int,int,char*) ; 
 int stb__alloc_size ; 
 TYPE_1__* stb__allocations ; 
 int /*<<< orphan*/ * stb_p_fopen (char*,char*) ; 

void stb_wrapper_dump(char *filename)
{
   int i;
   FILE *f = stb_p_fopen(filename, "w");
   if (!f) return;
   for (i=0; i < stb__alloc_size; ++i)
      if (stb__allocations[i].p > STB_DEL)
         fprintf(f, "%p %7d - %4d %s\n",
            stb__allocations[i].p   , (int) stb__allocations[i].size,
            stb__allocations[i].line, stb__allocations[i].file);
}