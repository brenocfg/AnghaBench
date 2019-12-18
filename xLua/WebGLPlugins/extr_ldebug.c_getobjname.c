#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * k; int /*<<< orphan*/ * code; } ;
typedef  TYPE_1__ Proto ;
typedef  int OpCode ;
typedef  int /*<<< orphan*/  Instruction ;

/* Variables and functions */
 int GETARG_A (int /*<<< orphan*/ ) ; 
 int GETARG_Ax (int /*<<< orphan*/ ) ; 
 int GETARG_B (int /*<<< orphan*/ ) ; 
 int GETARG_Bx (int /*<<< orphan*/ ) ; 
 int GETARG_C (int /*<<< orphan*/ ) ; 
 int GET_OPCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LUA_ENV ; 
#define  OP_GETTABLE 134 
#define  OP_GETTABUP 133 
#define  OP_GETUPVAL 132 
#define  OP_LOADK 131 
#define  OP_LOADKX 130 
#define  OP_MOVE 129 
#define  OP_SELF 128 
 int findsetreg (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  kname (TYPE_1__*,int,int,char const**) ; 
 char* luaF_getlocalname (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 char* svalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttisstring (int /*<<< orphan*/ *) ; 
 char* upvalname (TYPE_1__*,int) ; 

__attribute__((used)) static const char *getobjname (Proto *p, int lastpc, int reg,
                               const char **name) {
  int pc;
  *name = luaF_getlocalname(p, reg + 1, lastpc);
  if (*name)  /* is a local? */
    return "local";
  /* else try symbolic execution */
  pc = findsetreg(p, lastpc, reg);
  if (pc != -1) {  /* could find instruction? */
    Instruction i = p->code[pc];
    OpCode op = GET_OPCODE(i);
    switch (op) {
      case OP_MOVE: {
        int b = GETARG_B(i);  /* move from 'b' to 'a' */
        if (b < GETARG_A(i))
          return getobjname(p, pc, b, name);  /* get name for 'b' */
        break;
      }
      case OP_GETTABUP:
      case OP_GETTABLE: {
        int k = GETARG_C(i);  /* key index */
        int t = GETARG_B(i);  /* table index */
        const char *vn = (op == OP_GETTABLE)  /* name of indexed variable */
                         ? luaF_getlocalname(p, t + 1, pc)
                         : upvalname(p, t);
        kname(p, pc, k, name);
        return (vn && strcmp(vn, LUA_ENV) == 0) ? "global" : "field";
      }
      case OP_GETUPVAL: {
        *name = upvalname(p, GETARG_B(i));
        return "upvalue";
      }
      case OP_LOADK:
      case OP_LOADKX: {
        int b = (op == OP_LOADK) ? GETARG_Bx(i)
                                 : GETARG_Ax(p->code[pc + 1]);
        if (ttisstring(&p->k[b])) {
          *name = svalue(&p->k[b]);
          return "constant";
        }
        break;
      }
      case OP_SELF: {
        int k = GETARG_C(i);  /* key index */
        kname(p, pc, k, name);
        return "method";
      }
      default: break;  /* go through to return NULL */
    }
  }
  return NULL;  /* could not find reasonable name */
}