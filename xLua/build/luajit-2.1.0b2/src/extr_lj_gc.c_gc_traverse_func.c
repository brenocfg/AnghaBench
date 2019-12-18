#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_14__ {scalar_t__ sizeuv; } ;
struct TYPE_15__ {TYPE_4__ uv; } ;
struct TYPE_12__ {size_t nupvalues; int /*<<< orphan*/ * upvalue; int /*<<< orphan*/  env; } ;
struct TYPE_11__ {scalar_t__ nupvalues; int /*<<< orphan*/ * uvptr; } ;
struct TYPE_13__ {TYPE_2__ c; TYPE_1__ l; } ;
typedef  TYPE_3__ GCfunc ;

/* Variables and functions */
 TYPE_4__* funcproto (TYPE_3__*) ; 
 int /*<<< orphan*/  gc_markobj (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  gc_marktv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__* gcref (int /*<<< orphan*/ ) ; 
 scalar_t__ isluafunc (TYPE_3__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 TYPE_4__* tabref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gc_traverse_func(global_State *g, GCfunc *fn)
{
  gc_markobj(g, tabref(fn->c.env));
  if (isluafunc(fn)) {
    uint32_t i;
    lua_assert(fn->l.nupvalues <= funcproto(fn)->sizeuv);
    gc_markobj(g, funcproto(fn));
    for (i = 0; i < fn->l.nupvalues; i++)  /* Mark Lua function upvalues. */
      gc_markobj(g, &gcref(fn->l.uvptr[i])->uv);
  } else {
    uint32_t i;
    for (i = 0; i < fn->c.nupvalues; i++)  /* Mark C function upvalues. */
      gc_marktv(g, &fn->c.upvalue[i]);
  }
}