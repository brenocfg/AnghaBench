#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86Op ;
typedef  int /*<<< orphan*/  x86Mode ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {int base; scalar_t__ ofs; int idx; int /*<<< orphan*/  scale; } ;
struct TYPE_5__ {scalar_t__* mcp; TYPE_1__ mrm; } ;
typedef  int Reg ;
typedef  scalar_t__ MCode ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 scalar_t__ MODRM (int /*<<< orphan*/ ,int,int) ; 
 int RID_EBP ; 
 int RID_ESP ; 
 int RID_MRM ; 
 int RID_NONE ; 
 int /*<<< orphan*/  XM_OFS0 ; 
 int /*<<< orphan*/  XM_OFS32 ; 
 int /*<<< orphan*/  XM_OFS8 ; 
 int /*<<< orphan*/  XM_REG ; 
 int /*<<< orphan*/  XM_SCALE1 ; 
 scalar_t__ checki8 (scalar_t__) ; 
 scalar_t__* emit_opm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__* emit_opmx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,scalar_t__*) ; 

__attribute__((used)) static void emit_mrm(ASMState *as, x86Op xo, Reg rr, Reg rb)
{
  MCode *p = as->mcp;
  x86Mode mode = XM_REG;
  if (rb == RID_MRM) {
    rb = as->mrm.base;
    if (rb == RID_NONE) {
      rb = RID_EBP;
      mode = XM_OFS0;
      p -= 4;
      *(int32_t *)p = as->mrm.ofs;
      if (as->mrm.idx != RID_NONE)
	goto mrmidx;
#if LJ_64
      *--p = MODRM(XM_SCALE1, RID_ESP, RID_EBP);
      rb = RID_ESP;
#endif
    } else {
      if (as->mrm.ofs == 0 && (rb&7) != RID_EBP) {
	mode = XM_OFS0;
      } else if (checki8(as->mrm.ofs)) {
	*--p = (MCode)as->mrm.ofs;
	mode = XM_OFS8;
      } else {
	p -= 4;
	*(int32_t *)p = as->mrm.ofs;
	mode = XM_OFS32;
      }
      if (as->mrm.idx != RID_NONE) {
      mrmidx:
	as->mcp = emit_opmx(xo, mode, as->mrm.scale, rr, rb, as->mrm.idx, p);
	return;
      }
      if ((rb&7) == RID_ESP)
	*--p = MODRM(XM_SCALE1, RID_ESP, RID_ESP);
    }
  }
  as->mcp = emit_opm(xo, mode, rr, rb, p, 0);
}