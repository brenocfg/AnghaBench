#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int GCthreshold; int totalbytes; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  gt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaH_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaS_fix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaS_newliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaS_resize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaT_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaX_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  registry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sethvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void f_luaopen(lua_State*L,void*ud){
global_State*g=G(L);
UNUSED(ud);
stack_init(L,L);
sethvalue(L,gt(L),luaH_new(L,0,2));
sethvalue(L,registry(L),luaH_new(L,0,2));
luaS_resize(L,32);
luaT_init(L);
luaX_init(L);
luaS_fix(luaS_newliteral(L,"not enough memory"));
g->GCthreshold=4*g->totalbytes;
}