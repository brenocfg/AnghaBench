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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {scalar_t__ total; } ;
struct TYPE_5__ {TYPE_1__ gc; int /*<<< orphan*/  allocd; void* (* allocf ) (int /*<<< orphan*/ ,void*,scalar_t__,scalar_t__) ;} ;
typedef  TYPE_2__ global_State ;
typedef  scalar_t__ GCSize ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 int checkptrGC (void*) ; 
 int /*<<< orphan*/  lj_err_mem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 void* stub1 (int /*<<< orphan*/ ,void*,scalar_t__,scalar_t__) ; 

void *lj_mem_realloc(lua_State *L, void *p, GCSize osz, GCSize nsz)
{
  global_State *g = G(L);
  lua_assert((osz == 0) == (p == NULL));
  p = g->allocf(g->allocd, p, osz, nsz);
  if (p == NULL && nsz > 0)
    lj_err_mem(L);
  lua_assert((nsz == 0) == (p == NULL));
  lua_assert(checkptrGC(p));
  g->gc.total = (g->gc.total - osz) + nsz;
  return p;
}