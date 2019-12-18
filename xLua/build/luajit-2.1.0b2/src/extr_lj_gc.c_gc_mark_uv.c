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
struct TYPE_4__ {int /*<<< orphan*/  uvhead; } ;
typedef  TYPE_1__ global_State ;
typedef  int /*<<< orphan*/  GCupval ;

/* Variables and functions */
 int /*<<< orphan*/  gc_marktv (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ isgray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uvnext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uvprev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvval (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gc_mark_uv(global_State *g)
{
  GCupval *uv;
  for (uv = uvnext(&g->uvhead); uv != &g->uvhead; uv = uvnext(uv)) {
    lua_assert(uvprev(uvnext(uv)) == uv && uvnext(uvprev(uv)) == uv);
    if (isgray(obj2gco(uv)))
      gc_marktv(g, uvval(uv));
  }
}