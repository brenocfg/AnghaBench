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
typedef  int stb_uint32 ;
struct TYPE_2__ {size_t size; int line; char* file; int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 int /*<<< orphan*/ * STB_DEL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ stb__alloc_count ; 
 scalar_t__ stb__alloc_limit ; 
 int stb__alloc_mask ; 
 TYPE_1__* stb__allocations ; 
 int /*<<< orphan*/  stb__grow_alloc () ; 
 int stb_hashptr (void*) ; 
 int stb_rehash (int) ; 

__attribute__((used)) static void stb__add_alloc(void *p, size_t sz, char *file, int line)
{
   stb_uint32 h;
   int n;
   if (stb__alloc_count >= stb__alloc_limit)
      stb__grow_alloc();
   h = stb_hashptr(p);
   n = h & stb__alloc_mask;
   if (stb__allocations[n].p > STB_DEL) {
      int s = stb_rehash(h)|1;
      do {
         n = (n+s) & stb__alloc_mask;
      } while (stb__allocations[n].p > STB_DEL);
   }
   assert(stb__allocations[n].p == NULL || stb__allocations[n].p == STB_DEL);
   stb__allocations[n].p = p;
   stb__allocations[n].size = sz;
   stb__allocations[n].line = line;
   stb__allocations[n].file = file;
   ++stb__alloc_count;
}