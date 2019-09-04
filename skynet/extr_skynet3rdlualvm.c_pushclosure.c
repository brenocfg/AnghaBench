#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_13__ {size_t idx; scalar_t__ instack; } ;
typedef  TYPE_2__ Upvaldesc ;
struct TYPE_14__ {int /*<<< orphan*/  refcount; } ;
typedef  TYPE_3__ UpVal ;
struct TYPE_16__ {TYPE_3__** upvals; TYPE_4__* p; } ;
struct TYPE_15__ {TYPE_5__* cache; TYPE_1__* sp; } ;
struct TYPE_12__ {int sizeupvalues; TYPE_2__* upvalues; } ;
typedef  scalar_t__ StkId ;
typedef  TYPE_4__ Proto ;
typedef  TYPE_5__ LClosure ;

/* Variables and functions */
 int /*<<< orphan*/  isblack (TYPE_4__*) ; 
 TYPE_3__* luaF_findupval (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_5__* luaF_newLclosure (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setclLvalue (int /*<<< orphan*/ *,scalar_t__,TYPE_5__*) ; 

__attribute__((used)) static void pushclosure (lua_State *L, Proto *p, UpVal **encup, StkId base,
                         StkId ra) {
  int nup = p->sp->sizeupvalues;
  Upvaldesc *uv = p->sp->upvalues;
  int i;
  LClosure *ncl = luaF_newLclosure(L, nup);
  ncl->p = p;
  setclLvalue(L, ra, ncl);  /* anchor new closure in stack */
  for (i = 0; i < nup; i++) {  /* fill in its upvalues */
    if (uv[i].instack)  /* upvalue refers to local variable? */
      ncl->upvals[i] = luaF_findupval(L, base + uv[i].idx);
    else  /* get upvalue from enclosing function */
      ncl->upvals[i] = encup[uv[i].idx];
    ncl->upvals[i]->refcount++;
    /* new closure is white, so we do not need a barrier here */
  }
  if (!isblack(p))  /* cache will not break GC invariant? */
    p->cache = ncl;  /* save it on cache for reuse */
}