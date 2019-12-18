#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_20__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_5__ lua_State ;
typedef  int /*<<< orphan*/  ZIO ;
struct TYPE_25__ {TYPE_20__* p; } ;
struct TYPE_34__ {TYPE_1__ l; } ;
struct TYPE_29__ {scalar_t__ n; } ;
struct TYPE_28__ {scalar_t__ n; } ;
struct TYPE_27__ {scalar_t__ n; } ;
struct TYPE_33__ {TYPE_4__ label; TYPE_3__ gt; TYPE_2__ actvar; } ;
struct TYPE_32__ {int nups; int /*<<< orphan*/  prev; TYPE_20__* f; } ;
struct TYPE_31__ {int /*<<< orphan*/  fs; TYPE_8__* dyd; int /*<<< orphan*/ * buff; } ;
struct TYPE_26__ {int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  Mbuffer ;
typedef  TYPE_6__ LexState ;
typedef  TYPE_7__ FuncState ;
typedef  TYPE_8__ Dyndata ;
typedef  TYPE_9__ Closure ;

/* Variables and functions */
 int /*<<< orphan*/  incr_top (TYPE_5__*) ; 
 TYPE_9__* luaF_newLclosure (TYPE_5__*,int) ; 
 TYPE_20__* luaF_newproto (TYPE_5__*) ; 
 int /*<<< orphan*/  luaS_new (TYPE_5__*,char const*) ; 
 int /*<<< orphan*/  luaX_setinput (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  mainfunc (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  setclLvalue (TYPE_5__*,int /*<<< orphan*/ ,TYPE_9__*) ; 

Closure *luaY_parser (lua_State *L, ZIO *z, Mbuffer *buff,
                      Dyndata *dyd, const char *name, int firstchar) {
  LexState lexstate;
  FuncState funcstate;
  Closure *cl = luaF_newLclosure(L, 1);  /* create main closure */
  /* anchor closure (to avoid being collected) */
  setclLvalue(L, L->top, cl);
  incr_top(L);
  funcstate.f = cl->l.p = luaF_newproto(L);
  funcstate.f->source = luaS_new(L, name);  /* create and anchor TString */
  lexstate.buff = buff;
  lexstate.dyd = dyd;
  dyd->actvar.n = dyd->gt.n = dyd->label.n = 0;
  luaX_setinput(L, &lexstate, z, funcstate.f->source, firstchar);
  mainfunc(&lexstate, &funcstate);
  lua_assert(!funcstate.prev && funcstate.nups == 1 && !lexstate.fs);
  /* all scopes should be correctly finished */
  lua_assert(dyd->actvar.n == 0 && dyd->gt.n == 0 && dyd->label.n == 0);
  return cl;  /* it's on the stack too */
}