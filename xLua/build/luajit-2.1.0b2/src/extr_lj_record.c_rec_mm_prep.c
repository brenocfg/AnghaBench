#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t maxslot; int* base; int /*<<< orphan*/  framedepth; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ jit_State ;
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {size_t framesize; } ;
typedef  int TRef ;
typedef  size_t BCReg ;
typedef  scalar_t__ ASMFunction ;

/* Variables and functions */
 int TREF_CONT ; 
 TYPE_4__* curr_proto (int /*<<< orphan*/ ) ; 
 scalar_t__ lj_cont_cat ; 
 int lj_ir_kptr (TYPE_1__*,void*) ; 
 scalar_t__ lj_vm_asm_begin ; 

__attribute__((used)) static BCReg rec_mm_prep(jit_State *J, ASMFunction cont)
{
  BCReg s, top = cont == lj_cont_cat ? J->maxslot : curr_proto(J->L)->framesize;
#if LJ_64
  TRef trcont = lj_ir_kptr(J, (void *)((int64_t)cont-(int64_t)lj_vm_asm_begin));
#else
  TRef trcont = lj_ir_kptr(J, (void *)cont);
#endif
  J->base[top] = trcont | TREF_CONT;
  J->framedepth++;
  for (s = J->maxslot; s < top; s++)
    J->base[s] = 0;  /* Clear frame gap to avoid resurrecting previous refs. */
  return top+1;
}