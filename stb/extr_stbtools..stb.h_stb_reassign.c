#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__* prevn; scalar_t__ next; } ;
typedef  TYPE_1__ stb__nochildren ;
typedef  scalar_t__ stb__alloc_type ;
struct TYPE_9__ {scalar_t__* prevn; scalar_t__ next; } ;
typedef  TYPE_2__ stb__alloc ;

/* Variables and functions */
 scalar_t__ STB__alloc ; 
 scalar_t__ STB__nochildren ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* stb__get_context (void*) ; 
 scalar_t__ stb__identify (void*) ; 
 int /*<<< orphan*/  stb__insert_alloc (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stb__insert_nochild (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__** stb__prevn (scalar_t__) ; 

void stb_reassign(void *new_context, void *ptr)
{
   stb__alloc *src = stb__get_context(new_context);

   stb__alloc_type t = stb__identify(ptr);
   assert(t == STB__alloc || t == STB__nochildren);

   if (t == STB__alloc) {
      stb__alloc *s = (stb__alloc *) ptr - 1;

      // unlink from old
      *(s->prevn) = s->next;
      if (s->next)
         *stb__prevn(s->next) = s->prevn;

      stb__insert_alloc(src, s);
   } else {
      stb__nochildren *s = (stb__nochildren *) ptr - 1;

      // unlink from old
      *(s->prevn) = s->next;
      if (s->next)
         *stb__prevn(s->next) = s->prevn;

      stb__insert_nochild(src, s);
   }
}