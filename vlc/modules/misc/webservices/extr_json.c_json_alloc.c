#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ max_memory; } ;
struct TYPE_5__ {unsigned long ulong_max; unsigned long used_memory; TYPE_1__ settings; } ;
typedef  TYPE_2__ json_state ;

/* Variables and functions */
 void* calloc (unsigned long,int) ; 
 void* malloc (unsigned long) ; 

__attribute__((used)) static void * json_alloc (json_state * state, unsigned long size, int zero)
{
   void * mem;

   if ((state->ulong_max - state->used_memory) < size)
      return 0;

   if (state->settings.max_memory
         && (state->used_memory += size) > state->settings.max_memory)
   {
      return 0;
   }

   if (! (mem = zero ? calloc (size, 1) : malloc (size)))
      return 0;

   return mem;
}