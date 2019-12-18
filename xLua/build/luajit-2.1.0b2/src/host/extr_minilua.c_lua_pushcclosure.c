#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ top; } ;
typedef  TYPE_2__ lua_State ;
typedef  int /*<<< orphan*/  lua_CFunction ;
struct TYPE_14__ {int /*<<< orphan*/ * upvalue; int /*<<< orphan*/  f; } ;
struct TYPE_16__ {TYPE_1__ c; } ;
typedef  TYPE_3__ Closure ;

/* Variables and functions */
 int /*<<< orphan*/  api_checknelems (TYPE_2__*,int) ; 
 int /*<<< orphan*/  api_incr_top (TYPE_2__*) ; 
 int /*<<< orphan*/  getcurrenv (TYPE_2__*) ; 
 int /*<<< orphan*/  luaC_checkGC (TYPE_2__*) ; 
 TYPE_3__* luaF_newCclosure (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setclvalue (TYPE_2__*,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  setobj (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void lua_pushcclosure(lua_State*L,lua_CFunction fn,int n){
Closure*cl;
luaC_checkGC(L);
api_checknelems(L,n);
cl=luaF_newCclosure(L,n,getcurrenv(L));
cl->c.f=fn;
L->top-=n;
while(n--)
setobj(L,&cl->c.upvalue[n],L->top+n);
setclvalue(L,L->top,cl);
api_incr_top(L);
}