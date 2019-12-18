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
struct LexState {int /*<<< orphan*/ * buff; } ;
struct FuncState {TYPE_1__* f; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  ZIO ;
struct TYPE_3__ {int is_vararg; } ;
typedef  TYPE_1__ Proto ;
typedef  int /*<<< orphan*/  Mbuffer ;

/* Variables and functions */
 int /*<<< orphan*/  TK_EOS ; 
 int /*<<< orphan*/  check (struct LexState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk (struct LexState*) ; 
 int /*<<< orphan*/  close_func (struct LexState*) ; 
 int /*<<< orphan*/  luaS_new (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  luaX_next (struct LexState*) ; 
 int /*<<< orphan*/  luaX_setinput (int /*<<< orphan*/ *,struct LexState*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_func (struct LexState*,struct FuncState*) ; 

__attribute__((used)) static Proto*luaY_parser(lua_State*L,ZIO*z,Mbuffer*buff,const char*name){
struct LexState lexstate;
struct FuncState funcstate;
lexstate.buff=buff;
luaX_setinput(L,&lexstate,z,luaS_new(L,name));
open_func(&lexstate,&funcstate);
funcstate.f->is_vararg=2;
luaX_next(&lexstate);
chunk(&lexstate);
check(&lexstate,TK_EOS);
close_func(&lexstate);
return funcstate.f;
}