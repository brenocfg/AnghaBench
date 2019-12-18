#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_21__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_4__ lua_State ;
typedef  int /*<<< orphan*/  ZIO ;
struct TYPE_30__ {scalar_t__ n; } ;
struct TYPE_29__ {scalar_t__ n; } ;
struct TYPE_27__ {scalar_t__ n; } ;
struct TYPE_35__ {TYPE_3__ label; TYPE_2__ gt; TYPE_1__ actvar; } ;
struct TYPE_34__ {int nups; int /*<<< orphan*/  prev; TYPE_21__* f; } ;
struct TYPE_33__ {TYPE_21__* p; } ;
struct TYPE_32__ {int /*<<< orphan*/  fs; TYPE_8__* dyd; int /*<<< orphan*/ * buff; int /*<<< orphan*/  h; } ;
struct TYPE_28__ {int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  Mbuffer ;
typedef  TYPE_5__ LexState ;
typedef  TYPE_6__ LClosure ;
typedef  TYPE_7__ FuncState ;
typedef  TYPE_8__ Dyndata ;

/* Variables and functions */
 int iswhite (TYPE_21__*) ; 
 int /*<<< orphan*/  luaD_inctop (TYPE_4__*) ; 
 TYPE_6__* luaF_newLclosure (TYPE_4__*,int) ; 
 TYPE_21__* luaF_newproto (TYPE_4__*) ; 
 int /*<<< orphan*/  luaH_new (TYPE_4__*) ; 
 int /*<<< orphan*/  luaS_new (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  luaX_setinput (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  mainfunc (TYPE_5__*,TYPE_7__*) ; 
 int /*<<< orphan*/  setclLvalue (TYPE_4__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  sethvalue (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

LClosure *luaY_parser (lua_State *L, ZIO *z, Mbuffer *buff,
                       Dyndata *dyd, const char *name, int firstchar) {
  LexState lexstate;
  FuncState funcstate;
  LClosure *cl = luaF_newLclosure(L, 1);  /* create main closure */
  setclLvalue(L, L->top, cl);  /* anchor it (to avoid being collected) */
  luaD_inctop(L);
  lexstate.h = luaH_new(L);  /* create table for scanner */
  sethvalue(L, L->top, lexstate.h);  /* anchor it */
  luaD_inctop(L);
  funcstate.f = cl->p = luaF_newproto(L);
  funcstate.f->source = luaS_new(L, name);  /* create and anchor TString */
  lua_assert(iswhite(funcstate.f));  /* do not need barrier here */
  lexstate.buff = buff;
  lexstate.dyd = dyd;
  dyd->actvar.n = dyd->gt.n = dyd->label.n = 0;
  luaX_setinput(L, &lexstate, z, funcstate.f->source, firstchar);
  mainfunc(&lexstate, &funcstate);
  lua_assert(!funcstate.prev && funcstate.nups == 1 && !lexstate.fs);
  /* all scopes should be correctly finished */
  lua_assert(dyd->actvar.n == 0 && dyd->gt.n == 0 && dyd->label.n == 0);
  L->top--;  /* remove scanner's table */
  return cl;  /* closure is on the stack, too */
}