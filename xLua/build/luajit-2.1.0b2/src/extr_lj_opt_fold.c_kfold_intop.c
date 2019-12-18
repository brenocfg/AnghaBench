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
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int IROp ;

/* Variables and functions */
#define  IR_ADD 142 
#define  IR_BAND 141 
#define  IR_BOR 140 
#define  IR_BROL 139 
#define  IR_BROR 138 
#define  IR_BSAR 137 
#define  IR_BSHL 136 
#define  IR_BSHR 135 
#define  IR_BXOR 134 
#define  IR_MAX 133 
#define  IR_MIN 132 
#define  IR_MOD 131 
#define  IR_MUL 130 
#define  IR_NEG 129 
#define  IR_SUB 128 
 int /*<<< orphan*/  lj_rol (int,int) ; 
 int /*<<< orphan*/  lj_ror (int,int) ; 
 int lj_vm_modi (int,int) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t kfold_intop(int32_t k1, int32_t k2, IROp op)
{
  switch (op) {
  case IR_ADD: k1 += k2; break;
  case IR_SUB: k1 -= k2; break;
  case IR_MUL: k1 *= k2; break;
  case IR_MOD: k1 = lj_vm_modi(k1, k2); break;
  case IR_NEG: k1 = -k1; break;
  case IR_BAND: k1 &= k2; break;
  case IR_BOR: k1 |= k2; break;
  case IR_BXOR: k1 ^= k2; break;
  case IR_BSHL: k1 <<= (k2 & 31); break;
  case IR_BSHR: k1 = (int32_t)((uint32_t)k1 >> (k2 & 31)); break;
  case IR_BSAR: k1 >>= (k2 & 31); break;
  case IR_BROL: k1 = (int32_t)lj_rol((uint32_t)k1, (k2 & 31)); break;
  case IR_BROR: k1 = (int32_t)lj_ror((uint32_t)k1, (k2 & 31)); break;
  case IR_MIN: k1 = k1 < k2 ? k1 : k2; break;
  case IR_MAX: k1 = k1 > k2 ? k1 : k2; break;
  default: lua_assert(0); break;
  }
  return k1;
}