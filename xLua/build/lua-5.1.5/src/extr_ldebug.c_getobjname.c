#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {TYPE_2__* p; } ;
struct TYPE_9__ {TYPE_1__ l; } ;
struct TYPE_8__ {int /*<<< orphan*/ * upvalues; int /*<<< orphan*/ * k; } ;
typedef  TYPE_2__ Proto ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  int /*<<< orphan*/  CallInfo ;

/* Variables and functions */
 int GETARG_A (int /*<<< orphan*/ ) ; 
 int GETARG_B (int /*<<< orphan*/ ) ; 
 int GETARG_Bx (int /*<<< orphan*/ ) ; 
 int GETARG_C (int /*<<< orphan*/ ) ; 
 int GET_OPCODE (int /*<<< orphan*/ ) ; 
#define  OP_GETGLOBAL 132 
#define  OP_GETTABLE 131 
#define  OP_GETUPVAL 130 
#define  OP_MOVE 129 
#define  OP_SELF 128 
 TYPE_6__* ci_func (int /*<<< orphan*/ *) ; 
 int currentpc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* getstr (int /*<<< orphan*/ ) ; 
 scalar_t__ isLua (int /*<<< orphan*/ *) ; 
 char* kname (TYPE_2__*,int) ; 
 char* luaF_getlocalname (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 char* svalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbexec (TYPE_2__*,int,int) ; 
 int ttisstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *getobjname (lua_State *L, CallInfo *ci, int stackpos,
                               const char **name) {
  if (isLua(ci)) {  /* a Lua function? */
    Proto *p = ci_func(ci)->l.p;
    int pc = currentpc(L, ci);
    Instruction i;
    *name = luaF_getlocalname(p, stackpos+1, pc);
    if (*name)  /* is a local? */
      return "local";
    i = symbexec(p, pc, stackpos);  /* try symbolic execution */
    lua_assert(pc != -1);
    switch (GET_OPCODE(i)) {
      case OP_GETGLOBAL: {
        int g = GETARG_Bx(i);  /* global index */
        lua_assert(ttisstring(&p->k[g]));
        *name = svalue(&p->k[g]);
        return "global";
      }
      case OP_MOVE: {
        int a = GETARG_A(i);
        int b = GETARG_B(i);  /* move from `b' to `a' */
        if (b < a)
          return getobjname(L, ci, b, name);  /* get name for `b' */
        break;
      }
      case OP_GETTABLE: {
        int k = GETARG_C(i);  /* key index */
        *name = kname(p, k);
        return "field";
      }
      case OP_GETUPVAL: {
        int u = GETARG_B(i);  /* upvalue index */
        *name = p->upvalues ? getstr(p->upvalues[u]) : "?";
        return "upvalue";
      }
      case OP_SELF: {
        int k = GETARG_C(i);  /* key index */
        *name = kname(p, k);
        return "method";
      }
      default: break;
    }
  }
  return NULL;  /* no useful name found */
}