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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int gcrunning; int /*<<< orphan*/  version; int /*<<< orphan*/  memerrmsg; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEMERRMSG ; 
 int /*<<< orphan*/  MINSTRTABSIZE ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  init_registry (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  luaS_fix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaS_newliteral (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaS_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaT_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaX_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luai_userstateopen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void f_luaopen (lua_State *L, void *ud) {
  global_State *g = G(L);
  UNUSED(ud);
  stack_init(L, L);  /* init stack */
  init_registry(L, g);
  luaS_resize(L, MINSTRTABSIZE);  /* initial size of string table */
  luaT_init(L);
  luaX_init(L);
  /* pre-create memory-error message */
  g->memerrmsg = luaS_newliteral(L, MEMERRMSG);
  luaS_fix(g->memerrmsg);  /* it should never be collected */
  g->gcrunning = 1;  /* allow gc */
  g->version = lua_version(NULL);
  luai_userstateopen(L);
}