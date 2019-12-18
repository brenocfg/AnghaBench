#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ k; } ;
typedef  TYPE_2__ expdesc ;
struct TYPE_22__ {int nactvar; int freereg; } ;
struct TYPE_19__ {char token; } ;
struct TYPE_21__ {TYPE_1__ t; TYPE_4__* fs; } ;
typedef  TYPE_3__ LexState ;
typedef  TYPE_4__ FuncState ;

/* Variables and functions */
 int GETARG_A (int /*<<< orphan*/ ) ; 
 int LUA_MULTRET ; 
 int /*<<< orphan*/  OP_TAILCALL ; 
 int /*<<< orphan*/  SET_OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VCALL ; 
 scalar_t__ block_follow (TYPE_3__*,int) ; 
 int explist (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  getinstruction (TYPE_4__*,TYPE_2__*) ; 
 scalar_t__ hasmultret (scalar_t__) ; 
 int luaK_exp2anyreg (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_exp2nextreg (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_ret (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  luaK_setmultret (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  testnext (TYPE_3__*,char) ; 

__attribute__((used)) static void retstat (LexState *ls) {
  /* stat -> RETURN [explist] [';'] */
  FuncState *fs = ls->fs;
  expdesc e;
  int first, nret;  /* registers with returned values */
  if (block_follow(ls, 1) || ls->t.token == ';')
    first = nret = 0;  /* return no values */
  else {
    nret = explist(ls, &e);  /* optional return values */
    if (hasmultret(e.k)) {
      luaK_setmultret(fs, &e);
      if (e.k == VCALL && nret == 1) {  /* tail call? */
        SET_OPCODE(getinstruction(fs,&e), OP_TAILCALL);
        lua_assert(GETARG_A(getinstruction(fs,&e)) == fs->nactvar);
      }
      first = fs->nactvar;
      nret = LUA_MULTRET;  /* return all values */
    }
    else {
      if (nret == 1)  /* only one single value? */
        first = luaK_exp2anyreg(fs, &e);
      else {
        luaK_exp2nextreg(fs, &e);  /* values must go to the stack */
        first = fs->nactvar;  /* return all active values */
        lua_assert(nret == fs->freereg - first);
      }
    }
  }
  luaK_ret(fs, first, nret);
  testnext(ls, ';');  /* skip optional semicolon */
}