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
struct LexState {int /*<<< orphan*/ * fs; int /*<<< orphan*/ * buff; } ;
struct FuncState {TYPE_1__* f; int /*<<< orphan*/ * prev; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  ZIO ;
struct TYPE_3__ {scalar_t__ nups; int /*<<< orphan*/  is_vararg; } ;
typedef  TYPE_1__ Proto ;
typedef  int /*<<< orphan*/  Mbuffer ;

/* Variables and functions */
 int /*<<< orphan*/  TK_EOS ; 
 int /*<<< orphan*/  VARARG_ISVARARG ; 
 int /*<<< orphan*/  check (struct LexState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk (struct LexState*) ; 
 int /*<<< orphan*/  close_func (struct LexState*) ; 
 int /*<<< orphan*/  luaS_new (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  luaX_next (struct LexState*) ; 
 int /*<<< orphan*/  luaX_setinput (int /*<<< orphan*/ *,struct LexState*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  open_func (struct LexState*,struct FuncState*) ; 

Proto *luaY_parser (lua_State *L, ZIO *z, Mbuffer *buff, const char *name) {
  struct LexState lexstate;
  struct FuncState funcstate;
  lexstate.buff = buff;
  luaX_setinput(L, &lexstate, z, luaS_new(L, name));
  open_func(&lexstate, &funcstate);
  funcstate.f->is_vararg = VARARG_ISVARARG;  /* main func. is always vararg */
  luaX_next(&lexstate);  /* read first token */
  chunk(&lexstate);
  check(&lexstate, TK_EOS);
  close_func(&lexstate);
  lua_assert(funcstate.prev == NULL);
  lua_assert(funcstate.f->nups == 0);
  lua_assert(lexstate.fs == NULL);
  return funcstate.f;
}