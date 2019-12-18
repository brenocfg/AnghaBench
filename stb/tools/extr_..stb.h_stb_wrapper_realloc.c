#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  line; int /*<<< orphan*/  file; int /*<<< orphan*/  size; } ;
struct TYPE_3__ {size_t size; char* file; int line; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb__add_alloc (void*,size_t,char*,int) ; 
 TYPE_2__* stb__alloc_history ; 
 TYPE_1__* stb__allocations ; 
 int stb__hashfind (void*) ; 
 int stb__historyfind (void*) ; 
 int /*<<< orphan*/  stb__remove_alloc (int,char*,int) ; 
 int /*<<< orphan*/  stb_fatal (char*,void*,char*,...) ; 
 int /*<<< orphan*/  stb_wrapper_malloc (void*,size_t,char*,int) ; 

void stb_wrapper_realloc(void *p, void *q, size_t sz, char *file, int line)
{
   int n;
   if (p == NULL) { stb_wrapper_malloc(q, sz, file, line); return; }
   if (q == NULL) return; // nothing happened

   n = stb__hashfind(p);
   if (n == -1) {
      // tried to free something we hadn't allocated!
      // this is weird, though, because we got past the realloc!
      n = stb__historyfind(p);
      assert(0); /* NOTREACHED */
      if (n >= 0)
         stb_fatal("Attempted to realloc %d-byte block %p at %s:%d previously freed/realloced at %s:%d",
                       stb__alloc_history[n].size, p,
                       file, line,
                       stb__alloc_history[n].file, stb__alloc_history[n].line);
      else
         stb_fatal("Attempted to realloc unknown block %p at %s:%d", p, file,line);
   } else {
      if (q == p) {
         stb__allocations[n].size = sz;
         stb__allocations[n].file = file;
         stb__allocations[n].line = line;
      } else {
         stb__remove_alloc(n, file, line);
         stb__add_alloc(q,sz,file,line);
      }
   }
}