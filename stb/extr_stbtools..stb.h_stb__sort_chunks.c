#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ data_left; struct TYPE_4__* next; } ;
typedef  TYPE_1__ stb__chunk ;
typedef  int /*<<< orphan*/  stb__alloc ;

/* Variables and functions */
 TYPE_1__* stb__chunks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stb__setchunks (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void stb__sort_chunks(stb__alloc *src)
{
   // of the first two chunks, put the chunk with more data left in it first
   stb__chunk *c = stb__chunks(src), *d;
   if (c == NULL) return;
   d = c->next;
   if (d == NULL) return;
   if (c->data_left > d->data_left) return;

   c->next = d->next;
   d->next = c;
   stb__setchunks(src, d);
}