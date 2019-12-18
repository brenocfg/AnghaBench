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
typedef  int /*<<< orphan*/  x86Op ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * mcp; } ;
typedef  int /*<<< orphan*/  Reg ;
typedef  int /*<<< orphan*/  MCode ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  MODRM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RID_EBP ; 
 int /*<<< orphan*/  RID_ESP ; 
 int /*<<< orphan*/  XM_OFS0 ; 
 int /*<<< orphan*/  XM_SCALE1 ; 
 void* emit_opm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptr2addr (void const*) ; 

__attribute__((used)) static void emit_rma(ASMState *as, x86Op xo, Reg rr, const void *addr)
{
  MCode *p = as->mcp;
  *(int32_t *)(p-4) = ptr2addr(addr);
#if LJ_64
  p[-5] = MODRM(XM_SCALE1, RID_ESP, RID_EBP);
  as->mcp = emit_opm(xo, XM_OFS0, rr, RID_ESP, p, -5);
#else
  as->mcp = emit_opm(xo, XM_OFS0, rr, RID_EBP, p, -4);
#endif
}