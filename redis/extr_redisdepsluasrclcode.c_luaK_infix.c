#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  expdesc ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  int BinOpr ;

/* Variables and functions */
#define  OPR_ADD 136 
#define  OPR_AND 135 
#define  OPR_CONCAT 134 
#define  OPR_DIV 133 
#define  OPR_MOD 132 
#define  OPR_MUL 131 
#define  OPR_OR 130 
#define  OPR_POW 129 
#define  OPR_SUB 128 
 int /*<<< orphan*/  isnumeral (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_exp2RK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_exp2nextreg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_goiffalse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_goiftrue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void luaK_infix (FuncState *fs, BinOpr op, expdesc *v) {
  switch (op) {
    case OPR_AND: {
      luaK_goiftrue(fs, v);
      break;
    }
    case OPR_OR: {
      luaK_goiffalse(fs, v);
      break;
    }
    case OPR_CONCAT: {
      luaK_exp2nextreg(fs, v);  /* operand must be on the `stack' */
      break;
    }
    case OPR_ADD: case OPR_SUB: case OPR_MUL: case OPR_DIV:
    case OPR_MOD: case OPR_POW: {
      if (!isnumeral(v)) luaK_exp2RK(fs, v);
      break;
    }
    default: {
      luaK_exp2RK(fs, v);
      break;
    }
  }
}