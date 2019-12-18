#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  top; TYPE_4__* ci; } ;
typedef  TYPE_3__ lua_State ;
struct TYPE_10__ {int base; int /*<<< orphan*/ * savedpc; } ;
struct TYPE_11__ {TYPE_1__ l; } ;
struct TYPE_13__ {int /*<<< orphan*/  top; TYPE_2__ u; } ;
typedef  int StkId ;
typedef  int OpCode ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  TYPE_4__ CallInfo ;

/* Variables and functions */
 int GETARG_A (int /*<<< orphan*/ ) ; 
 int GETARG_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GETARG_C (int /*<<< orphan*/ ) ; 
 int GET_OPCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISK (int) ; 
#define  OP_ADD 147 
#define  OP_CALL 146 
#define  OP_CONCAT 145 
#define  OP_DIV 144 
#define  OP_EQ 143 
#define  OP_GETTABLE 142 
#define  OP_GETTABUP 141 
 int OP_JMP ; 
#define  OP_LE 140 
#define  OP_LEN 139 
#define  OP_LT 138 
#define  OP_MOD 137 
#define  OP_MUL 136 
#define  OP_POW 135 
#define  OP_SELF 134 
#define  OP_SETTABLE 133 
#define  OP_SETTABUP 132 
#define  OP_SUB 131 
#define  OP_TAILCALL 130 
#define  OP_TFORCALL 129 
 int OP_TFORLOOP ; 
#define  OP_UNM 128 
 int /*<<< orphan*/  TM_LE ; 
 int cast_int (scalar_t__) ; 
 int /*<<< orphan*/  l_isfalse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaT_gettmbyobj (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaV_concat (TYPE_3__*,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setobj2s (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  setobjs2s (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttisnil (int /*<<< orphan*/ ) ; 

void luaV_finishOp (lua_State *L) {
  CallInfo *ci = L->ci;
  StkId base = ci->u.l.base;
  Instruction inst = *(ci->u.l.savedpc - 1);  /* interrupted instruction */
  OpCode op = GET_OPCODE(inst);
  switch (op) {  /* finish its execution */
    case OP_ADD: case OP_SUB: case OP_MUL: case OP_DIV:
    case OP_MOD: case OP_POW: case OP_UNM: case OP_LEN:
    case OP_GETTABUP: case OP_GETTABLE: case OP_SELF: {
      setobjs2s(L, base + GETARG_A(inst), --L->top);
      break;
    }
    case OP_LE: case OP_LT: case OP_EQ: {
      int res = !l_isfalse(L->top - 1);
      L->top--;
      /* metamethod should not be called when operand is K */
      lua_assert(!ISK(GETARG_B(inst)));
      if (op == OP_LE &&  /* "<=" using "<" instead? */
          ttisnil(luaT_gettmbyobj(L, base + GETARG_B(inst), TM_LE)))
        res = !res;  /* invert result */
      lua_assert(GET_OPCODE(*ci->u.l.savedpc) == OP_JMP);
      if (res != GETARG_A(inst))  /* condition failed? */
        ci->u.l.savedpc++;  /* skip jump instruction */
      break;
    }
    case OP_CONCAT: {
      StkId top = L->top - 1;  /* top when 'call_binTM' was called */
      int b = GETARG_B(inst);      /* first element to concatenate */
      int total = cast_int(top - 1 - (base + b));  /* yet to concatenate */
      setobj2s(L, top - 2, top);  /* put TM result in proper position */
      if (total > 1) {  /* are there elements to concat? */
        L->top = top - 1;  /* top is one after last element (at top-2) */
        luaV_concat(L, total);  /* concat them (may yield again) */
      }
      /* move final result to final position */
      setobj2s(L, ci->u.l.base + GETARG_A(inst), L->top - 1);
      L->top = ci->top;  /* restore top */
      break;
    }
    case OP_TFORCALL: {
      lua_assert(GET_OPCODE(*ci->u.l.savedpc) == OP_TFORLOOP);
      L->top = ci->top;  /* correct top */
      break;
    }
    case OP_CALL: {
      if (GETARG_C(inst) - 1 >= 0)  /* nresults >= 0? */
        L->top = ci->top;  /* adjust results */
      break;
    }
    case OP_TAILCALL: case OP_SETTABUP: case OP_SETTABLE:
      break;
    default: lua_assert(0);
  }
}