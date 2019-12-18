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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int IROp ;

/* Variables and functions */
#define  IR_EQ 137 
#define  IR_GE 136 
#define  IR_GT 135 
#define  IR_LE 134 
#define  IR_LT 133 
#define  IR_NE 132 
#define  IR_UGE 131 
#define  IR_UGT 130 
#define  IR_ULE 129 
#define  IR_ULT 128 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 

int lj_ir_numcmp(lua_Number a, lua_Number b, IROp op)
{
  switch (op) {
  case IR_EQ: return (a == b);
  case IR_NE: return (a != b);
  case IR_LT: return (a < b);
  case IR_GE: return (a >= b);
  case IR_LE: return (a <= b);
  case IR_GT: return (a > b);
  case IR_ULT: return !(a >= b);
  case IR_UGE: return !(a < b);
  case IR_ULE: return !(a > b);
  case IR_UGT: return !(a <= b);
  default: lua_assert(0); return 0;
  }
}