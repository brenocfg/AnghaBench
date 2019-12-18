#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  jit_State ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int /*<<< orphan*/  t; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  TYPE_1__ IRIns ;

/* Variables and functions */
#define  IRT_I16 136 
#define  IRT_I64 135 
#define  IRT_I8 134 
#define  IRT_INT 133 
#define  IRT_NUM 132 
#define  IRT_U16 131 
#define  IRT_U32 130 
#define  IRT_U64 129 
#define  IRT_U8 128 
 int irt_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_getu16 (void const*) ; 
 int /*<<< orphan*/  lj_getu32 (void const*) ; 
 int /*<<< orphan*/  lj_ir_kint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_knum_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TRef kfold_xload(jit_State *J, IRIns *ir, const void *p)
{
  int32_t k;
  switch (irt_type(ir->t)) {
  case IRT_NUM: return lj_ir_knum_u64(J, *(uint64_t *)p);
  case IRT_I8: k = (int32_t)*(int8_t *)p; break;
  case IRT_U8: k = (int32_t)*(uint8_t *)p; break;
  case IRT_I16: k = (int32_t)(int16_t)lj_getu16(p); break;
  case IRT_U16: k = (int32_t)(uint16_t)lj_getu16(p); break;
  case IRT_INT: case IRT_U32: k = (int32_t)lj_getu32(p); break;
  case IRT_I64: case IRT_U64: return lj_ir_kint64(J, *(uint64_t *)p);
  default: return 0;
  }
  return lj_ir_kint(J, k);
}