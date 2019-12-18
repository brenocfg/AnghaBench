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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int IROp ;

/* Variables and functions */
#define  IR_ADD 138 
#define  IR_BAND 137 
#define  IR_BOR 136 
#define  IR_BROL 135 
#define  IR_BROR 134 
#define  IR_BSAR 133 
#define  IR_BSHL 132 
#define  IR_BSHR 131 
#define  IR_BXOR 130 
#define  IR_MUL 129 
#define  IR_SUB 128 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  lj_rol (int,int) ; 
 int /*<<< orphan*/  lj_ror (int,int) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t kfold_int64arith(uint64_t k1, uint64_t k2, IROp op)
{
  switch (op) {
#if LJ_HASFFI
  case IR_ADD: k1 += k2; break;
  case IR_SUB: k1 -= k2; break;
  case IR_MUL: k1 *= k2; break;
  case IR_BAND: k1 &= k2; break;
  case IR_BOR: k1 |= k2; break;
  case IR_BXOR: k1 ^= k2; break;
  case IR_BSHL: k1 <<= (k2 & 63); break;
  case IR_BSHR: k1 = (int32_t)((uint32_t)k1 >> (k2 & 63)); break;
  case IR_BSAR: k1 >>= (k2 & 63); break;
  case IR_BROL: k1 = (int32_t)lj_rol((uint32_t)k1, (k2 & 63)); break;
  case IR_BROR: k1 = (int32_t)lj_ror((uint32_t)k1, (k2 & 63)); break;
#endif
  default: UNUSED(k2); lua_assert(0); break;
  }
  return k1;
}