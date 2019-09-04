#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* arena; } ;
typedef  TYPE_1__ stb_sdict ;

/* Variables and functions */
 int /*<<< orphan*/  stb_free (void*) ; 
 int /*<<< orphan*/ * stb_malloc_global (int) ; 
 TYPE_1__* stb_sdictinternal_copy (TYPE_1__*) ; 

stb_sdict* stb_sdict_copy(stb_sdict *old)
{
   stb_sdict *n;
   void *old_arena = old->arena;
   void *new_arena = old_arena ? stb_malloc_global(1) : NULL;
   old->arena = new_arena;
   n = stb_sdictinternal_copy(old);
   old->arena = old_arena;
   if (n)
      n->arena = new_arena;
   else if (new_arena)
      stb_free(new_arena);
   return n;
}